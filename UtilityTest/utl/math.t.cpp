#include "Catch2.hpp"

#include <vector>
#include <random>
#include <concepts>

#include <utl/utility.hpp>

TEST_CASE("round_up", "[math]") {
    CHECK(utl::round_up(12u, 4) == 12);
    CHECK(utl::round_up(13u, 4) == 16);
    CHECK(utl::round_up(0u, 3) == 0);
    CHECK(utl::round_up(3u, 3) == 3);
    CHECK(utl::round_up(12u, 1) == 12);
    
    CHECK(utl::round_up_pow_two(12u, 4) == 12);
    CHECK(utl::round_up_pow_two(13u, 4) == 16);
    CHECK(utl::round_up_pow_two(12u, 1) == 12);
}

TEST_CASE("round_down", "[math]") {
    CHECK(utl::round_down(12u, 4) == 12);
    CHECK(utl::round_down(13u, 4) == 12);
    CHECK(utl::round_down(0u, 3) == 0);
    CHECK(utl::round_down(3u, 3) == 3);
    CHECK(utl::round_down(12u, 1) == 12);
    
    CHECK(utl::round_down_pow_two(12u, 4) == 12);
    CHECK(utl::round_down_pow_two(13u, 4) == 12);
    CHECK(utl::round_down_pow_two(12u, 1) == 12);
}

TEST_CASE("fast_mod_pow_two", "[math]") {
    CHECK(utl::fast_mod_pow_two(5u, 2) == 1);
    CHECK(utl::fast_mod_pow_two(13u, 4) == 1);
    CHECK(utl::fast_mod_pow_two(515u, 32) == 3);
    
    CHECK(utl::fast_mod_pow_two(512u, 32) == 0);
    CHECK(utl::fast_mod_pow_two(0u, 32) == 0);
    CHECK(utl::fast_mod_pow_two(32u, 32) == 0);
}

TEST_CASE("fast_div_pow_two", "[math]") {
    CHECK(utl::fast_div_pow_two(5u, 2) == 2);
    CHECK(utl::fast_div_pow_two(13u, 4) == 3);
    CHECK(utl::fast_div_pow_two(10u, 4) == 2);
    CHECK(utl::fast_div_pow_two(12u, 4) == 3);
}

static auto makeTestData(std::size_t count, std::invocable<std::mt19937_64&> auto f) {
    std::mt19937_64 rng(std::random_device{}());
    using T = std::invoke_result_t<decltype(f), decltype((rng))>;
    std::vector<T> result;
    result.reserve(512);
    for (int i = 0; i < count; ++i) {
        result.push_back(f(rng));
    }
    return result;
}

TEMPLATE_TEST_CASE("log2", "[math]", int, long, unsigned int, unsigned long) {
    auto const digits = std::numeric_limits<TestType>::digits;
    auto const data = makeTestData(512, [dist = std::uniform_int_distribution<TestType>(0, digits - 1)](auto& rng) mutable {
        return dist(rng);
    });
    
    for (auto x : data) {
        CHECK(utl::log2(TestType(1) << x) == x);
    }
}

TEMPLATE_TEST_CASE("ipow", "[math]", std::int64_t) {
    std::uniform_int_distribution<TestType> distBase(0, 30);
    std::uniform_int_distribution<int> distExp(0, 10);
    auto const data = makeTestData(512, [&](auto& rng) {
        return std::pair(distBase(rng), distExp(rng));
    });
    
    for (auto [base, exp] : data) {
        CHECK(utl::ipow(base, exp) == (TestType)std::pow(base, exp));
    }
}
