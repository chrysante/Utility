#ifndef UTL_MESSENGER_HPP_
#define UTL_MESSENGER_HPP_

#include <any>
#include <atomic>
#include <concepts>
#include <mutex>
#include <typeindex>

#include <utl/functional.hpp>
#include <utl/hashtable.hpp>
#include <utl/scope_guard.hpp>
#include <utl/type_traits.hpp>
#include <utl/vector.hpp>

namespace utl {

///
template <typename Messenger>
concept messenger_type = requires(Messenger msgn, std::any msg,
                                  Messenger::listener_id_type id) {
    // `send_now()` overloads
    msgn.send_now(std::move(msg));
    msgn.send_now(msg);

    // `listen()` with type explicit
    {
        msgn.template listen<int>([](int) {})
    } -> std::convertible_to<typename Messenger::listener_id_type>;

    // `listen()` with argument type deduction
    {
        msgn.listen([](int) {})
    } -> std::convertible_to<typename Messenger::listener_id_type>;

    // `unlisten()` single argument
    msgn.unlisten(id);

    // `unlisten()` range
    requires requires(std::vector<typename Messenger::listener_id_type> vec) {
        msgn.unlisten(vec.begin(), vec.end());
    };
};

template <typename Messenger>
concept buffered_messenger_type =
    messenger_type<Messenger> && requires(Messenger msgn, std::any msg) {
        // `send_buffered()` overloads
        msgn.send_buffered(std::move(msg));
        msgn.send_buffered(msg);
    };

/// \brief Represents a unique ID used to identify and remove a registered
/// listener.
struct listener_id {
    std::type_index __utl_type;
    std::size_t __utl_index;
};

/// \brief Asynchronous messenger for type-erased message dispatch and listener
/// management.
/// \note Thread-safe for concurrent calls to `send()`/`listen()`/`unlisten()`.
/// \warning Do not call `unlisten()` from within a listener callback.
class messenger {
public:
    using listener_id_type = listener_id;

    /// \brief Immediately invokes all listeners for the message's type.
    void send_now(std::any&& message) {
        std::lock_guard lock(_listener_mutex);
        send_impl_unsynchronized(std::move(message));
    }

    /// \overload
    void send_now(std::any const& message) {
        std::lock_guard lock(_listener_mutex);
        send_impl_unsynchronized(message);
    }

    /// \brief Registers a listener for messages of type `T`.
    /// \tparam T Message type.
    /// \tparam L Invocable listener type.
    /// \pre Not called from within a listener callback.
    template <typename T, std::invocable<T> L>
    listener_id listen(L&& listener) {
        using U = std::decay_t<T>;
        std::type_index const type = typeid(U);
        std::lock_guard lock(_listener_mutex);
        auto& typed_listeners = _listeners[type];
        typed_listeners[_index] =
            [listener = std::forward<L>(listener)](std::any const& message) {
            std::invoke(listener, std::any_cast<U const&>(message));
        };
        return listener_id{ type, _index++ };
    }

    /// \brief Registers a listener by inferring its argument type.
    /// \tparam L Callable taking exactly one argument.
    /// \pre Not called from within a listener callback.
    template <typename L>
    listener_id listen(L&& listener)
    requires(utl::function_traits<L>::argument_count == 1)
    {
        using T = std::decay_t<
            typename utl::function_traits<L>::template argument<0>>;
        return listen<T>(std::forward<L>(listener));
    }

    /// \brief Removes a registered listener.
    /// \pre Not called from within a listener callback.
    void unlisten(listener_id const& ID) {
        std::lock_guard lock(_listener_mutex);
        unlisten_unsynchronized(ID);
    }

    /// \brief Removes multiple listeners.
    /// \pre Not called from within a listener callback.
    template <std::input_iterator I, std::sentinel_for<I> S>
    requires std::convertible_to<std::iter_value_t<I>, listener_id>
    void unlisten(I begin, S end) {
        std::lock_guard lock(_listener_mutex);
        for (; begin != end; ++begin)
            unlisten_unsynchronized(*begin);
    }

private:
    friend class buffered_messenger;

    /// \brief Internal dispatch, assumes caller holds `_listener_mutex`.
    template <typename T>
    void send_impl_unsynchronized(T&& message) {
        std::type_index const type = message.type();
        auto const& typed_listeners = _listeners[type];
        for (auto&& [key, listener] : typed_listeners)
            listener(message);
    }

    /// \brief Internal dispatch, assumes caller holds `_listener_mutex`.
    void unlisten_unsynchronized(listener_id const& id) {
        auto const list_itr = _listeners.find(id.__utl_type);
        __utl_expect(list_itr != _listeners.end(), "Invalid ID");
        auto& typed_listeners = list_itr->second;
        auto const itr = typed_listeners.find(id.__utl_index);
        __utl_expect(itr != typed_listeners.end(), "Invalid ID");
        typed_listeners.erase(itr);
    }

