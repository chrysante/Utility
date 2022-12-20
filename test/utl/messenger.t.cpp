#include <catch/catch2.hpp>

#include <utl/messenger.hpp>


TEST_CASE("messenger") {
	utl::messenger m;
	
	int reference = 0;
	int reciever_count = 0;
	
	auto l1 = m.listen<int>([&](int i) {
		CHECK(i == reference);
		++reciever_count;
	});
	
	reference = 1;
	m.send(1);
	
	// notice no <int>
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

TEST_CASE("buffered_messenger") {
	utl::buffered_messenger m;
	
	int testValue = 0;
		
	auto l = m.listen([&](int msg) {
		testValue = msg;
	});
	
	m.send(-1);
	CHECK(testValue == 0);
	m.flush();
	CHECK(testValue == -1);
	CHECK(m.buffered_messages() == 0);

	m.unlisten(l);
	
	m.send(-2);
	m.flush();
	CHECK(testValue == -1);
}

TEST_CASE("emitter/reciever") {
	auto m = std::make_shared<utl::buffered_messenger>();
	
	utl::emitter<utl::buffered_messenger> e(m);
	utl::reciever<utl::buffered_messenger> r(m);
	
	int value = 0;
	
	r.listen([&](int i){
		value = i;
	});
	
	e.send(-1);
	CHECK(value == 0);
	m->flush();
	CHECK(value == -1);
}
