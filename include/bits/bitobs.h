// Bit observer classes -*- C++ -*-

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

/** @file        bits/bitobs.h
 *  @headerfile  bit_observer
 *  @brief       Bit observer classes
 *  @author      Polaris Zhao
 *  @version     3.0
 *
 *  This is an internal header file, included by other library headers.
 *  Do not attempt to use it directly.
**/

#ifndef _POL_BITOBS_H
#define _POL_BITOBS_H 1

#include <iosfwd>

namespace polaris
{

class basic_bit_observer
{
public:
    using size_type = std::size_t;

private:
    bool b0 : 1;
    bool b1 : 1;
    bool b2 : 1;
    bool b3 : 1;
    bool b4 : 1;
    bool b5 : 1;
    bool b6 : 1;
    bool b7 : 1;

public:
    bool
    at(size_type __pos) const;

    bool
    operator[] (size_type __pos) const noexcept;

    void
    set(size_type __pos);

    void
    reset(size_type __pos);

    void
    flip(size_type __pos);

    friend std::istream&
	operator >> (std::istream& __in, basic_bit_observer& __x);

    friend std::ostream&
	operator << (std::ostream& __out, const basic_bit_observer& __x);
};

template<typename _Tp>
class bit_observer
{
public:
    using value_type = _Tp;
    using size_type = std::size_t;

private:
    inline constexpr static size_type _S_len = sizeof(_Tp);

    union _Impl
    {
        _Tp _M_data;
        basic_bit_observer _M_obs[_S_len];

        _Impl() = default;
        _Impl(const value_type& __x);
    };

    _Impl _M_impl;

public:
    bool
    at(size_type __pos) const;

    bool
    operator[] (size_type __pos) const noexcept;
};

}

#endif /* _POL_BITOBS_H */
