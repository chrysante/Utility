#pragma once

#include "functional.hpp"
#include "hashmap.hpp"
#include "scope_guard.hpp"
#include "type_traits"
#include "vector.hpp"

#include <any>
#include <typeindex>

namespace utl {

/// MARK: listener_id
struct listener_id {
    std::type_index __utl_type;
    std::size_t __utl_index;
};

/// MARK: messenger
class messenger {
public:
    void send(std::any&& message) { send_impl(std::move(message)); }
    void send(std::any const& message) { send_impl(message); }

    template <typename T>
    listener_id listen(std::invocable<T> auto&& listener) {
        using U = std::decay_t<T>;
        std::type_index const type = typeid(U);
        auto& typed_listeners = _listeners[type];
        typed_listeners[_index] =
            [listener = UTL_FORWARD(listener)](std::any const& message) {
            std::invoke(listener, std::any_cast<U const&>(message));
        };
        return listener_id{ type, _index++ };
    }

    template <typename L>
    listener_id listen(L&& listener)
    requires(utl::function_traits<L>::argument_count == 1) &&
            requires { typename utl::function_traits<L>::template argument<0>; }
    {
        using T = std::decay_t<
            typename utl::function_traits<L>::template argument<0>>;
        return listen<T>(UTL_FORWARD(listener));
    }

    void unlisten(listener_id const& id) {
        auto const list_itr = _listeners.find(id.__utl_type);
        __utl_expect(list_itr != _listeners.end(), "Invalid ID");
        auto& typed_listeners = list_itr->second;
        auto const itr = typed_listeners.find(id.__utl_index);
        __utl_expect(itr != typed_listeners.end(), "Invalid ID");
        typed_listeners.erase(itr);
    }

private:
    template <typename T>
    void send_impl(T&& message) {
        std::type_index const type = message.type();
        auto const& typed_listeners = _listeners[type];
        for (auto&& [key, listener] : typed_listeners) {
            listener(message);
        }
    }

private:
    hashmap<std::type_index,
            hashmap<std::size_t, function<void(std::any const&)>>>
        _listeners;
    std::size_t _index = 0;
};

/// MARK: buffered_messenger
class buffered_messenger: private messenger {
public:
    void send(std::any const& message) { _messages.push_back(message); }

    void send(std::any&& message) { _messages.push_back(std::move(message)); }

    void send_now(std::any const& message) { messenger::send(message); }

    void send_now(std::any&& message) { messenger::send(std::move(message)); }

    using messenger::listen;
    using messenger::unlisten;

    void flush() {
        // guard this here to prevent feedback loops
        if (flushing) {
            return;
        }
        flushing = true;
        scope_guard reset = [&] { flushing = false; };
        for (auto const& msg : _messages) {
            messenger::send(msg);
        }
        _messages.clear();
    }

    std::size_t buffered_messages() const { return _messages.size(); }

private:
    utl::vector<std::any> _messages;
    bool flushing = false;
};

/// Convinience Classes
/// MARK: receiver
template <typename Messenger>
class receiver {
    static_assert(std::is_same_v<Messenger, messenger> ||
                  std::is_same_v<Messenger, buffered_messenger>);

public:
    receiver() = default;
    explicit receiver(std::weak_ptr<Messenger> m): m(std::move(m)) {}
    receiver(receiver const&) = delete;
    receiver(receiver&&) = default;
    receiver& operator=(receiver const&) = delete;
    receiver& operator=(receiver&&) = default;
    ~receiver() { unlisten_all(); }

    void set_messenger(std::weak_ptr<Messenger> m) {
        unlisten_all();
        m = std::move(m);
    }

    template <typename T>
    void listen(std::invocable<T> auto&& listener) {
        __utl_expect(m != nullptr);
        listen_impl(UTL_FORWARD(listener));
    }

    template <typename L>
    void listen(L&& listener) {
        listen_impl(UTL_FORWARD(listener));
    }

    void unlisten_all() {
        auto const msg = m.lock();
        for (auto const& id : ids) {
            msg->unlisten(id);
        }
        ids.clear();
    }

private:
    void listen_impl(auto&& l) {
        auto const msg = m.lock();
        if (msg) {
            ids.push_back(msg->listen(UTL_FORWARD(l)));
        }
    }

private:
    std::weak_ptr<Messenger> m;
    utl::vector<listener_id> ids;
};

/// MARK: emitter
template <typename Messenger>
class emitter {
    static_assert(std::is_same_v<Messenger, messenger> ||
                  std::is_same_v<Messenger, buffered_messenger>);

public:
    emitter() = default;
    explicit emitter(std::shared_ptr<Messenger> m): m(std::move(m)) {}

    void set_messenger(std::shared_ptr<Messenger> m) {
        __utl_expect(m);
        m = std::move(m);
    }

    void send(std::any&& message) const {
        __utl_expect(m);
        m->send(std::move(message));
    }

    void send(std::any const& message) const {
        __utl_expect(m);
        m->send(message);
    }

    void send_now(std::any&& message) const {
        __utl_expect(m);
        m->send_now(std::move(message));
    }

    void send_now(std::any const& message) const {
        __utl_expect(m);
        m->send_now(message);
    }

private:
    std::shared_ptr<Messenger> m;
    utl::vector<listener_id> ids;
};

} // namespace utl
