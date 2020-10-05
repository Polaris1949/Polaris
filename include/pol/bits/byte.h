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

/** @file        bits/byte.h
 *  @brief       Byte
 *  @author      Polaris Zhao
 *  @version     0.8.0
 *
 *  This is an internal header file, included by other library headers.
 *  Do not attempt to use it directly. @headername{byte}
**/

#ifndef _POL_BYTE_H
#define _POL_BYTE_H 1

#include <iosfwd>

namespace pol
{

struct signed_tag {};
struct unsigned_tag {};

template<typename>
class basic_byte;

typedef basic_byte<signed_tag>    signed_byte;
typedef basic_byte<unsigned_tag>  unsigned_byte;

using sbyte = signed_byte;
using ubyte = unsigned_byte;
using byte = unsigned_byte;

template<typename>
struct byte_helper;

template<>
struct byte_helper<signed_tag>
{
    using type = signed char;
    using io_type = signed int;
};

template<>
struct byte_helper<unsigned_tag>
{
    using type = unsigned char;
    using io_type = unsigned int;
};

template<typename _SigT>
std::istream&
operator >> (std::istream& __in, basic_byte<_SigT>& __x);

template<typename _SigT>
std::ostream&
operator << (std::ostream& __out, const basic_byte<_SigT>& __x);

template<typename _Sig>
class basic_byte
{
public:
    using sign_type = _Sig;
    using self_type = basic_byte<_Sig>;
    using value_type = byte_helper<_Sig>::type;
    using size_type = size_t;

public:
	basic_byte() noexcept = default;

	basic_byte(const value_type& __x) noexcept;

	basic_byte(value_type&& __x) noexcept;

	basic_byte(const self_type& __x) noexcept = default;

	basic_byte(self_type&& __x) noexcept = default;

	~basic_byte() noexcept = default;

	void
	swap(value_type& __x) noexcept;

	void
	swap(self_type& __x) noexcept;

