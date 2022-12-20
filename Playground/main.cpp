#include <utl/function_view.hpp>

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

