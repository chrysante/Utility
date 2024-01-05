#include <catch/catch2.hpp>
#include <utl/dyncast.hpp>
#include <utl/utility.hpp>

#include "TypeCompare.h"

TEST_CASE("dyncast internals", "[dyncast]") {
    using namespace utl::dc;
    // Single dimensional case
    CHECK(flattenIndex<1>({ 0 }, { 3 }) == 0);
    CHECK(expandIndex<1>(0, { 3 }) == std::array<size_t, 1>{ 0 });
    CHECK(flattenIndex<1>({ 2 }, { 3 }) == 2);
    CHECK(expandIndex<1>(2, { 3 }) == std::array<size_t, 1>{ 2 });

    // +---+---+
    // | 0 | 1 |
    // +---+---+
    // | 2 | 3 |
    // +---+---+
    CHECK(flattenIndex<2>({ 1, 1 }, { 2, 2 }) == 3);
    CHECK(expandIndex<2>(3, { 2, 2 }) == std::array<size_t, 2>{ 1, 1 });

    // +---+---+---+
    // | 0 | 1 | 2 |
    // +---+---+---+
    // | 3 | 4 | 5 |
    // +---+---+---+
    CHECK(flattenIndex<2>({ 1, 1 }, { 2, 3 }) == 4);
    CHECK(expandIndex<2>(4, { 2, 3 }) == std::array<size_t, 2>{ 1, 1 });
    CHECK(flattenIndex<2>({ 0, 2 }, { 2, 3 }) == 2);
    CHECK(expandIndex<2>(2, { 2, 3 }) == std::array<size_t, 2>{ 0, 2 });

    // +---+---+
    // | 0 | 1 |
    // +---+---+
    // | 2 | 3 |
    // +---+---+
    // | 4 | 5 |
    // +---+---+
    CHECK(flattenIndex<2>({ 1, 1 }, { 3, 2 }) == 3);
    CHECK(expandIndex<2>(3, { 3, 2 }) == std::array<size_t, 2>{ 1, 1 });
    CHECK(flattenIndex<2>({ 0, 1 }, { 3, 2 }) == 1);
    CHECK(expandIndex<2>(1, { 3, 2 }) == std::array<size_t, 2>{ 0, 1 });
    CHECK(flattenIndex<2>({ 2, 0 }, { 3, 2 }) == 4);
    CHECK(expandIndex<2>(4, { 3, 2 }) == std::array<size_t, 2>{ 2, 0 });
    CHECK(flattenIndex<2>({ 2, 1 }, { 3, 2 }) == 5);
    CHECK(expandIndex<2>(5, { 3, 2 }) == std::array<size_t, 2>{ 2, 1 });

    // +---+---+
    // | 0 | 3 |---+---+
    // +---+---+ 1 | 4 |---+---+
    // | 6 | 9 |---+---+ 2 | 5 |
    // +---+---+ 7 |10 |---+---+
    // |12 |15 |---+---+ 8 |11 |
    // +---+---+13 |16 |---+---+
    //         +---+---+14 |17 |
    //                 +---+---+
    CHECK(flattenIndex<3>({ 1, 1, 1 }, { 3, 2, 3 }) == 10);
    CHECK(expandIndex<3>(10, { 3, 2, 3 }) == std::array<size_t, 3>{ 1, 1, 1 });
    CHECK(flattenIndex<3>({ 0, 1, 2 }, { 3, 2, 3 }) == 5);
    CHECK(expandIndex<3>(5, { 3, 2, 3 }) == std::array<size_t, 3>{ 0, 1, 2 });
}

/// # Class hierarchy of new test cases

namespace {

enum class ID {
    Animal = 0,
    Cetacea = 1,
    Whale = 2,
    Dolphin = 3,
    Leopard = 4,
    LAST = Leopard
};

struct Animal;
struct Cetacea;
struct Whale;
struct Dolphin;
struct Whale;
struct Leopard;

} // namespace

UTL_DYNCAST_DEFINE(Animal, ID::Animal, void, Abstract);
UTL_DYNCAST_DEFINE(Cetacea, ID::Cetacea, Animal, Abstract);
UTL_DYNCAST_DEFINE(Whale, ID::Whale, Cetacea, Concrete);
UTL_DYNCAST_DEFINE(Dolphin, ID::Dolphin, Cetacea, Concrete);
UTL_DYNCAST_DEFINE(Leopard, ID::Leopard, Animal, Concrete);

