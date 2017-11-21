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

/** @file bits/byte.h
 *  This is an internal header file, included by other library headers.
 *  Do not attempt to use it directly. @headername{byte}
 */

// Written by Jingyu Zhao.

#ifndef _POL_BYTE_TCC
#define _POL_BYTE_TCC 1

#include <iostream>
#include <utility>
#include <limits>

namespace polaris
{

template<typename _Sig>
byte<_Sig>::
byte(const value_type& __x) noexcept
	: _M_data(__x)
{
}

template<typename _Sig>
byte<_Sig>::
byte(value_type&& __x) noexcept
{
	this->swap(__x);
}

template<typename _Sig>
void
byte<_Sig>::
swap(value_type& __x) noexcept
{
	std::swap(_M_data, __x);
}

template<typename _Sig>
void
byte<_Sig>::
swap(self_type& __x) noexcept
{
	std::swap(_M_data, __x._M_data);
}

#define POL_DEF_REF_true &
#define POL_DEF_REF_false

#define POL_DEF_BYTE_OPERATOR_UNARY_PLACEHOLDER_true(__op, __ref) \
	template<typename _Sig> \
	byte<_Sig> POL_DEF_REF_##__ref \
	byte<_Sig>:: \
	operator __op (int) noexcept \
	{ \
		_M_data __op; \
		return *this; \
	}

#define POL_DEF_BYTE_OPERATOR_UNARY_PLACEHOLDER_false(__op, __ref) \
	template<typename _Sig> \
	byte<_Sig> POL_DEF_REF_##__ref \
	byte<_Sig>:: \
	operator __op () noexcept \
	{ \
		__op _M_data; \
		return *this; \
	}

#define POL_DEF_BYTE_OPERATOR_UNARY(__op, __ref, __ph) \
	POL_DEF_BYTE_OPERATOR_UNARY_PLACEHOLDER_##__ph(__op, __ref)

#define POL_DEF_BYTE_OPERATOR_BINARY_SIZE_true(__op, __ref, __gen) \
	template<typename _Sig> \
	byte<_Sig> POL_DEF_REF_##__ref \
	byte<_Sig>:: \
	operator __op (size_type __n) noexcept \
	{ \
		_M_data __op __n; \
		return *this; \
	}

#define POL_DEF_BYTE_OPERATOR_BINARY_GENERATE_true(__op, __ref) \
	template<typename _Sig> \
	byte<_Sig> POL_DEF_REF_##__ref \
	byte<_Sig>:: \
	operator __op (const value_type& __x) noexcept \
	{ \
		return self_type(_M_data __op __x); \
	} \
	\
	template<typename _Sig> \
	byte<_Sig> POL_DEF_REF_##__ref \
	byte<_Sig>:: \
	operator __op (const self_type& __x) noexcept \
	{ \
		return self_type(_M_data __op __x._M_data); \
	} \
	\
	template<typename _Sig> \
	byte<_Sig> POL_DEF_REF_##__ref \
	byte<_Sig>:: \
	operator __op (value_type&& __x) noexcept \
	{ \
		return self_type(_M_data __op __x); \
	} \
	\
	template<typename _Sig> \
	byte<_Sig> POL_DEF_REF_##__ref \
	byte<_Sig>:: \
	operator __op (self_type&& __x) noexcept \
	{ \
		return self_type(_M_data __op __x._M_data); \
	}

#define POL_DEF_BYTE_OPERATOR_BINARY_GENERATE_false(__op, __ref) \
	template<typename _Sig> \
	byte<_Sig> POL_DEF_REF_##__ref \
	byte<_Sig>:: \
	operator __op (const value_type& __x) noexcept \
	{ \
		_M_data __op __x; \
		return *this; \
	} \
	\
	template<typename _Sig> \
	byte<_Sig> POL_DEF_REF_##__ref \
	byte<_Sig>:: \
	operator __op (const self_type& __x) noexcept \
	{ \
		_M_data __op __x._M_data; \
		return *this; \
	} \
	\
	template<typename _Sig> \
	byte<_Sig> POL_DEF_REF_##__ref \
	byte<_Sig>:: \
	operator __op (value_type&& __x) noexcept \
	{ \
		_M_data __op __x; \
		return *this; \
	} \
	\
	template<typename _Sig> \
	byte<_Sig> POL_DEF_REF_##__ref \
	byte<_Sig>:: \
	operator __op (self_type&& __x) noexcept \
	{ \
		_M_data __op __x._M_data; \
		return *this; \
	}

#define POL_DEF_BYTE_OPERATOR_BINARY_SIZE_false(__op, __ref, __gen) \
	POL_DEF_BYTE_OPERATOR_BINARY_GENERATE_##__gen(__op, __ref)

#define POL_DEF_BYTE_OPERATOR_BINARY_BOOL_true(__op, __ref, __size, __gen) \
	template<typename _Sig> \
	bool \
	byte<_Sig>:: \
	operator __op (const value_type& __x) noexcept \
	{ \
		return _M_data __op __x; \
	} \
	\
	template<typename _Sig> \
	bool \
	byte<_Sig>:: \
	operator __op (const self_type& __x) noexcept \
	{ \
		return _M_data __op __x._M_data; \
	} \
	\
	template<typename _Sig> \
	bool \
	byte<_Sig>:: \
	operator __op (value_type&& __x) noexcept \
	{ \
		return _M_data __op __x; \
	} \
	\
	template<typename _Sig> \
	bool \
	byte<_Sig>:: \
	operator __op (self_type&& __x) noexcept \
	{ \
		return _M_data __op __x._M_data; \
	}

#define POL_DEF_BYTE_OPERATOR_BINARY_BOOL_false(__op, __ref, __size, __gen) \
	POL_DEF_BYTE_OPERATOR_BINARY_SIZE_##__size(__op, __ref, __gen)

#define POL_DEF_BYTE_OPERATOR_BINARY(__op, __ref, __bool, __size, __gen) \
	POL_DEF_BYTE_OPERATOR_BINARY_BOOL_##__bool(__op, __ref, __size, __gen)

