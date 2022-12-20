#include <catch/catch2.hpp>

#include <utl/stack.hpp>

TEST_CASE("stack", "[stack]") {
    utl::stack<int> s;
    s.push(0);
    s.push(1);
    s.push(6);
    s.push(8);
    CHECK(s.pop() == 8);
    CHECK(s.pop() == 6);
    CHECK(s.pop() == 1);
    CHECK(s.pop() == 0);
}
