// Bit observer implementation -*- C++ -*-

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

/** @file        bits/bitobs.tcc
 *  @headerfile  bit_observer
 *  @brief       Bit observer implementation
 *  @author      Polaris Zhao
 *  @version     3.0
 *
 *  This is an internal header file, included by other library headers.
 *  Do not attempt to use it directly.
**/

#ifndef _POL_BITOBS_TCC
#define _POL_BITOBS_TCC 1

#include <stdexcept>
#include <iostream>

namespace pol
{

template<typename _Tp>
bit_observer<_Tp>::
bit_observer(const value_type& __x)
    : _M_impl{__x}
{}

template<typename _Tp>
bit_observer<_Tp>::_Impl::
_Impl(const value_type& __x)
    : _M_data{__x}
{}

template<typename _Tp>
bool
bit_observer<_Tp>::
at(size_type __pos) const
{
    size_type __byte{__pos / char_bit};
    if (__byte >= _S_len)
        throw std::out_of_range{"bit_observer::at()"};
    return this->_M_impl._M_obs[__byte][__pos % char_bit];
}

template<typename _Tp>
basic_bit_observer&
bit_observer<_Tp>::
at_observer(size_type __pos)
{ return this->_M_impl._M_obs[__pos]; }

template<typename _Tp>
const basic_bit_observer&
bit_observer<_Tp>::
at_observer(size_type __pos) const
{ return this->_M_impl._M_obs[__pos]; }

template<typename _Tp>
bool
bit_observer<_Tp>::
operator[] (size_type __pos) const noexcept
{ return this->_M_impl._M_obs[__pos / char_bit][__pos % char_bit]; }

template<typename _Tp>
_Tp&
bit_observer<_Tp>::
data() noexcept
{ return this->_M_impl._M_data; }

template<typename _Up>
std::ostream&
operator << (std::ostream& __out, const bit_observer<_Up>& __x)
{
    // TODO: Endian support
    for (size_t __i{}; __i < bit_observer<_Up>::_S_len; ++__i)
        __out << __x.at_observer(bit_observer<_Up>::_S_len - 1 - __i);

    return __out;
}

}

#endif /* _POL_BITOBS_TCC */
