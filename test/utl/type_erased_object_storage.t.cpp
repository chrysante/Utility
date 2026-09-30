#include <catch2/catch_test_macros.hpp>

#include <stdexcept>
#include <string>
#include <type_traits>
#include <utility>

#include <utl/type_erased_object_storage.hpp>

namespace {

struct SmallObject {
    int value = 42;

    explicit SmallObject(int value = 42): value(value) {}

    SmallObject(SmallObject&&) noexcept = default;
    SmallObject& operator=(SmallObject&&) noexcept = default;
};

struct LargeObject {
    char data[256]{};
    int value = 42;

    explicit LargeObject(int value = 42): value(value) {}

    LargeObject(LargeObject&&) noexcept = default;
    LargeObject& operator=(LargeObject&&) noexcept = default;
};

struct DestructionTracker {
    bool* destroyed;

    explicit DestructionTracker(bool& destroyed): destroyed(&destroyed) {
        *this->destroyed = false;
    }

    ~DestructionTracker() { *destroyed = true; }

    DestructionTracker(DestructionTracker&& other) noexcept:
        destroyed(other.destroyed) {
        other.destroyed = nullptr;
    }
};

struct ThrowingConstructor {
    explicit ThrowingConstructor() {
        throw std::runtime_error("construction failed");
    }
};

struct ThrowingMove {
    ThrowingMove() = default;

    ThrowingMove(ThrowingMove&&) { throw std::runtime_error("move failed"); }
};

} // namespace

TEST_CASE("utl::type_erased_object_storage starts empty") {
    utl::type_erased_object_storage storage;
    REQUIRE_FALSE(storage.has_value());
    REQUIRE_FALSE(static_cast<bool>(storage));
    REQUIRE(storage.data() == nullptr);
    REQUIRE(storage.type() == typeid(void));
}

TEST_CASE("utl::type_erased_object_storage stores an SBO object") {
    utl::type_erased_object_storage storage;
    auto& object = storage.emplace<SmallObject>(123);
    REQUIRE(storage.has_value());
    REQUIRE(static_cast<bool>(storage));
    REQUIRE(storage.type() == typeid(SmallObject));
    REQUIRE(storage.data() == &object);
    REQUIRE(object.value == 123);
    auto* ptr = static_cast<SmallObject*>(storage.data());
    REQUIRE(ptr == &object);
    REQUIRE(ptr->value == 123);
}

TEST_CASE("utl::type_erased_object_storage stores a heap object") {
    utl::type_erased_object_storage storage;
    auto& object = storage.emplace<LargeObject>(123);
    REQUIRE(storage.has_value());
    REQUIRE(storage.type() == typeid(LargeObject));
    REQUIRE(storage.data() == &object);
    REQUIRE(object.value == 123);
    auto* ptr = static_cast<LargeObject*>(storage.data());
    REQUIRE(ptr == &object);
    REQUIRE(ptr->value == 123);
}

TEST_CASE(
    "utl::type_erased_object_storage supports construction from a value") {
    SmallObject object{ 123 };
    utl::type_erased_object_storage storage{ std::move(object) };
    REQUIRE(storage.has_value());
    REQUIRE(storage.type() == typeid(SmallObject));
    auto* stored = static_cast<SmallObject*>(storage.data());
    REQUIRE(stored != nullptr);
    REQUIRE(stored->value == 123);
}

TEST_CASE("utl::type_erased_object_storage supports in-place construction") {
    utl::type_erased_object_storage storage{
        std::in_place_type<SmallObject>,
        123,
    };
    REQUIRE(storage.type() == typeid(SmallObject));
    auto* object = static_cast<SmallObject*>(storage.data());
    REQUIRE(object != nullptr);
    REQUIRE(object->value == 123);
}

