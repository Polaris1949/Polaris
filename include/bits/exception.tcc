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

/** @file        bits/exception.tcc
 *  @headerfile  exception
 *  @brief       Exception handling support
 *  @author      Polaris Zhao
 *  @version     3.0
 *
 *  This is an internal header file, included by other library headers.
 *  Do not attempt to use it directly.
**/

#ifndef _POL_EXCEPTION_TCC
#define _POL_EXCEPTION_TCC 1

namespace polaris
{

#define POL_ASSERT_CATEGORY "assertion failed"
#define POL_EXPECT_CATEGORY "precondition failed"
#define POL_ENSURE_CATEGORY "postcondition failed"

void
issue(bool __c, const std::string& __cate POL_SOURCE_LOCATION_DEFN)
{
    if (!__c)
        throw std::runtime_error{POL_SOURCE_LOCATION_ARGU __cate};
}

void
issue(bool __c, const std::string& __cate, const std::string& __msg
    POL_SOURCE_LOCATION_DEFN)
{
    if (!__c)
        throw std::runtime_error{POL_SOURCE_LOCATION_ARGU __cate
            + ": " + __msg};
}

void
assert_always(bool __c POL_SOURCE_LOCATION_DEFN)
{
    issue(__c, POL_ASSERT_CATEGORY POL_SOURCE_LOCATION_PARA);
}

void
assert_always(bool __c, const std::string& __msg POL_SOURCE_LOCATION_DEFN)
{
    issue(__c, POL_ASSERT_CATEGORY, __msg POL_SOURCE_LOCATION_PARA);
}

void
assert_debug(bool __c POL_SOURCE_LOCATION_DEFN)
{
#if POL_DEBUG
    assert_always(__c POL_SOURCE_LOCATION_PARA);
#endif
}

void
assert_debug(bool __c, const std::string& __msg POL_SOURCE_LOCATION_DEFN)
{
#if POL_DEBUG
    assert_always(__c, __msg POL_SOURCE_LOCATION_PARA);
#endif
}

void
assert_if(bool __p, bool __c POL_SOURCE_LOCATION_DEFN)
{
    if (__p)
        assert_always(__c POL_SOURCE_LOCATION_PARA);
}

void
assert_if(bool __p, bool __c, const std::string& __msg
    POL_SOURCE_LOCATION_DEFN)
{
    if (__p)
        assert_always(__c, __msg POL_SOURCE_LOCATION_PARA);
}

void
expect(bool __c POL_SOURCE_LOCATION_DEFN)
{
    issue(__c, POL_EXPECT_CATEGORY POL_SOURCE_LOCATION_PARA);
}

void
expect(bool __c, const std::string& __msg POL_SOURCE_LOCATION_DEFN)
{
    issue(__c, POL_EXPECT_CATEGORY, __msg POL_SOURCE_LOCATION_PARA);
}

void
ensure(bool __c POL_SOURCE_LOCATION_DEFN)
{
    issue(__c, POL_ENSURE_CATEGORY POL_SOURCE_LOCATION_PARA);
}

void
ensure(bool __c, const std::string& __msg POL_SOURCE_LOCATION_DEFN)
{
    issue(__c, POL_ENSURE_CATEGORY, __msg POL_SOURCE_LOCATION_PARA);
}

}

#endif /* _POL_EXCEPTION_TCC */
