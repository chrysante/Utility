//
//  test.cpp
//  Playground
//
//  Created by chrysante on 16.03.22.
//

#include "test.hpp"

namespace X {
	template <typename T>
	void Y<T>::g() {}
	template <typename T>
	void g(Y<T>) {}
	template struct Y<int>;
}
