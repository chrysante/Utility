//
//  test.hpp
//  Playground
//
//  Created by chrysante on 16.03.22.
//

#ifndef test_hpp
#define test_hpp

#include <stdio.h>

#endif /* test_hpp */


namespace X {
	template <typename>
	struct Y {
		friend void f(Y);
		void g();
	};
}