	explicit
	operator value_type() const noexcept;

#define POL_MAKE_REF_true &
#define POL_MAKE_REF_false
#define POL_MAKE_PLACEHOLDER_true int
#define POL_MAKE_PLACEHOLDER_false

#define POL_MAKE_BYTE_OPERATOR_UNARY(__op, __ref, __ph) \
	self_type POL_MAKE_REF_##__ref \
	operator __op (POL_MAKE_PLACEHOLDER_##__ph) noexcept;

#define POL_MAKE_BYTE_OPERATOR_BINARY_SIZE_true(__op, __ref) \
	self_type POL_MAKE_REF_##__ref \
	operator __op (size_type __n) noexcept;

#define POL_MAKE_BYTE_OPERATOR_BINARY_SIZE_false(__op, __ref) \
	self_type POL_MAKE_REF_##__ref \
	operator __op (const value_type& __x) noexcept; \
	\
	self_type POL_MAKE_REF_##__ref \
	operator __op (const self_type& __x) noexcept; \
	\
	self_type POL_MAKE_REF_##__ref \
	operator __op (value_type&& __x) noexcept; \
	\
	self_type POL_MAKE_REF_##__ref \
	operator __op (self_type&& __x) noexcept;

#define POL_MAKE_BYTE_OPERATOR_BINARY_BOOL_true(__op, __ref, __size) \
	bool \
	operator __op (const value_type& __x) noexcept; \
	\
	bool \
	operator __op (const self_type& __x) noexcept; \
	\
	bool \
	operator __op (value_type&& __x) noexcept; \
	\
	bool \
	operator __op (self_type&& __x) noexcept;

#define POL_MAKE_BYTE_OPERATOR_BINARY_BOOL_false(__op, __ref, __size) \
	POL_MAKE_BYTE_OPERATOR_BINARY_SIZE_##__size(__op, __ref)

#define POL_MAKE_BYTE_OPERATOR_BINARY(__op, __ref, __bool, __size) \
	POL_MAKE_BYTE_OPERATOR_BINARY_BOOL_##__bool(__op, __ref, __size)

	POL_MAKE_BYTE_OPERATOR_UNARY(+, false, false)
	POL_MAKE_BYTE_OPERATOR_UNARY(-, false, false)
	POL_MAKE_BYTE_OPERATOR_UNARY(++, true, false)
	POL_MAKE_BYTE_OPERATOR_UNARY(--, true, false)
	POL_MAKE_BYTE_OPERATOR_UNARY(++, false, true)
	POL_MAKE_BYTE_OPERATOR_UNARY(--, false, true)

	POL_MAKE_BYTE_OPERATOR_BINARY(=, true, false, false)
	POL_MAKE_BYTE_OPERATOR_BINARY(+=, true, false, false)
	POL_MAKE_BYTE_OPERATOR_BINARY(-=, true, false, false)
	POL_MAKE_BYTE_OPERATOR_BINARY(*=, true, false, false)
	POL_MAKE_BYTE_OPERATOR_BINARY(/=, true, false, false)
	POL_MAKE_BYTE_OPERATOR_BINARY(%=, true, false, false)
	POL_MAKE_BYTE_OPERATOR_BINARY(<<=, true, false, true)
	POL_MAKE_BYTE_OPERATOR_BINARY(>>=, true, false, true)
	POL_MAKE_BYTE_OPERATOR_BINARY(&=, true, false, false)
	POL_MAKE_BYTE_OPERATOR_BINARY(|=, true, false, false)
	POL_MAKE_BYTE_OPERATOR_BINARY(^=, true, false, false)
	POL_MAKE_BYTE_OPERATOR_BINARY(+, false, false, false)
	POL_MAKE_BYTE_OPERATOR_BINARY(-, false, false, false)
	POL_MAKE_BYTE_OPERATOR_BINARY(*, false, false, false)
	POL_MAKE_BYTE_OPERATOR_BINARY(/, false, false, false)
	POL_MAKE_BYTE_OPERATOR_BINARY(%, false, false, false)
	POL_MAKE_BYTE_OPERATOR_BINARY(<<, false, false, true)
	POL_MAKE_BYTE_OPERATOR_BINARY(>>, false, false, true)
	POL_MAKE_BYTE_OPERATOR_BINARY(&, false, false, false)
	POL_MAKE_BYTE_OPERATOR_BINARY(|, false, false, false)
	POL_MAKE_BYTE_OPERATOR_BINARY(^, false, false, false)
	POL_MAKE_BYTE_OPERATOR_BINARY(==, false, true, false)
	POL_MAKE_BYTE_OPERATOR_BINARY(!=, false, true, false)
	POL_MAKE_BYTE_OPERATOR_BINARY(<, false, true, false)
	POL_MAKE_BYTE_OPERATOR_BINARY(<=, false, true, false)
	POL_MAKE_BYTE_OPERATOR_BINARY(>, false, true, false)
	POL_MAKE_BYTE_OPERATOR_BINARY(>=, false, true, false)

#undef POL_MAKE_REF_true
#undef POL_MAKE_REF_false
#undef POL_MAKE_PLACEHOLDER_true
#undef POL_MAKE_PLACEHOLDER_false
#undef POL_MAKE_BYTE_OPERATOR_UNARY
#undef POL_MAKE_BYTE_OPERATOR_BINARY_SIZE_true
#undef POL_MAKE_BYTE_OPERATOR_BINARY_SIZE_false
#undef POL_MAKE_BYTE_OPERATOR_BINARY_BOOL_true
#undef POL_MAKE_BYTE_OPERATOR_BINARY_BOOL_false
#undef POL_MAKE_BYTE_OPERATOR_BINARY

	template<typename _SigT>
	friend std::istream&
	operator >> (std::istream& __in, basic_byte<_SigT>& __x);

	template<typename _SigT>
	friend std::ostream&
	operator << (std::ostream& __out, const basic_byte<_SigT>& __x);
    
private:
	value_type _M_data;
};

}

#endif /* _POL_BYTE_H */