    std::recursive_mutex _listener_mutex;
    hashmap<std::type_index,
            hashmap<std::size_t, function<void(std::any const&)>>>
        _listeners;
    std::size_t _index = 0;
};

/// \brief Buffered variant of messenger.
/// Messages are queued and only dispatched when `flush()` is called.
/// \note Thread-safe. May be flushed from any thread.
/// \warning Sending a message during `flush()` defers the new message to the
/// next flush.
class buffered_messenger: private messenger {
public:
    using messenger::listen;
    using messenger::listener_id_type;
    using messenger::send_now;
    using messenger::unlisten;

    /// \brief Queues a message to be sent on next flush.
    void send_buffered(std::any const& message) {
        std::lock_guard lock(_message_queue_mutex);
        _messages.push_back(message);
    }

    /// \overload
    void send_buffered(std::any&& message) {
        std::lock_guard lock(_message_queue_mutex);
        _messages.push_back(std::move(message));
    }

    /// \brief Dispatches all buffered messages in FIFO order.
    /// \note Reentrant-safe: returns immediately if another thread is already
    /// flushing.
    void flush() {
        if (!_flush_mutex.try_lock())
            return;
        std::lock_guard flush_lock(_flush_mutex, std::adopt_lock);
        std::unique_lock msg_lock(_message_queue_mutex);
        auto msgs = std::move(_messages);
        _messages.clear();
        msg_lock.unlock();
        std::lock_guard listener_lock(this->_listener_mutex);
        for (auto& msg : msgs)
            messenger::send_impl_unsynchronized(std::move(msg));
    }

private:
    std::mutex _flush_mutex;
    std::mutex _message_queue_mutex;
    utl::vector<std::any> _messages;
};

/// \brief Non-owning wrapper for receiving messages from a messenger.
/// Automatically unregisters all listeners on destruction.
/// \note Not thread-safe. Must not be accessed from multiple threads
/// concurrently.
template <messenger_type Messenger>
class receiver {
public:
    receiver() = default;
    explicit receiver(std::weak_ptr<Messenger> m): m(std::move(m)) {}
    receiver(receiver const&) = delete;
    receiver(receiver&&) = default;
    receiver& operator=(receiver const&) = delete;
    receiver& operator=(receiver&&) = default;
    ~receiver() { unlisten_all(); }

    /// \brief Sets the target messenger and clears existing listeners.
    void set_messenger(std::weak_ptr<Messenger> msgn) {
        unlisten_all();
        m = std::move(msgn);
    }

    /// \brief Registers a listener for a specific type.
    /// \note Does nothing if the messenger has expired.
    template <typename T, std::invocable<T> L>
    void listen(L&& listener) {
        listen_impl(std::forward<L>(listener));
    }

    /// \brief Registers a listener by inferring its argument type.
    /// \note Does nothing if the messenger has expired.
    template <typename L>
    void listen(L&& listener) {
        listen_impl(std::forward<L>(listener));
    }

    /// \brief Removes all registered listeners.
    void unlisten_all() {
        if (auto msgn = m.lock())
            msgn->unlisten(ids.begin(), ids.end());
        ids.clear();
    }

private:
    template <typename L>
    void listen_impl(L&& l) {
        auto const msg = m.lock();
        if (msg)
            ids.push_back(msg->listen(std::forward<L>(l)));
    }

private:
    std::weak_ptr<Messenger> m;
    utl::vector<listener_id> ids;
};

/// \brief Wrapper for sending messages to a `messenger`.
template <messenger_type Messenger>
class emitter {
public:
    emitter() = default;

    explicit emitter(std::shared_ptr<Messenger> m): m(std::move(m)) {}

    /// \brief Sets the target messenger.
    void set_messenger(std::shared_ptr<Messenger> m) {
        __utl_expect(m);
        m = std::move(m);
    }

    /// \brief Immediately dispatches a message, bypassing the buffer.
    void send_now(std::any&& message) const { m->send_now(std::move(message)); }

    /// \overload
    void send_now(std::any const& message) const { m->send_now(message); }

    /// \brief Sends a message
    void send_buffered(std::any&& message) const
    requires buffered_messenger_type<Messenger>
    {
        __utl_expect(m);
        m->send_buffered(std::move(message));
    }

    /// \overload
    void send_buffered(std::any const& message) const
    requires buffered_messenger_type<Messenger>
    {
        __utl_expect(m);
        m->send_buffered(message);
    }

private:
    std::shared_ptr<Messenger> m;
};

/// \brief Combines `receiver` and `emitter` for bidirectional messaging.
/// \note `receiver`-interface not thread-safe. Must not be accessed from
/// multiple threads concurrently.
template <messenger_type Messenger>
class transceiver: public receiver<Messenger>, public emitter<Messenger> {
public:
    transceiver() = default;
    explicit transceiver(std::shared_ptr<Messenger> m):
        receiver<Messenger>(m), emitter<Messenger>(m) {}

    /// \brief Sets the shared messenger for both sending and receiving.
    void set_messenger(std::shared_ptr<Messenger> m) {
        receiver<Messenger>::set_messenger(m);
        emitter<Messenger>::set_messenger(m);
    }
};

} // namespace utl

#endif // UTL_MESSENGER_HPP_
