#pragma once

#include <iosfwd>
#include <memory>



namespace utl_test {
	
	struct StdoutReroute {
		StdoutReroute();
		~StdoutReroute();
	private:
		std::unique_ptr<std::stringstream> _discard;
		std::reference_wrapper<std::ostream> _saved;
	};
	
}
