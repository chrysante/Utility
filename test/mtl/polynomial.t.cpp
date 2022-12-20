//#include <catch/catch2.hpp>
//
//#include <mtl/mtl.hpp>
//
//namespace {
//	template <typename T, std::size_t N>
//	bool set_equal(std::array<T, N> const& a, std::array<T, N> const& b) {
//		for (auto&& _a: a) {
//			if (std::find(b.begin(), b.end(), _a) == b.end()) {
//				return false;
//			}
//		}
//		return true;
//	}
//}
//
//TEST_CASE("quadratic roots") {
//	SECTION("real coeffs") {
//		std::array const roots = mtl::solve_quadratic(-3, 2);
//		CHECK(roots[0] == 2);
//		CHECK(roots[1] == 1);
//	}
//	
//	SECTION("complex coeffs") {
//		using namespace mtl::complex_literals;
//		std::array const roots = mtl::solve_quadratic(0, 1 + 0_i);
//		CHECK(roots[0] == mtl::approx{  1_i });
//		CHECK(roots[1] == mtl::approx{ -1_i });
//	}
//}
//
//
//TEST_CASE("cubic roots") {
//	return;
//	SECTION("") {
//		std::array const roots = mtl::solve_cubic<float>(-3, 0, 2);
//		CHECK(roots[0] == 1);
//		CHECK(roots[1] == 1 + std::sqrt(3.f));
//		CHECK(roots[1] == 1 - std::sqrt(3.f));
//	}
//	
//}
