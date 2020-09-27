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
 *  @version     0.8.0
 *
 *  This is an internal header file, included by other library headers.
 *  Do not attempt to use it directly. @headername{allocator}
**/

#ifndef _POL_ALLOC_TCC
#define _POL_ALLOC_TCC 1

namespace pol
{

inline void*
allocator::
allocate(size_t __n)
{ return ::operator new (__n); }

inline void
allocator::
deallocate(void* __p) noexcept
{ ::operator delete (__p); }

inline void*
allocator::
reallocate(void* __p, size_t __n)
{
#if POL_UNSAFE
    this->deallocate(__p);
    return this->allocate(__n);
#else
    void* __tmp = this->allocate(__n);
    this->deallocate(__p);
    return __tmp;
#endif
}

inline void*
nt_allocator::
allocate(size_t __n) noexcept
{ return ::operator new (__n, std::nothrow); }

inline void
nt_allocator::
deallocate(void* __p) noexcept
{ ::operator delete (__p); }

inline void*
nt_allocator::
reallocate(void* __p, size_t __n) noexcept
{
    void* __tmp = this->allocate(__n);
    if (__tmp) this->deallocate(__p);
    return __tmp;
}

inline void*
c_allocator::
allocate(size_t __n)
{
    void* __tmp = std::malloc(__n);
    if (!__tmp) throw std::bad_alloc();
    return __tmp;
}

inline void
c_allocator::
deallocate(void* __p) noexcept
{ std::free(__p); }

inline void*
c_allocator::
reallocate(void* __p, size_t __n)
{ 
    void* __tmp = std::realloc(__p, __n);
    if (!__tmp) throw std::bad_alloc();
    return __tmp;
}

inline void*
c_nt_allocator::
allocate(size_t __n) noexcept
{ return std::malloc(__n); }

inline void
c_nt_allocator::
deallocate(void* __p) noexcept
{ std::free(__p); }

inline void*
c_nt_allocator::
reallocate(void* __p, size_t __n) noexcept
{ return std::realloc(__p, __n); }

template<typename _Alloc, typename _Tp>
inline _Tp*
typed_alloc_adapter<_Alloc, _Tp>::
allocate(size_type __n)
{ return static_cast<_Tp*>(this->_Alloc::allocate(__n)); }

template<typename _Alloc, typename _Tp>
inline void
typed_alloc_adapter<_Alloc, _Tp>::
deallocate(pointer __p) noexcept
{ this->_Alloc::deallocate(static_cast<void*>(__p)); }

template<typename _Alloc, typename _Tp>
inline _Tp*
typed_alloc_adapter<_Alloc, _Tp>::
reallocate(pointer __p, size_type __n)
{
    if constexpr (has_reallocate<_Alloc>)
    {
        return static_cast<_Tp*>(this->_Alloc::reallocate(
            static_cast<void*>(__p), __n));
    }
    else
    {
#if POL_UNSAFE
        this->deallocate(__p);
        return this->allocate(__n);
#else
        void* __tmp = this->allocate(__n);
        this->deallocate(__p);
        return __tmp;
#endif
    }
}

template<typename _Alloc, typename _Tp>
template<typename... _Args>
inline _Tp*
typed_alloc_adapter<_Alloc, _Tp>::
construct(_Args&&... __args)
{
    _Tp* __mem = this->allocate(sizeof(_Tp));
    return new (__mem) _Tp{std::forward<_Args&&>(__args)...};
}

template<typename _Alloc, typename _Tp>
void
typed_alloc_adapter<_Alloc, _Tp>::
destroy(pointer __p) noexcept
{
    __p->~_Tp();
    this->deallocate(__p);
}

template<typename _Alloc, typename _Tp>
template<typename... _Args>
_Tp*
typed_alloc_adapter<_Alloc, _Tp>::
reconstruct(pointer __p, _Args&&... __args)
{
#if POL_UNSAFE
    this->destroy(__p);
    return this->construct(std::forward<_Args&&>(__args)...);
#else
    _Tp* __tmp = this->construct(std::forward<_Args&&>(__args)...);
    this->destroy(__p);
    return __tmp;
#endif
}

}

#endif /* _POL_ALLOC_TCC */
