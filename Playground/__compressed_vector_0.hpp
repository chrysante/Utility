#pragma once


#include <mtl/mtl.hpp>

namespace mtl
{

	template <std::size_t N, int E = std::countr_zero(std::max(std::size_t{ 8 }, std::bit_ceil(N)))>
	struct __uint_least;

	template <std::size_t N>
	struct __uint_least<N, 3> { using type = std::uint8_t; };
	template <std::size_t N>
	struct __uint_least<N, 4> { using type = std::uint16_t; };
	template <std::size_t N>
	struct __uint_least<N, 5> { using type = std::uint32_t; };
	template <std::size_t N>
	struct __uint_least<N, 6> { using type = std::uint64_t; };

	template <std::size_t N>
	using __uint_least_t = typename __uint_least<N>::type;

	static_assert(std::is_same_v<mtl::__uint_least_t<0>, std::uint8_t>);
	static_assert(std::is_same_v<mtl::__uint_least_t<7>, std::uint8_t>);
	static_assert(std::is_same_v<mtl::__uint_least_t<8>, std::uint8_t>);
	static_assert(std::is_same_v<mtl::__uint_least_t<9>, std::uint16_t>);
	static_assert(std::is_same_v<mtl::__uint_least_t<16>, std::uint16_t>);
	static_assert(std::is_same_v<mtl::__uint_least_t<17>, std::uint32_t>);
	static_assert(std::is_same_v<mtl::__uint_least_t<32>, std::uint32_t>);
	static_assert(std::is_same_v<mtl::__uint_least_t<33>, std::uint64_t>);
	static_assert(std::is_same_v<mtl::__uint_least_t<64>, std::uint64_t>);

	template <std::size_t N, std::floating_point F>
	constexpr __uint_least_t<N> deflate(F f) {
		using __uint = __uint_least_t<N>;
		constexpr __uint _max = ~(__uint(-1) << N);
		return std::clamp(f, F(0), F(1)) * _max;
	}

	template <std::size_t N, std::floating_point F = double, std::unsigned_integral T>
	constexpr F inflate(T x) {
		constexpr T _max = ~(T(-1) << N);
		return (F)x / _max;
	}

	template <typename>
	struct __compressed_vector_base;

	template <std::size_t I, std::size_t J>
	struct __compressed_vector_base<std::index_sequence<I, J>> {
		__compressed_vector_base() = default;
		template <std::floating_point F, vector_options O>
		constexpr __compressed_vector_base(vector2<F, O> const& v):
			__x(deflate<I>(v.__mtl_at(0))),
			__y(deflate<J>(v.__mtl_at(1)))
		{}
		
		template <std::floating_point F, vector_options O>
		constexpr operator vector2<F, O>() const {
			return {
				__mtl_get<0, F>(),
				__mtl_get<1, F>()
			};
		}
		
		template <std::size_t Index, typename F>
		constexpr F __mtl_get() const {
				 if constexpr (Index == 0) { return inflate<I, F>(__x); }
			else                           { return inflate<J, F>(__y); }
		}
		template <std::size_t Index, typename F>
		constexpr void __mtl_set(F v) {
				 if constexpr (Index == 0) { __x = deflate<I>(v); }
			else                           { __y = deflate<J>(v); }
		}
		
		template <typename F>
		constexpr F __mtl_vget(std::size_t index) const {
				 if (index == 0) { return __mtl_get<0, F>(); }
			else                 { return __mtl_get<1, F>(); }
		}
		
		__uint_least_t<I> __x: I;
		__uint_least_t<J> __y: J;
	};

	template <std::size_t I, std::size_t J, std::size_t K>
	struct __compressed_vector_base<std::index_sequence<I, J, K>> {
		__compressed_vector_base() = default;
		template <std::floating_point F, vector_options O>
		constexpr __compressed_vector_base(vector3<F, O> const& v):
			__x(deflate<I>(v.__mtl_at(0))),
			__y(deflate<J>(v.__mtl_at(1))),
			__z(deflate<K>(v.__mtl_at(2)))
		{}
		
