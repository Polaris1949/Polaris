// Allocator support -*- C++ -*-

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

/** @file        bits/alloc.h
 *  @headerfile  allocator
 *  @brief       Allocator support
 *  @author      Polaris Zhao
 *  @version     3.0
 *
 *  This is an internal header file, included by other library headers.
 *  Do not attempt to use it directly.
**/

#ifndef _POL_ALLOC_H
#define _POL_ALLOC_H 1

namespace polaris
{

template<typename _Tp = void>
class allocator;

template<typename _Tp>
class allocator
{
public:
    using value_type = _Tp;
    using pointer = _Tp*;
    using size_type = size_t;

    pointer allocate(size_type __n);
    void deallocate(pointer __p);
    pointer reallocate(pointer __p, size_type __n);

    template<typename... _Args>
    pointer construct(_Args&&... __args);

    void destroy(pointer __p);

    template<typename... _Args>
    pointer reconstruct(pointer __p, _Args&&... __args);
};

template<>
class allocator<void>
{
public:
    using pointer = void*;
    using size_type = size_t;

    pointer allocate(size_type __n);
    void deallocate(pointer __p);
    pointer reallocate(pointer __p, size_type __n);
};

}

#endif /* _POL_ALLOC_H */