namespace {

struct Animal {
protected:
    Animal(ID id): id(id) {}

private:
    friend ID dyncast_get_type(Animal const& animal) { return animal.id; }

    ID id;
};

struct Cetacea: Animal {
protected:
    using Animal::Animal;
};

struct Whale: Cetacea {
    Whale(): Cetacea(ID::Whale) {}
};

} // namespace

// Dolphin and Leopard remain undefined at this point

TEST_CASE("isa and dyncast", "[dyncast]") {
    Whale whale;
    Animal* animal = &whale;

    CHECK(utl::isa<Animal>(animal));
    CHECK(utl::isa<Cetacea>(animal));
    CHECK(utl::isa<Whale>(animal));
    CHECK(!utl::isa<Leopard>(animal));
    CHECK(!utl::isa<Dolphin>(animal));

    CHECK(utl::dyncast<Animal*>(animal));
    CHECK(utl::dyncast<Cetacea*>(animal));
    CHECK(utl::dyncast<Whale*>(animal));
}

// Now we define the remaining types

namespace {

struct Dolphin: Cetacea {
    Dolphin(): Cetacea(ID::Dolphin) {}
};

struct Leopard: Animal {
    Leopard(): Animal(ID::Leopard) {}
};

} // namespace

TEST_CASE("Visitation") {
    Dolphin d;
    Leopard l;
    SECTION("Return void") {
        bool foundDolphin = false;
        // clang-format off
        utl::visit((Cetacea&)d, utl::overload{
            [&](Dolphin const&) { foundDolphin = true; },
            [&](Animal const&) {}
        }); // clang-format on
        CHECK(foundDolphin);
    }
    SECTION("More cases") {
        bool foundCetaceaAndLeopard = false;
        // clang-format off
        utl::visit((Cetacea&)d, (Animal const&)l, utl::overload{
            [&](Cetacea const&, Leopard const&) {
                foundCetaceaAndLeopard = true;
            },
            [&](Cetacea const&, Animal const&) {},
            [&](Animal const&, Animal const&) {}
        }); // clang-format on
        CHECK(foundCetaceaAndLeopard);
    }
    SECTION("Return type deduced as int") {
        // clang-format off
        auto res = utl::visit((Cetacea&)d, (Animal const&)l, utl::overload{
            [&](Cetacea const&, Leopard const&) {
                return 1;
            },
            [&](Cetacea const&, Animal const&) { return '\0'; },
            [&](Animal const&, Animal const&) { return (unsigned short)0; }
        }); // clang-format on
        CHECK(res == 1);
        static_assert(std::is_same_v<decltype(res), int>);
    }
    SECTION("Returns reference") {
        struct Base {};
        struct Derived: Base {};
        Derived obj;

        // clang-format off
        auto& res = utl::visit((Cetacea&)d, (Animal const&)l, utl::overload{
            [&](Cetacea const&, Leopard const&) -> Derived& {
                return obj;
            },
            [&](Cetacea const&, Animal const&) -> Base& {
                return obj;
            },
            [&](Animal const&, Animal const&) -> Derived& {
                return obj;
            }
        }); // clang-format on
        CHECK(std::is_same_v<decltype(res), Base&>);
    }
}

/// # Second class hierarchy of old test cases