		template <std::floating_point F, vector_options O>
		constexpr operator vector3<F, O>() const {
			return {
				__mtl_get<0, F>(),
				__mtl_get<1, F>(),
				__mtl_get<2, F>()
			};
		}
		
		template <std::size_t Index, typename F>
		constexpr F __mtl_get() const {
				 if constexpr (Index == 0) { return inflate<I, F>(__x); }
			else if constexpr (Index == 1) { return inflate<J, F>(__y); }
			else                           { return inflate<K, F>(__z); }
		}
		template <std::size_t Index, typename F>
		constexpr void __mtl_set(F v) {
				 if constexpr (Index == 0) { __x = deflate<I>(v); }
			else if constexpr (Index == 1) { __y = deflate<J>(v); }
			else                           { __z = deflate<K>(v); }
		}
		
		template <typename F>
		constexpr F __mtl_vget(std::size_t index) const {
				 if (index == 0) { return __mtl_get<0, F>(); }
			else if (index == 1) { return __mtl_get<1, F>(); }
			else                 { return __mtl_get<2, F>(); }
		}
		
		__uint_least_t<I> __x: I;
		__uint_least_t<J> __y: J;
		__uint_least_t<K> __z: K;
	};

	template <std::size_t I, std::size_t J, std::size_t K, std::size_t L>
	struct __compressed_vector_base<std::index_sequence<I, J, K, L>> {
		__compressed_vector_base() = default;
		template <std::floating_point F, vector_options O>
		constexpr __compressed_vector_base(vector4<F, O> const& v):
			__x(deflate<I>(v.__mtl_at(0))),
			__y(deflate<J>(v.__mtl_at(1))),
			__z(deflate<K>(v.__mtl_at(2))),
			__w(deflate<L>(v.__mtl_at(3)))
		{}
		
		template <std::floating_point F, vector_options O>
		constexpr operator vector4<F, O>() const {
			return {
				__mtl_get<0, F>(),
				__mtl_get<1, F>(),
				__mtl_get<2, F>(),
				__mtl_get<3, F>()
			};
		}
		
		template <std::size_t Index, typename F>
		constexpr F __mtl_get() const {
				 if constexpr (Index == 0) { return inflate<I, F>(__x); }
			else if constexpr (Index == 1) { return inflate<J, F>(__y); }
			else if constexpr (Index == 2) { return inflate<K, F>(__z); }
			else                           { return inflate<L, F>(__w); }
		}
		template <std::size_t Index, typename F>
		constexpr void __mtl_set(F v) {
				 if constexpr (Index == 0) { __x = deflate<I>(v); }
			else if constexpr (Index == 1) { __y = deflate<J>(v); }
			else if constexpr (Index == 2) { __z = deflate<K>(v); }
			else                           { __w = deflate<L>(v); }
		}
		
		template <typename F>
		constexpr F __mtl_vget(std::size_t index) const {
				 if (index == 0) { return __mtl_get<0, F>(); }
			else if (index == 1) { return __mtl_get<1, F>(); }
			else if (index == 2) { return __mtl_get<2, F>(); }
			else                 { return __mtl_get<3, F>(); }
		}
		
		__uint_least_t<I> __x: I;
		__uint_least_t<J> __y: J;
		__uint_least_t<K> __z: K;
		__uint_least_t<L> __w: L;
	};

	template <std::size_t... Widths> requires ((Widths + ...) % CHAR_BIT == 0)
	struct compressed_vector: __compressed_vector_base<std::index_sequence<Widths...>> {
		using __base = __compressed_vector_base<std::index_sequence<Widths...>>;
		
		using __base::__base;
		
		static constexpr std::size_t size() { return sizeof...(Widths); }
		double operator[](std::size_t i) const { return this->template __mtl_vget<double>(i); }
	};

	using r11g11b10 = compressed_vector<11, 11, 10>;
	using rgba8 = compressed_vector<8, 8, 8, 8>;
}
