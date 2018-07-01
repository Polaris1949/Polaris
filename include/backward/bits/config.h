// Predefined symbols and macros for Polaris Library -*- C++ -*-

// Copyright (C) 1997-2016 Free Software Foundation, Inc.
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

/** @file bits/config.h
 *  This is an internal header file, included by other library headers.
 *  Do not attempt to use it directly. @headername{utility}
 */

#ifndef _POL_CONFIG_H
#define _POL_CONFIG_H 1

#include <iosfwd>

namespace polaris
{
/*
#if __cplusplus < 201103L
#error polaris library need c++11 at least
#pragma message("use option -std=c++11 to enable")
#endif
*/
/* Experimental
#if __cplusplus < 201103L
#define __noexcept noexcept
#else
#define __noexcept throw()
#endif
*/
// Deprecated

// Standard veriosn declarations.
//@{
/*
// Same declarations.
#define and_pol and
#define and_eq_pol and_eq
#define asm_pol asm
#define auto_pol auto
#define bitand_pol bitand
#define bitor_pol bitor
#define bool_pol bool
#define break_pol break
#define case_pol case
#define catch_pol catch
#define char_pol char
#define class_pol class
#define compl_pol compl
#define const_pol const
#define const_cast_pol const_cast
#define continue_pol continue
#define default_pol default
#define delete_pol delete
#define do_pol do
#define double_pol double
#define dynamic_cast_pol dynamic_cast
#define else_pol else
#define enum_pol enum
#define explicit_pol explicit
#define extern_pol extern
#define false_pol false
#define float_pol float
#define for_pol for
#define friend_pol friend
#define goto_pol goto
#define if_pol if
#define inline_pol inline
#define int_pol int
#define long_pol long
#define mutable_pol mutable
#define namespace_pol namespace
#define new_pol new
#define not_pol not
#define not_eq_pol not_eq
#define operator_pol operator
#define or_pol or
#define or_eq_pol or_eq
#define private_pol private
#define protected_pol protected
#define public_pol public
#define register_pol register
#define reinterpret_cast_pol reinterpret_cast
#define return_pol return
#define short_pol short
#define signed_pol signed
#define sizeof_pol sizeof
#define static_pol static
#define static_cast_pol static_cast
#define struct_pol struct
#define switch_pol switch
#define template_pol template
#define this_pol this
#define throw_pol throw
#define true_pol true
#define try_pol try
#define typedef_pol typedef
#define typeid_pol typeid
#define typename_pol typename
#define union_pol union
#define unsigned_pol unsigned
#define using_pol using
#define virtual_pol virtual
#define void_pol void
#define volatile_pol volatile
#define wchar_t_pol wchar_t
#define while_pol while
#define xor_pol xor
#define xor_eq_pol xor_eq

// Different declarations.
#if __cplusplus < 201103L
# define alignas_pol(__x)
# define alignof_pol(__x)
# define char16_t_pol unsigned short
# define char32_t_pol unsigned long
# define constexpr_pol
# define decltype_pol(__x)
# define noexcept_pol throw()
# define nullptr_pol ((void*)0)
# define static_assert_pol(__x, __y)
# define thread_local_pol
#else
# define alignas_pol(__x) alignas(__x)
# define alignof_pol(__x) alignof(__x)
# define char16_t_pol char16_t
# define char32_t_pol char32_t
# define constexpr_pol constexpr
# define decltype_pol(__x) decltype(__x)
# define noexcept_pol noexcept
# define nullptr_pol nullptr
# define static_assert_pol(__x, __y) static_assert(__x, __y)
# define thread_local_pol thread_local
#endif

//@}

// TS version declarations.
//@{

// Transactional Memory TS.
#if defined(__cpp_transactional_memory)
# warning mingw gcc has bad TM TS with value 210505L
# define atomic_cancel_pol atomic_cancel
# define atomic_commit_pol atomic_commit
# define atomic_noexcept_pol atomic_noexcept
# define synchronized_pol synchronized
# if __cpp_transactional_memory < 201505L
#  warning bad version
# endif
#else
# define atomic_cancel_pol
# define atomic_commit_pol
# define atomic_noexcept_pol
# define synchronized_pol
#endif

// Concepts TS.
#if defined(__cpp_concepts)
# define concept_pol concept
# define requires_pol requires
// For bug fixes.
//# if __cpp_concepts < 201507
//#  warning bad version
//# endif
//
# if __cpp_concepts < 201500
#  warning bad version
# endif
#else
# define concept_pol
# define requires_pol
#endif

// Modules TS (unimplemented).
#if defined(__cpp_modules)
# define export_pol export
# define import_pol import
# define module_pol module
# if __cpp_modules < 201600
#  warning bad version
# endif
#else
# define export_pol
# define import_pol
# define module_pol
#endif

//@}

#define __pol_keyword(__x) __x##_pol
*/
/*
struct tag_type
{
	typedef tag_type type;
	
	constexpr static const char*
	value()
	{
		return "tag_type";
	}
};

#define POL_MAKE_BTAG(__name) \
	struct __name : public tag_type \
	{ \
		typedef __name type; \
		typedef tag_type backward_type; \
		\
		constexpr static const char* \
		value() \
		{ \
			return #__name; \
		} \
		\
		constexpr static const char* \
		backward_value() \
		{ \
			return "tag_type";\
		} \
	};

#define POL_MAKE_DTAG(__name, __base) \
	struct __name : public __base \
	{ \
		typedef __name type; \
		typedef __base backward_type; \
		\
		constexpr static const char* \
		value() \
		{ \
			return #__name; \
		} \
		\
		constexpr static const char* \
		backward_value() \
		{ \
			return #__base;\
		} \
	};

POL_MAKE_BTAG(integer_sign)
POL_MAKE_DTAG(signed_type, integer_sign)
POL_MAKE_DTAG(unsigned_type, integer_sign)

//typedef tag_type* tag;

typedef signed char signed_char;
typedef unsigned char unsigned_char;
typedef signed short signed_short;
typedef unsigned short unsigned_short;

typedef std::size_t size_t;
constexpr size_t npos = static_cast<size_t>(-1);
*/
}
/*
namespace pol
{
	using namespace polaris;
}

namespace polstd
{
	using namespace polaris;
	using namespace std;
}
*/
#endif
