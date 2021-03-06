// Boolean implementation -*- C++ -*-

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

/** @file        bits/boolean.tcc
 *  @headerfile  boolean
 *  @brief       Boolean implementation
 *  @author      Polaris Zhao
 *  @version     3.0
 *
 *  This is an internal header file, included by other library headers.
 *  Do not attempt to use it directly.
**/

#ifndef _POL_BOOLEAN_TCC
#define _POL_BOOLEAN_TCC 1

#include <iostream>

namespace polaris
{

boolean::
boolean(bool __arg) noexcept
	: _M_data{__arg}
{}

bool
boolean::
operator == (const boolean& __arg) const noexcept
{ return _M_data == __arg._M_data; }

bool
boolean::
operator != (const boolean& __arg) const noexcept
{ return _M_data != __arg._M_data; }

boolean::
operator bool() const noexcept
{ return _M_data; }

std::istream&
operator >> (std::istream& __in, boolean& __arg)
{
	__in >> __arg._M_data;
	return __in;
}

std::ostream&
operator << (std::ostream& __out, const boolean& __arg)
{
	__out << __arg._M_data;
	return __out;
}

}

#endif /* _POL_BOOLEAN_TCC */
