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

namespace polaris
{

bool
basic_bit_observer::
at(size_type __pos) const
{
    switch (__pos)
	{
		case 0: return b0;
		case 1: return b1;
		case 2: return b2;
		case 3: return b3;
		case 4: return b4;
		case 5: return b5;
		case 6: return b6;
		case 7: return b7;
		default: throw std::out_of_range{"basic_bit_observer::at()"};
	}
}

bool
basic_bit_observer::
operator[] (size_type __pos) const noexcept
{
	switch (__pos)
	{
		case 0: return b0;
		case 1: return b1;
		case 2: return b2;
		case 3: return b3;
		case 4: return b4;
		case 5: return b5;
		case 6: return b6;
		case 7: return b7;
		default: return false;
	}
}

void
basic_bit_observer::
set(size_type __pos)
{
    switch (__pos)
	{
		case 0: b0 = true; return;
		case 1: b1 = true; return;
		case 2: b2 = true; return;
		case 3: b3 = true; return;
		case 4: b4 = true; return;
		case 5: b5 = true; return;
		case 6: b6 = true; return;
		case 7: b7 = true; return;
		default: throw std::out_of_range{"basic_bit_observer::set()"};
	}
}

void
basic_bit_observer::
reset(size_type __pos)
{
    switch (__pos)
	{
		case 0: b0 = false; return;
		case 1: b1 = false; return;
		case 2: b2 = false; return;
		case 3: b3 = false; return;
		case 4: b4 = false; return;
		case 5: b5 = false; return;
		case 6: b6 = false; return;
		case 7: b7 = false; return;
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
        char __ch{__x[__j] + '0'};
		__out << __ch;
	}

	return __out;
}

}

#endif /* _POL_BITOBS_TCC */
