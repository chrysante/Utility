#pragma once

#include "__base.hpp"
_MTL_SYSTEM_HEADER_

#include "__common.hpp"
#include "__complex.hpp"
#include <array>
#include <cmath>


namespace mtl {
	
	/**
	 solve_quadratic
	 solves the equation x^2 + px + q = 0
	 */
	template <typename T, typename U>
	std::array<__mtl_to_complex_t<__mtl_floatify(__mtl_promote(T, U))>, 2> solve_quadratic(T const& __p, U const& __q) {
		using F = __mtl_floatify(__mtl_promote(T, U));
		using C = __mtl_to_complex_t<F>;
		
		F const p = F(__p);
		F const q = F(__q);
		
		F const neg_p_halfs = -p / F(2);
		F const discriminant = p * p / F(4) - q;
		
		if constexpr (is_complex<F>::value) {
			F const root_d = _VMTL::sqrt(discriminant);
			return { neg_p_halfs + root_d, neg_p_halfs - root_d };
		}
		else {
			F const root_d = std::sqrt(std::fabs(discriminant));
			if (discriminant >= 0) {
				return { neg_p_halfs + root_d, neg_p_halfs - root_d };
			}
			else {
				return { C{ neg_p_halfs, root_d }, C{ neg_p_halfs, -root_d } };
			}
		}
	}
	
	/**
	 solve_quadratic
	 solves the equation ax^2 + bx + c = 0
	 */
	template <typename T, typename U, typename V>
	std::array<__mtl_to_complex_t<__mtl_floatify(__mtl_promote(T, U, V))>, 2> solve_quadratic(T const& __a, U const& __b, V const& __c) {
		using F = __mtl_floatify(__mtl_promote(T, U, V));
		__mtl_expect(__a != T(0));
		return solve_quadratic(__b / F(__a), __c / F(__a));
	}
	
	/**
	 solve_cubic_numeric
	 solves the equation x^3 + ax^2 + bx + c = 0
	 */
//	template <std::arithmetic T, std::arithmetic U, std::arithmetic V>
//	std::array<__mtl_to_complex_t<__mtl_floatify(__mtl_promote(T, U, V))>, 3> solve_cubic_numeric(T const& __a, U const& __b, V const& __c) {
//		using F = __mtl_floatify(__mtl_promote(T, U, V));
//		__mtl_expect(__a != T(0));
//		return solve_quadratic(__b / F(__a), __c / F(__a));
//	}
	
}








namespace mtl {
	
#define	TwoPi  6.28318530717958648
const double eps = 1e-14;
	
	// x - array of size 2
	// return 2: 2 real roots x[0], x[1]
	// return 0: pair of complex roots: x[0]±i*x[1]
	
	template <typename T>
	auto __mtl_root3(T x) {
		using F = __mtl_floatify(T);
		return std::copysign(std::pow(std::abs(x), F(1) / F(3)), x);
	}
	
//	template <typename T>
//	std::array<complex<__mtl_floatify(T)>, 2> solve_quadratic(T a, T b) {
//		using F = __mtl_floatify(T);
//		using std::sqrt;
//		F const D = F(0.25) * a * a - b;
//		if (D >= 0) {
//			D = sqrt(D);
//			return {
//				F(-0.5) * a + D,
//				F(-0.5) * a - D
//			};
//		}
//		F const real = F(-0.5) * a;
//		F const imag = sqrt(-D);
//		return {
//			complex<F>(real, imag),
//			complex<F>(real, -imag),
//		};
//	}
	
	template <typename T>
	std::array<complex<__mtl_floatify(T)>, 3> solve_cubic(T a, T b, T c) {	// solve cubic equation x^3 + a*x^2 + b*x + c = 0
		using F = __mtl_floatify(T);
		F const a2 = a * a;
		F const q  = (a2 - 3 * b) / 9;
		F const r  = (a * (2 * a2 - 9 * b) + 27 * c) / 54;
		// equation y^3 - 3q*y + r/2 = 0 where x = y-a/3
		using std::sqrt;
		if (std::fabs(q) < eps) {		// y^3 =-r/2	!!! Thanks to John Fairman <jfairman1066@gmail.com>
			if (std::fabs(r) < eps) {	// three identical roots
				F const result = -a / 3;
				return { result, result, result };
			}
			// y^3 =-r/2
			F const real_root = __mtl_root3(-r / 2);
			F const real = real_root * F(0.5);
			F const imag = real_root * sqrt(F(3)) / 2;
			return { real_root, { real, imag }, { real, -imag } };
		}
		// now favs(q)>eps
		F const r2 = r * r;
		F const q3 = q * q * q;
		if (r2 <= (q3 + eps)) {
			F t = r / std::sqrt(q3);
			if (t < -1)
				t = -1;
			if (t >  1)
				t = 1;
			t = std::acos(t);
			a /= 3;
			F const p = -2 * sqrt(q);
			F const real_root = p * std::cos(t / 3) - a;
			F const real = p * std::cos((t + TwoPi) / 3) - a;
			F const imag = p * std::cos((t - TwoPi) / 3) - a;
			return { real_root, { real, imag }, { real, -imag } };
		}
		else {
			//A =-pow(fabs(r)+sqrt(r2-q3),1./3);
			F A = -__mtl_root3(fabs(r) + sqrt(r2 - q3));
			if (r < 0)
				A = -A;
			F B = (A == 0 ? 0 : q / A);

			a /= 3;
			F const real_root = A + B - a;
			F const real = F(-0.5) * (A + B) - a;
			F const imag = F(0.5) * sqrt(F(3)) * (A - B);
			
			return { real_root, { real, imag }, { real, -imag } };
		}
	}
	
}
