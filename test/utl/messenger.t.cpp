#include <thread>

#include <catch2/catch_test_macros.hpp>

#include <utl/messenger.hpp>

TEST_CASE("test messenger", "[messenger]") {
    utl::messenger m;
    int reference = 0;
    int reciever_count = 0;
    auto l1 = m.listen<int>([&](int i) {
        CHECK(i == reference);
        ++reciever_count;
    });
    reference = 1;
    m.send(1);
    auto l2 = m.listen([&](int i) {
        CHECK(i == reference);
        ++reciever_count;
    });
    CHECK(reciever_count == 1);
    reciever_count = 0;
    reference = 2;
    m.send(2);
    CHECK(reciever_count == 2);
    reciever_count = 0;
    m.unlisten(l2);
    reference = 3;
    m.send(3);
    CHECK(reciever_count == 1);
    reciever_count = 0;
    m.unlisten(l1);
    reference = 4;
    m.send(4);
    CHECK(reciever_count == 0);
    reciever_count = 0;
}

TEST_CASE("test buffered_messenger", "[messenger]") {
    utl::buffered_messenger m;
    int testValue = 0;
    auto l = m.listen([&](int msg) { testValue = msg; });
    m.send(-1);
    CHECK(testValue == 0);
    m.flush();
    CHECK(testValue == -1);
    m.unlisten(l);
    m.send(-2);
    m.flush();
    CHECK(testValue == -1);
}

TEST_CASE("test emitter/receiver", "[messenger]") {
    auto m = std::make_shared<utl::buffered_messenger>();
    utl::emitter<utl::buffered_messenger> e(m);
    utl::receiver<utl::buffered_messenger> r(m);
    int value = 0;
    r.listen([&](int i) { value = i; });
    e.send(-1);
    CHECK(value == 0);
    m->flush();
    CHECK(value == -1);
}

TEST_CASE("recursive send", "[messenger]") {
    utl::messenger m;
    bool second_called = false;
    enum Message { First, Second };
    auto id = m.listen([&](Message msg) {
        if (msg == First)
            m.send(Second);
        else if (msg == Second)
            second_called = true;
    });
    m.send(First);
    CHECK(second_called);
}

TEST_CASE("concurrent access", "[messenger]") {
    utl::messenger m;
    std::atomic<bool> running = true;
    std::atomic<int> counter = 0;
    enum Message { Ping };
    std::thread sender([&] {
        while (running) {
            m.send(Ping);
            std::this_thread::yield();
        }
    });
    std::thread listener_manager([&] {
        while (running) {
            auto id = m.listen([&](Message msg) { counter++; });
            m.unlisten(id);
            std::this_thread::yield();
        }
    });
    while (counter < 500)
        std::this_thread::yield();
    running = false;
    sender.join();
    listener_manager.join();
    CHECK(counter >= 500);
}

TEST_CASE("parallel flush", "[messenger]") {
    auto m = std::make_shared<utl::buffered_messenger>();
    std::atomic<int> count = 0;
    utl::receiver<utl::buffered_messenger> r(m);
    enum class Message : int;
    r.listen([&](Message) { ++count; });
    m->send(Message{});
    m->send(Message{});
    std::thread flush1([&] { m->flush(); });
    std::thread flush2([&] { m->flush(); });
    flush1.join();
    flush2.join();
    CHECK(count == 2);
}

TEST_CASE("send from buffered message", "[messenger]") {
    auto m = std::make_shared<utl::buffered_messenger>();
    utl::receiver<utl::buffered_messenger> r(m);
    enum Message { First, Second, Third };
    int count = 0;
    r.listen([&](Message msg) {
        if (msg == First)
            m->send(Second);
        if (msg == Second)
            m->send_now(Third);
    });
    r.listen([&](Message msg) { ++count; });
    m->send(First);
    CHECK(count == 0);
    m->flush();
    CHECK(count == 1);
    m->flush();
    CHECK(count == 3);
    m->flush();
    CHECK(count == 3);
}
