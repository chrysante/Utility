#include <catch/catch2.hpp>

#include <utl/dyncast.hpp>
#include <utl/utility.hpp>

namespace {

enum class Type {
    Base, LDerivedA, LDerivedB, LDerivedC, RDerived, _count
};

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

template <typename To, typename From>
static bool canDyncast(From&& from) {
    return requires { dyncast<To>(from); };
}

TEST_CASE("Dyncast visit", "[common][dyncast]") {
    LDerivedA a;
    Base& base = a;
    CHECK(utl::visit(base, [](Base& base) { return base.type(); }) == Type::LDerivedA);
}

TEST_CASE("Dyncast visit subtree", "[common][dyncast]") {
    auto dispatcher = [](LDerivedA& x) {
        return visit(x, utl::overload {
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
        return utl::visit(x, utl::overload {
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

TEST_CASE("isa and dyncast", "[common][dyncast]") {
    LDerivedA la;

    CHECK( utl::isa<Base>(la));
    CHECK( utl::isa<LDerivedA>(la));
    CHECK(!utl::isa<LDerivedB>(la));
    CHECK(!utl::isa<RDerived>(la));

    CHECK(utl::dyncast<Base*>(&la)      != nullptr);
    CHECK(utl::dyncast<LDerivedA*>(&la) != nullptr);
    CHECK(utl::dyncast<LDerivedB*>(&la) == nullptr);
    CHECK(!canDyncast<RDerived*>(&la));

    CHECK_NOTHROW(utl::dyncast<Base&>(la));
    CHECK_NOTHROW(utl::dyncast<LDerivedA&>(la));
    CHECK_THROWS( utl::dyncast<LDerivedB&>(la));

    Base const* base = &la;

    CHECK( utl::isa<Base>(*base));
    CHECK( utl::isa<LDerivedA>(*base));
    CHECK(!utl::isa<LDerivedB>(*base));
    CHECK(!utl::isa<RDerived>(*base));

    CHECK(utl::dyncast<Base const*>(base)      != nullptr);
    CHECK(utl::dyncast<LDerivedA const*>(base) != nullptr);
    CHECK(utl::dyncast<LDerivedB const*>(base) == nullptr);
    CHECK(utl::dyncast<RDerived const*>(base)  == nullptr);

    CHECK_NOTHROW(utl::dyncast<Base const&>(*base));
    CHECK_NOTHROW(utl::dyncast<LDerivedA const&>(*base));
    CHECK_THROWS( utl::dyncast<LDerivedB const&>(*base));
    CHECK_THROWS( utl::dyncast<RDerived const&>(*base));

    LDerivedB lb;

    CHECK( utl::isa<Base>(lb));
    CHECK( utl::isa<LDerivedA>(lb));
    CHECK( utl::isa<LDerivedB>(lb));
    CHECK(!utl::isa<RDerived>(lb));

    CHECK(utl::dyncast<Base*>(&lb)      != nullptr);
    CHECK(utl::dyncast<LDerivedA*>(&lb) != nullptr);
    CHECK(utl::dyncast<LDerivedB*>(&lb) != nullptr);
    CHECK(!canDyncast<RDerived*>(&lb));

    CHECK_NOTHROW(utl::dyncast<Base&>(lb));
    CHECK_NOTHROW(utl::dyncast<LDerivedA&>(lb));
    CHECK_NOTHROW(utl::dyncast<LDerivedB&>(lb));

    base = &lb;

    CHECK( utl::isa<Base>(*base));
    CHECK( utl::isa<LDerivedA>(*base));
    CHECK( utl::isa<LDerivedB>(*base));
    CHECK(!utl::isa<RDerived>(*base));

    CHECK(utl::dyncast<Base const*>(base)      != nullptr);
    CHECK(utl::dyncast<LDerivedA const*>(base) != nullptr);
    CHECK(utl::dyncast<LDerivedB const*>(base) != nullptr);
    CHECK(utl::dyncast<RDerived const*>(base)  == nullptr);

    CHECK_NOTHROW(utl::dyncast<Base const&>(*base));
    CHECK_NOTHROW(utl::dyncast<LDerivedA const&>(*base));
    CHECK_NOTHROW(utl::dyncast<LDerivedB const&>(*base));
    CHECK_THROWS( utl::dyncast<RDerived const&>(*base));

    RDerived r;

    CHECK( utl::isa<Base>(r));
    CHECK(!utl::isa<LDerivedA>(r));
    CHECK(!utl::isa<LDerivedB>(r));
    CHECK( utl::isa<RDerived>(r));

    CHECK(utl::dyncast<Base*>(&r) != nullptr);
    CHECK(!canDyncast<LDerivedA*>(&r));
    CHECK(!canDyncast<LDerivedB*>(&r));
    CHECK(utl::dyncast<RDerived*>(&r) != nullptr);

    CHECK_NOTHROW(utl::dyncast<Base&>(r));
    CHECK_NOTHROW(utl::dyncast<RDerived&>(r));

    base = &r;

    CHECK( utl::isa<Base>(*base));
    CHECK(!utl::isa<LDerivedA>(*base));
    CHECK(!utl::isa<LDerivedB>(*base));
    CHECK( utl::isa<RDerived>(*base));

    CHECK( utl::dyncast<Base const*>(base));
    CHECK(!utl::dyncast<LDerivedA const*>(base));
    CHECK(!utl::dyncast<LDerivedB const*>(base));
    CHECK( utl::dyncast<RDerived const*>(base));

    CHECK_NOTHROW(utl::dyncast<Base const&>(*base));
    CHECK_THROWS (utl::dyncast<LDerivedA const&>(*base));
    CHECK_THROWS (utl::dyncast<LDerivedB const&>(*base));
    CHECK_NOTHROW(utl::dyncast<RDerived const&>(*base));
}
