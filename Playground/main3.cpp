#include <iostream>

#include <utl/dyncast.hpp>

namespace {

// Base
// ├─ LDerivedA
// │  └─ LDerivedB
// │     └─ LDerivedC
// └─ RDerived

enum class Type { Base, LDerivedA, LDerivedB, LDerivedC, RDerived, _count };

struct Base {
protected:
    explicit Base(Type type): _type(type) {}

public:
    Type type() const { return _type; }

private:
    Type _type;
};

struct LDerivedA: Base {
protected:
    explicit LDerivedA(Type type): Base(type) {}

public:
    LDerivedA(): Base(Type::LDerivedA) {}
};

struct LDerivedB: LDerivedA {
protected:
    LDerivedB(Type type): LDerivedA(type) {}

    LDerivedB(LDerivedB const&) = delete;

public:
    LDerivedB(): LDerivedA(Type::LDerivedB) {}
};

struct LDerivedC: LDerivedB {
    LDerivedC(): LDerivedB(Type::LDerivedC) {}
};

struct RDerived: Base {
    RDerived(): Base(Type::RDerived) {}
};

} // namespace

UTL_DYNCAST_MAP(Base, Type::Base);
UTL_DYNCAST_MAP(LDerivedA, Type::LDerivedA);
UTL_DYNCAST_MAP(LDerivedB, Type::LDerivedB);
UTL_DYNCAST_MAP(LDerivedC, Type::LDerivedC);
UTL_DYNCAST_MAP(RDerived, Type::RDerived);

UTL_DYNCAST_ABSTRACT(Base);

template <typename T>
struct __match_helper {
    explicit __match_helper(T& value): value(value) {}
    T& value;
};

template <typename... F>
struct fn: utl::overload<F...> { using utl::overload<F...>::overload; };

template <typename... F>
decltype(auto) operator->*(auto& value, utl::overload<F...>&& f) {
    return utl::visit(value, std::move(f));
}

//template <typename... F>
//decltype(auto) match(/*auto& value,*/ utl::overload<F...>&& f) {
//    return utl::visit(/*value*/, std::move(f));
//}

int main() {
    LDerivedB db;
    Base& b = db;
    std::cout << b->*utl::overload{
        [](LDerivedA&) { return "L"; },
        [](RDerived&) { return "R."; },
    } << std::endl;
}