TEST_CASE("utl::type_erased_object_storage reset destroys the object") {
    bool destroyed = false;
    {
        utl::type_erased_object_storage storage;
        storage.emplace<DestructionTracker>(destroyed);
        REQUIRE(storage.has_value());
        REQUIRE_FALSE(destroyed);
        storage.reset();
        REQUIRE(destroyed);
        REQUIRE_FALSE(storage.has_value());
        REQUIRE(storage.data() == nullptr);
        REQUIRE(storage.type() == typeid(void));
    }
    REQUIRE(destroyed);
}

TEST_CASE("utl::type_erased_object_storage destroys SBO objects") {
    bool destroyed = false;
    {
        utl::type_erased_object_storage storage;
        storage.emplace<DestructionTracker>(destroyed);
        REQUIRE_FALSE(destroyed);
    }
    REQUIRE(destroyed);
}

TEST_CASE("utl::type_erased_object_storage destroys heap objects") {
    bool destroyed = false;
    {
        // Make the object large enough to force heap storage.
        struct LargeDestructionTracker {
            char data[256]{};
            bool* destroyed;

            explicit LargeDestructionTracker(bool& destroyed):
                destroyed(&destroyed) {
                *this->destroyed = false;
            }

            ~LargeDestructionTracker() { *destroyed = true; }

            LargeDestructionTracker(LargeDestructionTracker&& other) noexcept:
                destroyed(other.destroyed) {
                other.destroyed = nullptr;
            }
        };

        utl::type_erased_object_storage storage;
        storage.emplace<LargeDestructionTracker>(destroyed);
        REQUIRE_FALSE(destroyed);
    }
    REQUIRE(destroyed);
}

TEST_CASE("utl::type_erased_object_storage supports move construction") {
    utl::type_erased_object_storage source;
    auto& object = source.emplace<SmallObject>(123);
    auto* original_pointer = &object;
    utl::type_erased_object_storage destination{ std::move(source) };
    REQUIRE_FALSE(source.has_value());
    REQUIRE(source.data() == nullptr);
    REQUIRE(destination.has_value());
    REQUIRE(destination.type() == typeid(SmallObject));
    auto* destination_pointer = static_cast<SmallObject*>(destination.data());
    REQUIRE(destination_pointer != nullptr);
    REQUIRE(destination_pointer->value == 123);
    // SBO means the object itself is moved into a new location.
    REQUIRE(destination_pointer != original_pointer);
}

TEST_CASE("utl::type_erased_object_storage supports heap move construction") {
    utl::type_erased_object_storage source;
    auto& object = source.emplace<LargeObject>(123);
    auto* original_pointer = &object;
    utl::type_erased_object_storage destination{ std::move(source) };
    REQUIRE_FALSE(source.has_value());
    REQUIRE(destination.has_value());
    REQUIRE(destination.type() == typeid(LargeObject));
    auto* destination_pointer = static_cast<LargeObject*>(destination.data());
    // Heap storage can simply transfer ownership of the pointer.
    REQUIRE(destination_pointer == original_pointer);
    REQUIRE(destination_pointer->value == 123);
}

TEST_CASE("utl::type_erased_object_storage supports move assignment") {
    utl::type_erased_object_storage source;
    source.emplace<SmallObject>(123);
    utl::type_erased_object_storage destination;
    destination.emplace<SmallObject>(456);
    destination = std::move(source);
    REQUIRE_FALSE(source.has_value());
    REQUIRE(destination.has_value());
    REQUIRE(destination.type() == typeid(SmallObject));
    auto* object = static_cast<SmallObject*>(destination.data());
    REQUIRE(object->value == 123);
}

TEST_CASE("utl::type_erased_object_storage supports heap move assignment") {
    utl::type_erased_object_storage source;
    source.emplace<LargeObject>(123);
    auto* source_pointer = static_cast<LargeObject*>(source.data());
    utl::type_erased_object_storage destination;
    destination.emplace<LargeObject>(456);
    destination = std::move(source);
    REQUIRE_FALSE(source.has_value());
    auto* destination_pointer = static_cast<LargeObject*>(destination.data());
    REQUIRE(destination_pointer == source_pointer);
    REQUIRE(destination_pointer->value == 123);
}

