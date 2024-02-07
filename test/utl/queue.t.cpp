#include <catch2/catch_test_macros.hpp>
#include <utl/queue.hpp>

TEST_CASE("empty queue") {
    utl::queue<int, 3> q;
    CHECK(q.empty());
    q.push(1);
    q.push(2);
    q.push(3);
    CHECK(q.size() == 3);
    CHECK(q.pop() == 1);
    CHECK(q.pop() == 2);
    CHECK(q.size() == 1);
    CHECK(q.front() == 3);
    q.push(1);
}

TEST_CASE("queue 2") {
    utl::queue<int> q = { 1, 2, 3 };
    SECTION("Init list") {
        CHECK(q.size() == 3);
        CHECK(q.pop() == 1);
        CHECK(q.pop() == 2);
        CHECK(q.pop() == 3);
        CHECK(q.empty());
    }
}
