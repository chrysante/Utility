#ifndef UTL_HASH_HPP_
#define UTL_HASH_HPP_

#include <string_view>
#include <utility>

#include <utl/__base.hpp>
#include <utl/__third_party/ankerl/unordered_dense.h>
#include <utl/common.hpp>
#include <utl/concepts.hpp>

namespace utl {

template <std::unsigned_integral T>
inline constexpr T __utl_hash_seed = static_cast<T>(0x9e3779b97f4a7c15);

template <typename T>
_UTL_DISABLE_UBSAN_INTEGER void hash_combine_seed(std::size_t& seed,
                                                  T const& v) {
    seed ^= std::hash<T>{}(v) + __utl_hash_seed<std::size_t> + (seed << 6) +
            (seed >> 2);
}

template <typename Key>
concept __utl_hashable = std::is_default_constructible_v<std::hash<Key>>;

template <__utl_hashable... Keys>
std::size_t hash_combine(Keys const&... keys) {
    size_t seed = 0;
    (hash_combine_seed(seed, keys), ...);
    return seed;
}

template <typename I, typename S>
std::size_t hash_combine_range(I begin, S end) {
    size_t seed = __utl_hash_seed<std::size_t>;
    for (; begin != end; ++begin) {
        hash_combine_seed(seed, *begin);
    }
    return seed;
}

template <typename T>
struct hash: ankerl::unordered_dense::hash<T> {
    using is_transparent = void;
    using ankerl::unordered_dense::hash<T>::operator();
    template <typename U>
    decltype(std::declval<std::common_type_t<T, U>>(), std::size_t{})
    operator()(U const& u) const {
        return ankerl::unordered_dense::hash<U>{}(u);
    }
};

template <typename T, typename U>
struct hash<std::pair<T, U>> {
    std::size_t operator()(std::pair<T, U> const& p) const {
        return utl::hash_combine(p.first, p.second);
    }
};

template <typename... T>
struct hash<std::tuple<T...>> {
    std::size_t operator()(std::tuple<T...> const& t) const {
#ifdef _MSC_VER
        return [&]<std::size_t... I>(std::index_sequence<I...>) {
            return utl::hash_combine(std::get<I>(t)...);
        }(std::make_index_sequence<sizeof...(T)>());
#else
        return UTL_WITH_INDEX_SEQUENCE((I, sizeof...(T)), {
            return utl::hash_combine(std::get<I>(t)...);
        });
#endif
    }
};

constexpr std::size_t hash_string(std::string_view str) {
    std::size_t result = 0xcbf29ce484222325; // FNV offset basis

    for (char c : str) {
        result ^= c;
        result *= 1099511628211; // FNV prime
    }

    return result;
}

} // namespace utl

#endif // UTL_HASH_HPP_