TEST_CASE(
    "utl::type_erased_object_storage move assignment destroys old value") {
    bool destination_destroyed = false;
    {
        utl::type_erased_object_storage source;
        source.emplace<SmallObject>(123);
        utl::type_erased_object_storage destination;
        destination.emplace<DestructionTracker>(destination_destroyed);
        destination = std::move(source);
        REQUIRE(destination_destroyed);
        REQUIRE(destination.has_value());
        REQUIRE(destination.type() == typeid(SmallObject));
    }

    REQUIRE(destination_destroyed);
}

TEST_CASE("utl::type_erased_object_storage can be reused with emplace") {
    utl::type_erased_object_storage storage;
    storage.emplace<SmallObject>(123);
    REQUIRE(storage.type() == typeid(SmallObject));
    REQUIRE(static_cast<SmallObject*>(storage.data())->value == 123);
    storage.emplace<LargeObject>(456);
    REQUIRE(storage.type() == typeid(LargeObject));
    REQUIRE(static_cast<LargeObject*>(storage.data())->value == 456);
    storage.emplace<SmallObject>(789);
    REQUIRE(storage.type() == typeid(SmallObject));
    REQUIRE(static_cast<SmallObject*>(storage.data())->value == 789);
}

TEST_CASE("utl::type_erased_object_storage handles construction exceptions") {
    utl::type_erased_object_storage storage;
    REQUIRE_THROWS_AS(storage.emplace<ThrowingConstructor>(),
                      std::runtime_error);
    REQUIRE_FALSE(storage.has_value());
    REQUIRE(storage.data() == nullptr);
    REQUIRE(storage.type() == typeid(void));
}

TEST_CASE(
    "utl::type_erased_object_storage does not use SBO for throwing moves") {
    static_assert(!std::is_nothrow_move_constructible_v<ThrowingMove>);

    utl::type_erased_object_storage storage;

    // This should succeed despite ThrowingMove having a throwing move
    // constructor because it is constructed directly on the heap.
    REQUIRE_NOTHROW(storage.emplace<ThrowingMove>());

    REQUIRE(storage.has_value());
    REQUIRE(storage.type() == typeid(ThrowingMove));
}

TEST_CASE("utl::type_erased_object_storage is move-only") {
    static_assert(
        !std::is_copy_constructible_v<utl::type_erased_object_storage>);
    static_assert(!std::is_copy_assignable_v<utl::type_erased_object_storage>);
    static_assert(
        std::is_move_constructible_v<utl::type_erased_object_storage>);
    static_assert(std::is_move_assignable_v<utl::type_erased_object_storage>);
    static_assert(
        std::is_nothrow_move_constructible_v<utl::type_erased_object_storage>);
    static_assert(
        std::is_nothrow_move_assignable_v<utl::type_erased_object_storage>);
}

TEST_CASE("utl::type_erased_object_storage const data access works") {
    utl::type_erased_object_storage storage;
    storage.emplace<SmallObject>(123);
    auto const& const_storage = storage;
    void const* data = const_storage.data();
    REQUIRE(data != nullptr);
    auto* object = static_cast<SmallObject const*>(data);
    REQUIRE(object->value == 123);
}

TEST_CASE("utl::type_erased_object_storage handles self move assignment") {
    utl::type_erased_object_storage storage;
    storage.emplace<SmallObject>(123);
    auto* original = static_cast<SmallObject*>(storage.data());
    storage = std::move(storage);
    REQUIRE(storage.has_value());
    REQUIRE(storage.type() == typeid(SmallObject));
    auto* object = static_cast<SmallObject*>(storage.data());
    REQUIRE(object == original);
    REQUIRE(object->value == 123);
}
