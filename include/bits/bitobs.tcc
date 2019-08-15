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

bit_ref
basic_bit_observer::
at(size_type __pos)
{
    if (__pos >= char_bit)
        throw std::out_of_range{"basic_bit_observer::at()"};
    return bit_ref{bit_address{&this->_M_impl._M_data, __pos}};
}

bool
basic_bit_observer::
at(size_type __pos) const
{
    switch (__pos)
    {
        case 0: return this->_M_impl._M_obs.b0;
        case 1: return this->_M_impl._M_obs.b1;
        case 2: return this->_M_impl._M_obs.b2;
        case 3: return this->_M_impl._M_obs.b3;
        case 4: return this->_M_impl._M_obs.b4;
        case 5: return this->_M_impl._M_obs.b5;
        case 6: return this->_M_impl._M_obs.b6;
        case 7: return this->_M_impl._M_obs.b7;
        default: throw std::out_of_range{"basic_bit_observer::at()"};
    }
}

bit_ref
basic_bit_observer::
operator[] (size_type __pos) noexcept
{
    return bit_ref{bit_address{&this->_M_impl._M_data, __pos}};
}

bool
basic_bit_observer::
operator[] (size_type __pos) const noexcept
{
    switch (__pos)
    {
        case 0: return this->_M_impl._M_obs.b0;
        case 1: return this->_M_impl._M_obs.b1;
        case 2: return this->_M_impl._M_obs.b2;
        case 3: return this->_M_impl._M_obs.b3;
        case 4: return this->_M_impl._M_obs.b4;
        case 5: return this->_M_impl._M_obs.b5;
        case 6: return this->_M_impl._M_obs.b6;
        case 7: return this->_M_impl._M_obs.b7;
        default: return false;
    }
}

void
basic_bit_observer::
set(size_type __pos)
{
    switch (__pos)
    {
        case 0: this->_M_impl._M_obs.b0 = true; return;
        case 1: this->_M_impl._M_obs.b1 = true; return;
        case 2: this->_M_impl._M_obs.b2 = true; return;
        case 3: this->_M_impl._M_obs.b3 = true; return;
        case 4: this->_M_impl._M_obs.b4 = true; return;
        case 5: this->_M_impl._M_obs.b5 = true; return;
        case 6: this->_M_impl._M_obs.b6 = true; return;
        case 7: this->_M_impl._M_obs.b7 = true; return;
        default: throw std::out_of_range{"basic_bit_observer::set()"};
    }
}

void
basic_bit_observer::
reset(size_type __pos)
{
    switch (__pos)
    {
        case 0: this->_M_impl._M_obs.b0 = false; return;
        case 1: this->_M_impl._M_obs.b1 = false; return;
        case 2: this->_M_impl._M_obs.b2 = false; return;
        case 3: this->_M_impl._M_obs.b3 = false; return;
        case 4: this->_M_impl._M_obs.b4 = false; return;
        case 5: this->_M_impl._M_obs.b5 = false; return;
        case 6: this->_M_impl._M_obs.b6 = false; return;
        case 7: this->_M_impl._M_obs.b7 = false; return;
        default: throw std::out_of_range{"basic_bit_observer::reset()"};
    }
}

void
basic_bit_observer::
flip(size_type __pos)
{
    if (__pos >= 8) throw std::out_of_range{"basic_bit_observer::flip()"};
    if (this->at(__pos)) this->reset(__pos);
    else this->set(__pos);
}

std::istream&
operator >> (std::istream& __in, basic_bit_observer& __x)
{
    for (std::size_t __i{}; __i < char_bit; ++__i)
    {
        std::size_t __j{char_bit - 1 - __i};
        char __ch;
        __in >> __ch;

        if (!(__ch == '0' || __ch == '1'))
        {
            __in.setstate(std::ios_base::failbit);
            return __in;
        }

        if (__ch - '0') __x.set(__j);
        else __x.reset(__j);
    }

    return __in;
}

std::ostream&
operator << (std::ostream& __out, const basic_bit_observer& __x)
{
    for (std::size_t __i{}; __i < char_bit; ++__i)
    {
        std::size_t __j{char_bit - 1 - __i};
        __out << char(__x[__j] + '0');
    }

    return __out;
}

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
    if (__byte >= _S_len) throw std::out_of_range{"bit_observer::at()"};
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
