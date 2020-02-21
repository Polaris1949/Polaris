// Bitmask -*- C++ -*-

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

/** @file bits/bmask.h
 *  This is an internal header file, included by other library headers.
 *  Do not attempt to use it directly. @headername{bitmask}
 */

// Written by Polaris Zhao.

#ifndef _POL_BMASK_H
#define _POL_BMASK_H 1

namespace polaris
{

class bitmask;

bitmask operator & (const bitmask& __x, const bitmask& __y);
bitmask operator | (const bitmask& __x, const bitmask& __y);
bitmask operator ^ (const bitmask& __x, const bitmask& __y);

template<size_t _Num>
class bitmask
{
	typedef std::bitset<_Num> _Cont;

public:
	typedef _Cont                   container_type;
	typedef _Cont::size_type        size_type;
	typedef _Cont::value_type       value_type;
	typedef _Cont::reference        reference;
	typedef _Cont::const_reference  const_reference;

public:
	bitmask() = default;
	bitmask(const std::string& __x);
	bitmask(const container_type& __x);
	~bitmask() noexcept = default;

	[[deprecated]] container_type& raw();
	[[deprecated]] const container_type& raw() const;

	reference operator[] (size_type __n);
	const_reference operator[] (size_type __n) const;

	bitmask& flip();
	bitmask operator~ ();

	bitmask& operator &= (const bitmask& __x);
	bitmask& operator |= (const bitmask& __x);
	bitmask& operator ^= (const bitmask& __x);

	friend bitmask operator & (const bitmask& __x, const bitmask& __y);
	friend bitmask operator | (const bitmask& __x, const bitmask& __y);
	friend bitmask operator ^ (const bitmask& __x, const bitmask& __y);

private:
	_Cont _M_b;
};

}

#endif
