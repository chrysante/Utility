#include "StdoutReroute.hpp"


#include <utl/stdio.hpp>

utl_test::StdoutReroute::StdoutReroute():
	_discard(std::make_unique<std::stringstream>()),
	_saved(*utl::set_global_output_stream(*_discard)._stream)
{
	
}

utl_test::StdoutReroute::~StdoutReroute() {
	utl::set_global_output_stream(_saved);
}
