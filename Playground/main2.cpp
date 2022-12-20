#include <iostream>
#include <compare>
#include <vector>
#include <list>
#include <forward_list>

#include <experimental/memory_resource>

#include <utl/utility.hpp>
#include <utl/ranges.hpp>
#include <utl/typeinfo.hpp>
#include <utl/vector.hpp>
#include <utl/variant.hpp>

void print(char const* text) { std::cout << text << std::endl; }

struct LifetimeCapabilities {
    template <typename T>
    explicit LifetimeCapabilities(utl::tag<T>):
        defaultConstructible(std::is_default_constructible_v<T>),
        triviallyDefaultConstructible(std::is_trivially_default_constructible_v<T>),
        copyConstructible(std::is_copy_constructible_v<T>),
        triviallyCopyConstructible(std::is_trivially_copy_constructible_v<T>),
        moveConstructible(std::is_move_constructible_v<T>),
        triviallyMoveConstructible(std::is_trivially_move_constructible_v<T>),
        copyAssignable(std::is_copy_assignable_v<T>),
        triviallyCopyAssignable(std::is_trivially_copy_assignable_v<T>),
        moveAssignable(std::is_move_assignable_v<T>),
        triviallyMoveAssignable(std::is_trivially_move_assignable_v<T>),
        destructible(std::is_destructible_v<T>),
        triviallyDestructible(std::is_trivially_destructible_v<T>)
    {}
    
    bool defaultConstructible          : 1;
    bool triviallyDefaultConstructible : 1;
    bool copyConstructible             : 1;
    bool triviallyCopyConstructible    : 1;
    bool moveConstructible             : 1;
    bool triviallyMoveConstructible    : 1;
    bool copyAssignable                : 1;
    bool triviallyCopyAssignable       : 1;
    bool moveAssignable                : 1;
    bool triviallyMoveAssignable       : 1;
    bool destructible                  : 1;
    bool triviallyDestructible         : 1;
};

void print(LifetimeCapabilities c) {
    std::cout << "Default constructible           : " << (c.defaultConstructible          ? "true" : "false") << "\n";
    std::cout << "Trivially default constructible : " << (c.triviallyDefaultConstructible ? "true" : "false") << "\n";
    std::cout << "Copy constructible              : " << (c.copyConstructible             ? "true" : "false") << "\n";
    std::cout << "Trivially copy constructible    : " << (c.triviallyCopyConstructible    ? "true" : "false") << "\n";
    std::cout << "Move constructible              : " << (c.moveConstructible             ? "true" : "false") << "\n";
    std::cout << "Trivially move constructible    : " << (c.triviallyMoveConstructible    ? "true" : "false") << "\n";
    std::cout << "Copy assignable                 : " << (c.copyAssignable                ? "true" : "false") << "\n";
    std::cout << "Trivially copy assignable       : " << (c.triviallyCopyAssignable       ? "true" : "false") << "\n";
    std::cout << "Move assignable                 : " << (c.moveAssignable                ? "true" : "false") << "\n";
    std::cout << "Trivially move assignable       : " << (c.triviallyMoveAssignable       ? "true" : "false") << "\n";
    std::cout << "Destructible                    : " << (c.destructible                  ? "true" : "false") << "\n";
    std::cout << "Trivially destructible          : " << (c.triviallyDestructible         ? "true" : "false") << "\n";
}

[[gnu::weak]]
int main() {
    
    using V = utl::variant<int, float>;
    
    print(LifetimeCapabilities(utl::tag<V>{}));

    V v;
    
//    V w = v;
    
}
