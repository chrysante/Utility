#include "Catch2.hpp"

#include <mtl/mtl.hpp>


TEST_CASE("mtl::rgb_to_hsv") {
	using namespace Catch::literals;
	
	CHECK(mtl::rgb_to_hsv(mtl::float3(1, 0, 0)) == mtl::float3(0, 1, 1));
	CHECK(mtl::rgb_to_hsv(mtl::float3(1, 1, 0)) == mtl::float3(1.0 / 6.0, 1, 1));
	CHECK(mtl::rgb_to_hsv(mtl::float3(1, 1, 1)) == mtl::float3(0, 0, 1));
	CHECK(mtl::rgb_to_hsv(mtl::float3(0, 0, 0)) == mtl::float3(0, 0, 0));
//	CHECK(mtl::rgb_to_hsv(mtl::float3(0, 0, 1)) == mtl::float3(4.0 / 6.0, 1, 1));
	CHECK(mtl::rgb_to_hsv(mtl::float3(0.5))     == mtl::float3(0, 0, 0.5));
	
	
	CHECK(mtl::hsv_to_rgb(mtl::float3(0, 1, 1))         == mtl::float3(1, 0, 0));
	CHECK(mtl::hsv_to_rgb(mtl::float3(1.0 / 6.0, 1, 1)) == mtl::float3(1, 1, 0));
	CHECK(mtl::hsv_to_rgb(mtl::float3(0, 0, 1))         == mtl::float3(1, 1, 1));
	CHECK(mtl::hsv_to_rgb(mtl::float3(0, 0, 0))         == mtl::float3(0, 0, 0));
	CHECK(mtl::hsv_to_rgb(mtl::float3(4.0 / 6.0, 1, 1)) == mtl::float3(0, 0, 1));
	CHECK(mtl::hsv_to_rgb(mtl::float3(0, 0, 0.5))       == mtl::float3(0.5));
}
