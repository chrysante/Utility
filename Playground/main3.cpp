#include <iostream>

#include <utl/variant.hpp>

namespace {

struct Base {
    int i;
};

int& f(Base& b) { return b.i; }

struct A: Base {
    A(int i, float a): Base{ i }, a(a) {}
    float a;
};

struct B: Base {
    B(int i, long a): Base{ i }, a(a) {}
    long a;
};

struct X { int _; };

struct C: X, B {
    using B::B;
};

} // namespace

void line() { std::cout << "====================================================================\n"; }

[[gnu::weak]]
int main() {
    
}
