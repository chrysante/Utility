#include <iterator>
#include <memory>
#include <utility>

namespace utl {

/// Output iterator that calls a function with the assigned value on assignment.
template <typename F>
class callback_iterator {
public:
    using difference_type = std::ptrdiff_t;

    using iterator_category = std::output_iterator_tag;

    struct reference {
        template <typename T>
        constexpr reference operator=(T&& value) const {
            std::invoke(r.callback, std::forward<T>(value));
            return *this;
        }

    private:
        friend class callback_iterator;

        constexpr reference(callback_iterator& r): r(r) {}

        callback_iterator& r;
    };

    explicit constexpr callback_iterator(F callback):
        callback(std::move(callback)) {}

    callback_iterator(callback_iterator const&) = default;
    callback_iterator(callback_iterator&&) = default;

    // Workaround for the fact, that capturing lambdas are not assignable. We
    // simply destroy and reconstruct non-assignable callback types
    callback_iterator& operator=(callback_iterator const&)
    requires std::is_copy_assignable_v<F>
    = default;
    callback_iterator& operator=(callback_iterator&&)
    requires std::is_move_assignable_v<F>
    = default;

    constexpr callback_iterator& operator=(callback_iterator const& rhs) {
        std::destroy_at(&callback);
        std::construct_at(&callback, rhs);
        return *this;
    }
    constexpr callback_iterator& operator=(callback_iterator&& rhs) {
        std::destroy_at(&callback);
        std::construct_at(&callback, std::move(rhs));
        return *this;
    }

    constexpr reference operator*() { return *this; }

    constexpr callback_iterator& operator++() { return *this; }

    constexpr callback_iterator operator++(int) { return *this; }

private:
    F callback;
};

template <typename F>
callback_iterator(F) -> callback_iterator<F>;

} // namespace utl
