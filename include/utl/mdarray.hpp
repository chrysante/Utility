#pragma once

#include <array>
#include <cstddef>

#include "../mtl/ext.hpp"
#include "../mtl/vector.hpp"
#include "__base.hpp"
#include "__function_objects.hpp"
#include "common.hpp"

_UTL_SYSTEM_HEADER_

namespace utl {

template <typename Container, std::size_t Dimensions, typename = make_type_sequence<std::size_t, Dimensions>>
class mdarray;

template <typename Container, std::size_t Dimensions, typename... SizeT>
class mdarray<Container, Dimensions, type_sequence<SizeT...>> {
public:
    using container_type             = Container;
    using value_type                 = typename Container::value_type;
    using size_type                  = mtl::vector<std::size_t, Dimensions>;
    static constexpr auto dimensions = Dimensions;

public:
    mdarray() = default;
    mdarray(size_type size): __size(size), __cont(size.fold(utl::multiplies)) {}
    mdarray(SizeT... size): mdarray(size_type{ size... }) {}

    size_type size() const { return __size; }

    value_type const& operator()(size_type index) const& {
        __utl_expect(mtl::map(index, __size, utl::less).fold(utl::logical_and));
        return (*this)[__expand_index(index)];
    }
    value_type& operator()(size_type index) & { return utl::as_mutable(utl::as_const(*this)(index)); }
    value_type const& operator()(SizeT... index) const& { return (*this)({ index... }); }
    value_type& operator()(SizeT... index) & { return utl::as_mutable(utl::as_const(*this)(index...)); }

    value_type const& operator[](std::size_t index) const& { return __cont[index]; }
    value_type& operator[](std::size_t index) & { return utl::as_mutable(utl::as_const(*this)[index]); }

    value_type const& operator[](size_type index) const& { return (*this)(index); }
    value_type& operator[](size_type index) & { return (*this)(index); }

    void resize(size_type new_size) {
        mdarray new_inst(new_size);
        for (auto i : utl::iota(mtl::map(__size, new_size, utl::min))) {
            new_inst(i) = (*this)(i);
        }
        *this = new_inst;
    }
    void resize(SizeT... new_size) { resize({ new_size... }); }

    auto begin() { return __cont.begin(); }
    auto begin() const { return __cont.begin(); }
    auto end() { return __cont.end(); }
    auto end() const { return __cont.end(); }

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
    size_type __size = 0;
    container_type __cont;
};

} // namespace utl
