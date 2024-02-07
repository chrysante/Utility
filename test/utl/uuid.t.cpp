#include <catch2/catch_test_macros.hpp>
#include <utl/uuid.hpp>

TEST_CASE("uuid Serialize") {
    for (int i = 0; i < 50; ++i) {
        utl::uuid const original = utl::uuid::generate();
        std::string const text = original.to_string();
        utl::uuid const read = utl::uuid::from_string(text);
        CHECK(read == original);
    }
}
