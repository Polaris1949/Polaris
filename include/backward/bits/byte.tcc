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

/** @file backward/bits/byte.tcc
 *  This is an internal header file, included by other library headers.
 *  Do not attempt to use it directly. @headername{backward/byte}
 */

// Written by Jingyu Zhao.

#ifndef _POL_BYTE_TCC
#define _POL_BYTE_TCC 1

#include <stdexcept>
#include <iostream>
#include <limits>
#include <polaris/bits/type.tcc>

namespace polaris
{

template<typename _Sig>
byte<_Sig>::
byte() noexcept
	: integer_type<typename byte_helper<_Sig>::type>()
{
}

template<typename _Sig>
byte<_Sig>::
byte(const typename byte_helper<_Sig>::type& __x) noexcept
	: integer_type<typename byte_helper<_Sig>::type>(__x)
{
}

template<typename _Sig>
byte<_Sig>::
byte(typename byte_helper<_Sig>::type&& __x) noexcept
	: integer_type<typename byte_helper<_Sig>::type>()
{
	this->swap(__x);
}

template<typename _Sig>
byte<_Sig>::
byte(const byte<_Sig>& __x) noexcept
	: integer_type<typename byte_helper<_Sig>::type>(__x._M_data)
{
}

template<typename _Sig>
byte<_Sig>::
byte(byte<_Sig>&& __x) noexcept
	: integer_type<typename byte_helper<_Sig>::type>()
{
	this->swap(__x);
}

template<typename _Sig>
byte<_Sig>::
~byte() noexcept
{
}

template<typename _Sig>
byte<_Sig>&
byte<_Sig>::
operator = (const byte<_Sig>& __x) noexcept
{
	this->_M_data = __x._M_data;
	return *this;
}

template<typename _Sig>
byte<_Sig>&
byte<_Sig>::
operator = (byte<_Sig>&& __x) noexcept
{
	this->_M_data = typename byte_helper<_Sig>::type();
	this->swap(__x);
	return *this;
}

template<typename _S>
std::istream&
operator >> (std::istream& __in, byte<_S>& __x)
{
	typename byte_helper<_S>::io_type temp;
	__in >> temp;

	if (__in.fail())
		return __in;

	if (temp > static_cast<typename byte_helper<_S>::io_type>
		(std::numeric_limits<typename byte_helper<_S>::type>::max()))
	{
		__in.setstate(std::ios_base::failbit);
		return __in;
	}

	if (temp < static_cast<typename byte_helper<_S>::io_type>
		(std::numeric_limits<typename byte_helper<_S>::type>::min()))
	{
		__in.setstate(std::ios_base::failbit);
		return __in;
	}

	__x._M_data = temp;
	return __in;
}

template<typename _S>
std::ostream&
operator << (std::ostream& __out, const byte<_S>& __x)
{
	__out << typename byte_helper<_S>::io_type(__x._M_data);
	return __out;
}

}

#endif
