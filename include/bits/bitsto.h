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
 *  @version     3.0
 *
 *  This is an internal header file, included by other library headers.
 *  Do not attempt to use it directly. @headername{bit}
**/

#ifndef _POL_BITSTO_H
#define _POL_BITSTO_H 1

namespace polaris
{

template<typename _Tp>
class basic_bit_storage
{
public:
    using storage_type = _Tp;
    using level_type = unsigned char;

private:
    _Tp _M_data;
    _Tp _M_count;

public:
    basic_bit_storage() = default;
    [[deprecated]] explicit basic_bit_storage(const storage_type& __data);
    [[deprecated]] explicit basic_bit_storage(storage_type&& __data);

    bool empty() const;
    bool full() const;
    void clear();
    storage_type* data() const;

    bool set(level_type __n, bool __x);
    bool get(level_type __n) const;

    bool is_locked(level_type __n) const;
    bool lock(level_type __n);
    bool unlock(level_type __n);

    level_type obtain();
    void release(level_type __n);
};

using  bit_storage = basic_bit_storage<uint32_t>;
using wbit_storage = basic_bit_storage<uint64_t>;

}

#endif /* _POL_BITSTO_H */