namespace {

// Base
// ├─ LDerivedA
// │  └─ LDerivedB
// │     └─ LDerivedC
// └─ RDerived

enum class Type {
    Base,
    LDerivedA,
    LDerivedB,
    LDerivedC,
    RDerived,
    LAST = RDerived
};

struct Base {
protected:
    explicit Base(Type type): _type(type) {}

public:
    Type type() const { return _type; }

private:
    friend Type dyncast_get_type(Base const& obj) { return obj.type(); }

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

UTL_DYNCAST_DEFINE(Base, Type::Base, void, Abstract);
UTL_DYNCAST_DEFINE(LDerivedA, Type::LDerivedA, Base, Concrete);
UTL_DYNCAST_DEFINE(LDerivedB, Type::LDerivedB, LDerivedA, Concrete);
UTL_DYNCAST_DEFINE(LDerivedC, Type::LDerivedC, LDerivedB, Concrete);
UTL_DYNCAST_DEFINE(RDerived, Type::RDerived, Base, Concrete);

template <typename To, typename From>
static bool canDyncast(From&& from) {
    return requires { dyncast<To>(from); };
}

using namespace utl_test;

TEST_CASE("Dyncast visit", "[common][dyncast]") {
    LDerivedA a;
    Base& base = a;
    CHECK(utl::visit(base, [](Base& base) { return base.type(); }) ==
          Type::LDerivedA);
}

TEST_CASE("Dyncast visit abstract", "[common][dyncast]") {
    LDerivedA a;
    Base& base = a;
    int i = 0;
    /// Primarily testing successful compilation here.
    /// We wrap \p utl::overload in a lambda taking \p auto& to test that the
    /// function doesn't get called with non-sensible arguments even if
    /// semantically possible.
    utl::visit(base, [&](auto& b) {
        return utl::overload{ [&](LDerivedA&) { i = 1; },
                              [&](RDerived&) { i = 2; } }(b);
    });
    CHECK(i == 1);
}

TEST_CASE("Dyncast visit returning reference", "[common][dyncast]") {
    LDerivedA a;
    Base& base = a;
    auto f = [&, i = 0](Base&) -> auto& { return i; };
    decltype(auto) result = utl::visit(base, f);
    CHECK(T<decltype(result)> == T<int const&>);
}

TEST_CASE("Dyncast visit returning reference to hierarchy",
          "[common][dyncast]") {
    struct A {};
    struct B: A {};
    LDerivedA a;
    Base& base = a;
    SECTION("Reference") {
        decltype(auto) result =
            utl::visit(base, [b = B{}]<typename T>(T&) -> auto& {
                if constexpr (std::is_same_v<T, LDerivedB>) {
                    return static_cast<A const&>(b);
                }
                else {
                    return b;
                }
            });
        CHECK(T<decltype(result)> == T<A const&>);
    }
    SECTION("Pointer") {
        auto* result = utl::visit(base, [b = B{}]<typename T>(T&) -> auto* {
            if constexpr (std::is_same_v<T, LDerivedB>) {
                return static_cast<A const*>(&b);
            }
            else {
                return &b;
            }
        });
        CHECK(T<decltype(result)> == T<A const*>);
    }
}

TEST_CASE("Dyncast visit subtree", "[common][dyncast]") {
    auto dispatcher = [](LDerivedA& x) {
        return visit(x, utl::overload{
                            [](LDerivedA& a) { return 0; },
                            [](LDerivedC& c) { return 1; },
                        });
    };
    LDerivedA a;
    LDerivedB b;
    LDerivedC c;
    CHECK(dispatcher(a) == 0);
    CHECK(dispatcher(b) == 0);
    CHECK(dispatcher(c) == 1);
}

TEST_CASE("Dyncast visit subtree - 2", "[common][dyncast]") {
    auto dispatcher = [](LDerivedA& x) {
        return utl::visit(x, utl::overload{
                                 [](LDerivedA& a) { return 0; },
                                 [](LDerivedB& b) { return 1; },
                             });
    };
    LDerivedA a;
    LDerivedB b;
    LDerivedC c;
    CHECK(dispatcher(a) == 0);
    CHECK(dispatcher(b) == 1);
    CHECK(dispatcher(c) == 1);
}

TEST_CASE("Dyncast MD visit", "[common][dyncast]") {
    auto dispatcher = [](Base& b, LDerivedA& x) {
        return utl::visit(b, x,
                          utl::overload{
                              [](Base&, LDerivedA& a) { return 0; },
                              [](Base&, LDerivedB& b) { return 1; },
                              [](LDerivedB&, LDerivedA& a) { return 2; },
                              [](LDerivedB&, LDerivedB& b) { return 3; },
                          });
    };
    LDerivedA a;
    LDerivedB b;
    LDerivedC c;
    CHECK(dispatcher(a, a) == 0);
    CHECK(dispatcher(a, b) == 1);
    CHECK(dispatcher(a, c) == 1);
    CHECK(dispatcher(b, a) == 2);
    CHECK(dispatcher(b, b) == 3);
    CHECK(dispatcher(b, c) == 3);
}

TEST_CASE("isa and dyncast", "[common][dyncast]") {
    LDerivedA la;

    CHECK(utl::isa<Base>(la));
    CHECK(utl::isa<LDerivedA>(la));
    CHECK(!utl::isa<LDerivedB>(la));
    CHECK(!utl::isa<RDerived>(la));

    CHECK(utl::dyncast<Base*>(&la) != nullptr);
    CHECK(utl::dyncast<LDerivedA*>(&la) != nullptr);
    CHECK(utl::dyncast<LDerivedB*>(&la) == nullptr);
    CHECK(!canDyncast<RDerived*>(&la));

    CHECK_NOTHROW(utl::dyncast<Base&>(la));
    CHECK_NOTHROW(utl::dyncast<LDerivedA&>(la));
    CHECK_THROWS(utl::dyncast<LDerivedB&>(la));

    Base const* base = &la;

    CHECK(utl::isa<Base>(*base));
    CHECK(utl::isa<LDerivedA>(*base));
    CHECK(!utl::isa<LDerivedB>(*base));
    CHECK(!utl::isa<RDerived>(*base));

    CHECK(utl::dyncast<Base const*>(base) != nullptr);
    CHECK(utl::dyncast<LDerivedA const*>(base) != nullptr);
    CHECK(utl::dyncast<LDerivedB const*>(base) == nullptr);
    CHECK(utl::dyncast<RDerived const*>(base) == nullptr);

    CHECK_NOTHROW(utl::dyncast<Base const&>(*base));
    CHECK_NOTHROW(utl::dyncast<LDerivedA const&>(*base));
    CHECK_THROWS(utl::dyncast<LDerivedB const&>(*base));
    CHECK_THROWS(utl::dyncast<RDerived const&>(*base));

    LDerivedB lb;

    CHECK(utl::isa<Base>(lb));
    CHECK(utl::isa<LDerivedA>(lb));
    CHECK(utl::isa<LDerivedB>(lb));
    CHECK(!utl::isa<RDerived>(lb));

    CHECK(utl::dyncast<Base*>(&lb) != nullptr);
    CHECK(utl::dyncast<LDerivedA*>(&lb) != nullptr);
    CHECK(utl::dyncast<LDerivedB*>(&lb) != nullptr);
    CHECK(!canDyncast<RDerived*>(&lb));

    CHECK_NOTHROW(utl::dyncast<Base&>(lb));
    CHECK_NOTHROW(utl::dyncast<LDerivedA&>(lb));
    CHECK_NOTHROW(utl::dyncast<LDerivedB&>(lb));

    base = &lb;

    CHECK(utl::isa<Base>(*base));
    CHECK(utl::isa<LDerivedA>(*base));
    CHECK(utl::isa<LDerivedB>(*base));
    CHECK(!utl::isa<RDerived>(*base));

    CHECK(utl::dyncast<Base const*>(base) != nullptr);
    CHECK(utl::dyncast<LDerivedA const*>(base) != nullptr);
    CHECK(utl::dyncast<LDerivedB const*>(base) != nullptr);
    CHECK(utl::dyncast<RDerived const*>(base) == nullptr);

    CHECK_NOTHROW(utl::dyncast<Base const&>(*base));
    CHECK_NOTHROW(utl::dyncast<LDerivedA const&>(*base));
    CHECK_NOTHROW(utl::dyncast<LDerivedB const&>(*base));
    CHECK_THROWS(utl::dyncast<RDerived const&>(*base));

    RDerived r;

    CHECK(utl::isa<Base>(r));
    CHECK(!utl::isa<LDerivedA>(r));
    CHECK(!utl::isa<LDerivedB>(r));
    CHECK(utl::isa<RDerived>(r));

    CHECK(utl::dyncast<Base*>(&r) != nullptr);
    CHECK(!canDyncast<LDerivedA*>(&r));
    CHECK(!canDyncast<LDerivedB*>(&r));
    CHECK(utl::dyncast<RDerived*>(&r) != nullptr);

    CHECK_NOTHROW(utl::dyncast<Base&>(r));
    CHECK_NOTHROW(utl::dyncast<RDerived&>(r));

    base = &r;

    CHECK(utl::isa<Base>(*base));
    CHECK(!utl::isa<LDerivedA>(*base));
    CHECK(!utl::isa<LDerivedB>(*base));
    CHECK(utl::isa<RDerived>(*base));

    CHECK(utl::dyncast<Base const*>(base));
    CHECK(!utl::dyncast<LDerivedA const*>(base));
    CHECK(!utl::dyncast<LDerivedB const*>(base));
    CHECK(utl::dyncast<RDerived const*>(base));

    CHECK_NOTHROW(utl::dyncast<Base const&>(*base));
    CHECK_THROWS(utl::dyncast<LDerivedA const&>(*base));
    CHECK_THROWS(utl::dyncast<LDerivedB const&>(*base));
    CHECK_NOTHROW(utl::dyncast<RDerived const&>(*base));
}
