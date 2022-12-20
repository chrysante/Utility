
#include <utl/type_traits.hpp>
#include <utl/__debug.hpp>

namespace utl {

template <typename Signature>
class function_view;

template <bool IsNoexcept, typename R, typename... Args>
class __function_view_impl {
    using __sig = std::conditional_t<IsNoexcept, R(Args...) noexcept, R(Args...)>;
    
public:
    template <typename F>
    requires std::is_invocable_r_v<R, F, Args...> &&
             ((!IsNoexcept) || std::is_nothrow_invocable_r_v<R, F, Args...>) &&
             (!std::is_same_v<function_view<__sig>, std::remove_cvref_t<F>>)
    constexpr __function_view_impl(F&& f) noexcept:
        __invoke_ptr(&__static_invoke<std::remove_reference_t<F>>),
        __state_ptr(reinterpret_cast<void*>(&f))
    {}
    
    constexpr R operator()(Args... args) const noexcept(IsNoexcept) {
        __utl_expect(__invoke_ptr);
        return __invoke_ptr(__state_ptr, args...);
    }
    
private:
    template <typename F>
    constexpr static R __static_invoke(void const* state, Args&... args) {
        F& f = *(F*)state;
        if constexpr (std::is_same_v<R, std::invoke_result_t<F, Args...>>) {
            return std::invoke(f, std::move(args)...);
        }
        else {
            return static_cast<R>(std::invoke(f, std::move(args)...));
        }
    }
    
    decltype(&__static_invoke<void>) __invoke_ptr;
    void const* __state_ptr;
};

template <typename R, typename... Args>
class function_view<R(Args...)>: public __function_view_impl<false, R, Args...> {
    using __base = __function_view_impl<false, R, Args...>;
public:
    using __base::__base;
    using __base::operator();
};

template <typename R, typename... Args>
class function_view<R(Args...) noexcept>: public __function_view_impl<true, R, Args...> {
    using __base = __function_view_impl<true, R, Args...>;
public:
    using __base::__base;
    using __base::operator();
};

} // namespace utl

#include <iostream>
#include <span>
#include <vector>
#include <optional>

struct Lifetime {
    Lifetime()                              { std::cout << "Construct\n"; }
    Lifetime(Lifetime const&)               { std::cout << "Copy construct\n"; }
    Lifetime(Lifetime&&) noexcept           { std::cout << "Move construct\n"; }
    Lifetime operator=(Lifetime const&)     { std::cout << "Copy assign\n"; return *this; }
    Lifetime operator=(Lifetime&&) noexcept { std::cout << "Move assign\n"; return *this; }
    ~Lifetime()                             { std::cout << "Destroy\n"; }
};

struct S {
    void f(Lifetime) { std::cout << "f()\n"; }
};

void f(utl::function_view<void(S, Lifetime&&)> callback, Lifetime l) {
    callback(S{}, std::move(l));
}

[[gnu::weak]]
int main() {
    
    f(&S::f, Lifetime{});
    
}

