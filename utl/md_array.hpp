#pragma once

#include "__base.hpp"
_UTL_SYSTEM_HEADER_


#include "__common.hpp"

#include <cstddef>
#include <array>

#include <mtl/vector.hpp>
#include <mtl/ext.hpp>

namespace utl {

	template <typename Container,
			  std::size_t Dimensions,
			  typename = make_type_sequence<std::size_t, Dimensions>>
	class md_array;

	template <typename Container, std::size_t Dimensions, typename... SizeT>
	class md_array<Container, Dimensions, type_sequence<SizeT...>> {
	public:
		using container_type = Container;
		using value_type = typename Container::value_type;
		using size_type = mtl::vector<std::size_t, Dimensions>;
		static constexpr auto dimensions = Dimensions;
		
	public:
		md_array(size_type size):
			__size(size),
			__cont(size.fold(utl::multiplies))
		{}
		
		size_type size() const { return __size; }
		
		value_type const& operator()(size_type index) const& {
			UTL_WITH_INDEX_SEQUENCE((I, Dimensions), {
				(utl_expect(index[I] < __size[I]), ...);
			});
			return (*this)[__expand_index(index)];
		}
		value_type& operator()(size_type index)& {
			return utl::as_mutable(utl::as_const(*this)(index));
		}
		value_type const& operator()(SizeT... index) const& {
			return (*this)({ index... });
		}
		value_type& operator()(SizeT... index)& {
			return utl::as_mutable(utl::as_const(*this)(index...));
		}
		
		value_type const& operator[](std::size_t index) const& {
			return __cont[index];
		}
		value_type& operator[](std::size_t index)& {
			return utl::as_mutable(utl::as_const(*this)[index]);
		}
		
		void resize(size_type new_size) {
			md_array new_inst(new_size);
			for (auto i: utl::iota(mtl::map(__size, new_size, utl::min))) {
				new_inst(i) = (*this)(i);
			}
			*this = new_inst;
		}
		void resize(SizeT... new_size) { resize({ new_size... }); }
		
	private:
		std::size_t __expand_index(size_type index) const {
			std::size_t result = index[0];
			for (std::size_t i = 1; i < Dimensions; ++i) {
				result *= __size[i];
				result += index[i];
			}
			return result;
		}
		
	private:
		size_type __size;
		container_type __cont;
	};

	
}

