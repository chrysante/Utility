#include <utl/common.hpp>
#include <utl/vector.hpp>
#include <stack>
#include <iostream>

struct M {
	void f() {}
};

struct X {
protected: M m;
};

struct Y: X {
	static M& getMember(X& x) { return x.*&Y::m; }
};

int main() {

	X x;
	Y::getMember(x);
	
	std::stack<int, utl::vector<int>> S;
	S.push(0);
	S.push(1);
	S.push(2);
	
	for (auto&& i: utl::get_container(utl::as_const(S))) {
		std::cout << i << std::endl;
	}
	
}
