// Allocator support -*- C++ -*-

// Copyright (C) 2004-2018 Free Software Foundation, Inc.
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

/** @file        bits/alloc.tcc
 *  @brief       Allocator support
 *  @author      Polaris Zhao
 *  @version     3.0
 *
 *  This is an internal header file, included by other library headers.
 *  Do not attempt to use it directly. @headername{allocator}
**/

#ifndef _POL_ALLOC_TCC
#define _POL_ALLOC_TCC 1

#include <new> // for ::operator new and ::operator delete

namespace polaris
{

template<typename _Tp>
_Tp*
allocator<_Tp>::
allocate(size_type __n)
{
    return static_cast<_Tp*>(::operator new (sizeof(_Tp) * __n));
}

template<typename _Tp>
void
allocator<_Tp>::
deallocate(pointer __p)
{
    ::operator delete (static_cast<void*>(__p));
}

template<typename _Tp>
_Tp*
allocator<_Tp>::
reallocate(pointer __p, size_type __n)
{
    this->deallocate(__p);
    return this->allocate(__n);
}

template<typename _Tp>
template<typename... _Args>
_Tp*
allocator<_Tp>::
construct(_Args&&... __args)
{
    return new _Tp{__args...};
}

template<typename _Tp>
void
allocator<_Tp>::
destroy(pointer __p)
{
    delete __p;
}

template<typename _Tp>
template<typename... _Args>
_Tp*
allocator<_Tp>::
reconstruct(pointer __p, _Args&&... __args)
{
    this->destroy(__p);
    return this->construct(__args...);
}

void*
allocator<void>::
allocate(size_type __n)
{
    return ::operator new (sizeof(char) * __n);
}

void
allocator<void>::
deallocate(pointer __p)
{
    ::operator delete (__p);
}

void*
allocator<void>::
reallocate(pointer __p, size_type __n)
{
    this->deallocate(__p);
    return this->allocate(__n);
}

}

#endif /* _POL_ALLOC_TCC */
