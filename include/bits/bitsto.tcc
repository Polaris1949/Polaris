// Bit storage implementation -*- C++ -*-

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

/** @file        bits/bitsto.tcc
 *  @brief       Bit storage implementation
 *  @author      Polaris Zhao
 *  @version     3.0
 *
 *  This is an internal header file, included by other library headers.
 *  Do not attempt to use it directly. @headername{bit}
**/

#ifndef _POL_BITSTO_TCC
#define _POL_BITSTO_TCC 1

namespace polaris
{

template<typename _Tp>
basic_bit_storage<_Tp>::
basic_bit_storage(const storage_type& __data)
    : _M_data{__data}
{}

template<typename _Tp>
basic_bit_storage<_Tp>::
basic_bit_storage(storage_type&& __data)
    : _M_data{std::move(__data)}
{}

template<typename _Tp>
bool
basic_bit_storage<_Tp>::
empty() const
{
    return this->_M_count == 0u;
}

template<typename _Tp>
bool
basic_bit_storage<_Tp>::
full() const
{
    return this->_M_count == storage_type{-1};
}

template<typename _Tp>
void
basic_bit_storage<_Tp>::
clear()
{
    for (level_type __i{}; __i < bitof<storage_type>(); ++__i)
        this->unlock(__i);
}

template<typename _Tp>
_Tp*
basic_bit_storage<_Tp>::
data() const
{
    return std::addressof(this->_M_data);
}

template<typename _Tp>
bool
basic_bit_storage<_Tp>::
set(level_type __n, bool __x)
{
    if (__n >= bitof<storage_type>())
        return false;

    if (__x) this->_M_data |= (storage_type{true} << __n);
    else this->_M_data &= ~(storage_type{true} << __n);
    return true;
}

template<typename _Tp>
bool
basic_bit_storage<_Tp>::
get(level_type __n) const
{
    return this->_M_data & (storage_type{true} << __n);
}

template<typename _Tp>
bool
basic_bit_storage<_Tp>::
is_locked(level_type __n) const
{
    return this->_M_count & (storage_type{true} << __n);
}

template<typename _Tp>
bool
basic_bit_storage<_Tp>::
lock(level_type __n)
{
    if (this->is_locked(__n))
        return false;
    this->_M_count |= (storage_type{true} << __n);
    return true;
}

template<typename _Tp>
bool
basic_bit_storage<_Tp>::
unlock(level_type __n)
{
    if (!this->is_locked(__n))
        return false;
    this->_M_count &= ~(storage_type{true} << __n);
    return true;
}

template<typename _Tp>
unsigned char
basic_bit_storage<_Tp>::
obtain()
{
    for (level_type __i{}; __i < bitof<storage_type>(); ++__i)
        if (this->lock(__i)) return __i;
    throw std::runtime_error{"basic_bit_storage::obtain(): "
        "no available resource"};
}

template<typename _Tp>
void
basic_bit_storage<_Tp>::
release(level_type __n)
{
    if (this->unlock(__n)) return;
    throw std::runtime_error{"basic_bit_storage::release(): "
        "no such active resource"};
}

}

#endif /* _POL_BITSTO_TCC */
