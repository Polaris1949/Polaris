// Bit storage -*- C++ -*-

// Copyright (C) 1997-2017 Free Software Foundation, Inc.
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

/** @file        bits/bitsto.h
 *  @brief       Bit storage
 *  @author      Polaris Zhao
 *  @version     0.8.0
 *
 *  This is an internal header file, included by other library headers.
 *  Do not attempt to use it directly. @headername{bit}
**/

#ifndef _POL_BITSTO_H
#define _POL_BITSTO_H 1

namespace pol
{

template<typename _Tp>
class basic_bit_storage
{
public:
    static_assert(std::is_integral_v<_Tp> && std::is_unsigned_v<_Tp>,
        "require unsigned integral type");

    using storage_type = _Tp;
    using value_type = _Tp;
    using size_type = size_t;
    using reference = bit_ref;
    using const_reference = bool;

private:
    _Tp _M_data;
    _Tp _M_count;

public:
    basic_bit_storage() noexcept;

    bool empty() const noexcept;
    bool full() const noexcept;

    void clear() noexcept;
    constexpr size_type size() const noexcept;
    storage_type& data() noexcept;
    const storage_type& data() const noexcept;

    void set(size_type __n, bool __x);
    bool get(size_type __n) const;

    bool is_locked(size_type __n) const;
    bool lock(size_type __n);
    bool unlock(size_type __n);

    void lockl(size_type __n);
    void lockr(size_type __n);

    size_type alloc_p();
    void dealloc_p(size_type __n);

    bitmem_ptr allocate(size_type __n);
    void deallocate(bitmem_ptr __p) noexcept;

    size_type free_countl() const noexcept;
    size_type free_countr() const noexcept;

    size_type busy_count() const noexcept;

    void*
    begin() noexcept;

    const void*
    begin() const noexcept;

    void*
    end() noexcept;

    const void*
    end() const noexcept;

    bool
    in_range(bit_ptr __p) const noexcept;

    bit_ref at(size_type __n);
    bool at(size_type __n) const;

    bit_ref
    operator[] (size_type __n);

    bool
    operator[] (size_type __n) const;
};

#if POL_BITSTO_NEW
using bit_storage = basic_bit_storage<size_t>;
using bit_storage32_t = basic_bit_storage<uint32_t>;
using bit_storage64_t = basic_bit_storage<uint64_t>;
#else
using  bit_storage = basic_bit_storage<uint32_t>;
using wbit_storage = basic_bit_storage<uint64_t>;
#endif

}

#endif /* _POL_BITSTO_H */