	POL_DEF_BYTE_OPERATOR_UNARY(+, false, false)
	POL_DEF_BYTE_OPERATOR_UNARY(-, false, false)
	POL_DEF_BYTE_OPERATOR_UNARY(++, true, false)
	POL_DEF_BYTE_OPERATOR_UNARY(--, true, false)
	POL_DEF_BYTE_OPERATOR_UNARY(++, false, true)
	POL_DEF_BYTE_OPERATOR_UNARY(--, false, true)
	
	POL_DEF_BYTE_OPERATOR_BINARY(=, true, false, false, false)
	POL_DEF_BYTE_OPERATOR_BINARY(+=, true, false, false, false)
	POL_DEF_BYTE_OPERATOR_BINARY(-=, true, false, false, false)
	POL_DEF_BYTE_OPERATOR_BINARY(*=, true, false, false, false)
	POL_DEF_BYTE_OPERATOR_BINARY(/=, true, false, false, false)
	POL_DEF_BYTE_OPERATOR_BINARY(%=, true, false, false, false)
	POL_DEF_BYTE_OPERATOR_BINARY(<<=, true, false, true, false)
	POL_DEF_BYTE_OPERATOR_BINARY(>>=, true, false, true, false)
	POL_DEF_BYTE_OPERATOR_BINARY(&=, true, false, false, false)
	POL_DEF_BYTE_OPERATOR_BINARY(|=, true, false, false, false)
	POL_DEF_BYTE_OPERATOR_BINARY(^=, true, false, false, false)
	POL_DEF_BYTE_OPERATOR_BINARY(+, false, false, false, true)
	POL_DEF_BYTE_OPERATOR_BINARY(-, false, false, false, true)
	POL_DEF_BYTE_OPERATOR_BINARY(*, false, false, false, true)
	POL_DEF_BYTE_OPERATOR_BINARY(/, false, false, false, true)
	POL_DEF_BYTE_OPERATOR_BINARY(%, false, false, false, true)
	POL_DEF_BYTE_OPERATOR_BINARY(<<, false, false, true, true)
	POL_DEF_BYTE_OPERATOR_BINARY(>>, false, false, true, true)
	POL_DEF_BYTE_OPERATOR_BINARY(&, false, false, false, true)
	POL_DEF_BYTE_OPERATOR_BINARY(|, false, false, false, true)
	POL_DEF_BYTE_OPERATOR_BINARY(^, false, false, false, true)
	POL_DEF_BYTE_OPERATOR_BINARY(==, false, true, false, false)
	POL_DEF_BYTE_OPERATOR_BINARY(!=, false, true, false, false)
	POL_DEF_BYTE_OPERATOR_BINARY(<, false, true, false, false)
	POL_DEF_BYTE_OPERATOR_BINARY(<=, false, true, false, false)
	POL_DEF_BYTE_OPERATOR_BINARY(>, false, true, false, false)
	POL_DEF_BYTE_OPERATOR_BINARY(>=, false, true, false, false)

#undef POL_DEF_REF_true
#undef POL_DEF_REF_false
#undef POL_DEF_BYTE_OPERATOR_UNARY_PLACEHOLDER_true
#undef POL_DEF_BYTE_OPERATOR_UNARY_PLACEHOLDER_false
#undef POL_DEF_BYTE_OPERATOR_UNARY
#undef POL_DEF_BYTE_OPERATOR_BINARY_GENERATE_true
#undef POL_DEF_BYTE_OPERATOR_BINARY_GENERATE_false
#undef POL_DEF_BYTE_OPERATOR_BINARY_SIZE_true
#undef POL_DEF_BYTE_OPERATOR_BINARY_SIZE_false
#undef POL_DEF_BYTE_OPERATOR_BINARY_BOOL_true
#undef POL_DEF_BYTE_OPERATOR_BINARY_BOOL_false
#undef POL_DEF_BYTE_OPERATOR_BINARY

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

#endif /* _POL_BYTE_TCC */
