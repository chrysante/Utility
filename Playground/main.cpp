#include <iostream>
#include <algorithm>
#include <vector>



int main() {
	std::vector<int> v = { 0, 1, 3, 4 };
	auto range = std::equal_range(v.begin(), v.end(), 2);
	for (auto i = range.first; i != range.second; ++i) {
		std::cout << *i << std::endl;
	}
	std::cout << std::boolalpha;
	std::cout << (range.first == v.end()) << std::endl;
	std::cout << (range.second == v.end()) << std::endl;
	
	std::cout << std::to_address(range.first) << std::endl;
	std::cout << std::to_address(range.second) << std::endl;
	std::cout << std::to_address(v.end()) << std::endl;
	
}
