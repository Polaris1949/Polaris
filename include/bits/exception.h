// Exception handling support -*- C++ -*-

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

/** @file        bits/exception.h
 *  @headerfile  exception
 *  @brief       Exception handling support
 *  @author      Polaris Zhao
 *  @version     3.0
 *
 *  This is an internal header file, included by other library headers.
 *  Do not attempt to use it directly.
**/

#ifndef _POL_EXCEPTION_H
#define _POL_EXCEPTION_H 1

namespace polaris
{

void
issue(bool __c POL_SOURCE_LOCATION_DECL);

void
issue(bool __c, const std::string& __msg POL_SOURCE_LOCATION_DECL);

void
assert_always(bool __c POL_SOURCE_LOCATION_DECL);

void
assert_always(bool __c, const std::string& __msg POL_SOURCE_LOCATION_DECL);

void
assert_debug(bool __c POL_SOURCE_LOCATION_DECL);

void
assert_debug(bool __c, const std::string& __msg POL_SOURCE_LOCATION_DECL);

void
assert_if(bool __p, bool __c POL_SOURCE_LOCATION_DECL);

void
assert_if(bool __p, bool __c, const std::string& __msg
    POL_SOURCE_LOCATION_DECL);

void
expect(bool __c POL_SOURCE_LOCATION_DECL);

void
expect(bool __c, const std::string& __msg POL_SOURCE_LOCATION_DECL);

void
ensure(bool __c POL_SOURCE_LOCATION_DECL);

void
ensure(bool __c, const std::string& __msg POL_SOURCE_LOCATION_DECL);

}

#endif /* _POL_EXCEPTION_H */
