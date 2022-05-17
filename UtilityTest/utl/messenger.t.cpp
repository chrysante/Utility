#include "Catch2.hpp"

#include <utl/messenger.hpp>

namespace {
	
	struct TestMessage: utl::message<TestMessage> {
		TestMessage(int payload): payload(payload) {}
		int payload;
	};
	
}

TEST_CASE("messenger") {
	
	utl::messenger m;
	
	int testValue = 0;
	{
		utl::listener_id_bag ids;
		ids.insert(m.register_listener([&](TestMessage msg){
			testValue = msg.payload;
		}));
		
		m.send_message(TestMessage{ -1 });
		CHECK(testValue == -1);
	}
	
	m.send_message(TestMessage{ -2 });
	CHECK(testValue == -1);
}

TEST_CASE("messenger ignoring register return value") {
	utl::messenger m;
	
	int testValue = 0;
	
	(void)m.register_listener([&](TestMessage msg){
		testValue = msg.payload;
	});
	
	m.send_message(TestMessage{ -1 });
	CHECK(testValue == 0); // listener should have been removed immediately because we are discarding its id
}

TEST_CASE("buffered_messenger") {
	
	utl::buffered_messenger m;
	
	int testValue = 0;
	{
		utl::listener_id_bag ids;
		ids.insert(m.register_listener([&](TestMessage msg){
			testValue = msg.payload;
		}));
		
		m.send_message(TestMessage{ -1 });
		CHECK(testValue == 0);
		m.flush();
		CHECK(testValue == -1);
		CHECK(m.buffered_messages() == 0);
	}
	
	m.send_message(TestMessage{ -2 });
	m.flush();
	CHECK(testValue == -1);
}
