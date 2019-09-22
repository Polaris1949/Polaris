// Bit memory resource management -*- C++ -*-

// Copyright (C) 2004-2018 Free Software Foundation, Inc.
//
// This file is part of the Polaris C++ Library.  This library is free
// software; you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the
// Free Software Foundation; either version 3, or (at your option)
// any later version.

// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// Under Section 7 of GPL version 3, you are granted additional
// permissions described in the GCC Runtime Library Exception, version
// 3.1, as published by the Free Software Foundation.

// You should have received a copy of the GNU General Public License and
// a copy of the GCC Runtime Library Exception along with this program;
// see the files COPYING3 and COPYING.RUNTIME respectively.  If not, see
// <http://www.gnu.org/licenses/>.

/** @file        bits/bitres.h
 *  @brief       Bit memory resource management
 *  @author      Polaris Zhao
 *  @version     0.8.0
 *
 *  This is an internal header file, included by other library headers.
 *  Do not attempt to use it directly. @headername{bit}
**/

#ifndef _POL_BITRES_H
#define _POL_BITRES_H 1

#include <list>
#include <memory>

namespace pol
{

template<typename _Tp>
class bit_resource
{
public:
    using value_type = _Tp;
    using storage_type = basic_bit_storage<_Tp>;
    using size_type = size_t;
    using pointer = bitmem_ptr;

private:
    struct _Chunk
    {
        storage_type* _M_data;
        size_type _M_size;

        using iterator = storage_type*;

        _Chunk() = default;

        explicit
        _Chunk(size_type __n);

        _Chunk(const _Chunk&) = delete;

        _Chunk(_Chunk&& __c) noexcept;

        ~_Chunk() noexcept;

        size_type
        size() const noexcept;

        iterator
        begin() const noexcept;

        iterator
        end() const noexcept;

        [[nodiscard]] bitmem_ptr
        allocate(size_type __n);

        void
        deallocate(bitmem_ptr __p) noexcept;
    };

public:
    using container_type = std::list<_Chunk>;
    using iterator = container_type::iterator;

private:
    container_type _M_chunk;

public:
    [[nodiscard]] pointer
    allocate(size_type __n);

    void
    deallocate(pointer __p) noexcept;

    [[nodiscard]] pointer
    reallocate(pointer __p, size_type __n);
};

template<typename _Tp = uint32_t>
bit_resource<_Tp>* default_bit_resource();

}

#endif /* _POL_BITRES_H */
