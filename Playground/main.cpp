#include <iostream>

#include "utl/__common.hpp"
#include "dispatch_queue.hpp"
#include "fancy_debug.hpp"
#include "utl/md_array.hpp"

#define MyAssert(...) UTL_FANCY_ASSERT("My Module", 2, assertion, __VA_ARGS__)



int main(int argc, const char * argv[]) {
	
	utl::dispatch_queue q;
	
	int x = 0;
	
	
	
	
	MyAssert(x > 0);
	MyAssert(x > 0, "Message");
	MyAssert(audit, x > 0);
	MyAssert(audit, x > 0, "Message");
	
	return 0;
}
