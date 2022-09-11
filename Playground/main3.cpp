#define _UTL_MAP_DEBUG_PRINT

#include <utl/map.hpp>
#include <string>
#include <iostream>

static int _main() {
	
	utl::map<std::string, std::string> m;
	
	m.insert("bob", "ross");
	m.insert("christian", "lindner");
	m.insert("angela", "merkel");
	
	m.insert("Turanga", "Leela");
	m.insert("Bender", "Rodriguez");
	m.insert("Hubert", "Farnsworth");
	
	if (auto lastName = m["bob"]) {
		std::cout << lastName.get() << std::endl;
	}
	if (auto lastName = m["angela"]) {
		std::cout << lastName.get() << std::endl;
	}
	if (auto lastName = m["christian"]) {
		std::cout << lastName.get() << std::endl;
	}
	
	
	m.__debug_print();
	
	return 0;
}
