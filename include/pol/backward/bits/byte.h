// Byte -*- C++ -*-

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

/** @file backward/bits/byte.h
 *  This is an internal header file, included by other library headers.
 *  Do not attempt to use it directly. @headername{backward/byte}
 */

// Written by Jingyu Zhao.

#ifndef _POL_BYTE_H
#define _POL_BYTE_H 1

#include <polaris/bits/type.h>

namespace polaris
{

template<typename>
struct byte_helper;

template<typename>
class byte;

typedef byte<signed_type>    signed_byte;
typedef byte<unsigned_type>  unsigned_byte;

template<typename>
struct byte_helper
{
};

template<>
struct byte_helper<signed_type>
{
	typedef signed_char   type;
	typedef signed_short  io_type;
};

template<>
struct byte_helper<unsigned_type>
{
	typedef unsigned_char   type;
	typedef unsigned_short  io_type;
};

template<typename _Sig>
class byte : public integer_type<typename byte_helper<_Sig>::type>
{
public:
	typedef _Sig                              sign_type;
	typedef typename byte_helper<_Sig>::type  value_type;

public:
	byte() noexcept;

	byte(const value_type& __x) noexcept;

	byte(value_type&& __x) noexcept;

	byte(const byte<sign_type>& __x) noexcept;

	byte(byte<sign_type>&& __x) noexcept;

	virtual
	~byte() noexcept;

	byte<sign_type>&
	operator = (const byte<sign_type>& __x) noexcept;

	byte<sign_type>&
	operator = (byte<sign_type>&& __x) noexcept;

	template<typename _S>
	friend std::istream&
	operator >> (std::istream& __in, byte<_S>& __x);

	template<typename _S>
	friend std::ostream&
	operator << (std::ostream& __out, const byte<_S>& __x);
};

}

#endif
