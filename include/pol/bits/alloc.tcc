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
allocate(size_t __n) const
{ return ::operator new (__n); }

inline void
allocator::
deallocate(void* __p) const noexcept
{ ::operator delete (__p); }

inline void*
allocator::
reallocate(void* __p, size_t __n) const
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
allocate(size_t __n) const noexcept
{ return ::operator new (__n, std::nothrow); }

inline void
nt_allocator::
deallocate(void* __p) const noexcept
{ ::operator delete (__p); }

inline void*
nt_allocator::
reallocate(void* __p, size_t __n) const noexcept
{
    void* __tmp = this->allocate(__n);
    if (__tmp) this->deallocate(__p);
    return __tmp;
}

inline void*
c_allocator::
allocate(size_t __n) const
{
    void* __tmp = std::malloc(__n);
    if (!__tmp) throw std::bad_alloc();
    return __tmp;
}

inline void
c_allocator::
deallocate(void* __p) const noexcept
{ std::free(__p); }

inline void*
c_allocator::
reallocate(void* __p, size_t __n) const
{ 
    void* __tmp = std::realloc(__p, __n);
    if (!__tmp) throw std::bad_alloc();
    return __tmp;
}

inline void*
c_nt_allocator::
allocate(size_t __n) const noexcept
{ return std::malloc(__n); }

inline void
c_nt_allocator::
deallocate(void* __p) const noexcept
{ std::free(__p); }

inline void*
c_nt_allocator::
reallocate(void* __p, size_t __n) const noexcept
{ return std::realloc(__p, __n); }

template<typename _Alloc, typename _Fun1, typename _Fun2, typename _Fun3>
debug_alloc_adapter<_Alloc, _Fun1, _Fun2, _Fun3>::
debug_alloc_adapter(_Fun1&& __f1, _Fun2&& __f2, _Fun3&& __f3)
    : _M_f1(std::move(__f1)), _M_f2(std::move(__f2)), _M_f3(std::move(__f3))
{ }

template<typename _Alloc, typename _Fun1, typename _Fun2, typename _Fun3>
void*
debug_alloc_adapter<_Alloc, _Fun1, _Fun2, _Fun3>::
allocate(size_t __n)
{
    void* __ret = nullptr;
    std::exception_ptr __eptr;
    try { __ret = this->_Alloc::allocate(__n); }
    catch (...) { __eptr = std::current_exception(); }
    this->_M_f1(__n,  __ret);
    if (__eptr) std::rethrow_exception(__eptr);
    return __ret;
}

template<typename _Alloc, typename _Fun1, typename _Fun2, typename _Fun3>
void
debug_alloc_adapter<_Alloc, _Fun1, _Fun2, _Fun3>::
deallocate(void* __p)
{
    std::exception_ptr __eptr;
    try { this->_Alloc::deallocate(__p); }
    catch (...) { __eptr = std::current_exception(); }
    this->_M_f2(__p);
    if (__eptr) std::rethrow_exception(__eptr);
}

template<typename _Alloc, typename _Fun1, typename _Fun2, typename _Fun3>
void*
debug_alloc_adapter<_Alloc, _Fun1, _Fun2, _Fun3>::
reallocate(void* __p, size_t __n)
{
    void* __ret = nullptr;
    std::exception_ptr __eptr;
    try { __ret = this->_Alloc::reallocate(__p, __n); }
    catch (...) { __eptr = std::current_exception(); }
    this->_M_f3(__p, __n, __ret);
    if (__eptr) std::rethrow_exception(__eptr);
    return __ret;
}

template<typename _Tp, typename _Alloc>
inline _Tp*
typed_alloc_adapter<_Tp, _Alloc>::
allocate(size_type __n)
{ return static_cast<_Tp*>(this->_Alloc::allocate(__n)); }

template<typename _Tp, typename _Alloc>
inline void
typed_alloc_adapter<_Tp, _Alloc>::
deallocate(pointer __p) noexcept
{ this->_Alloc::deallocate(static_cast<void*>(__p)); }

template<typename _Tp, typename _Alloc>
inline _Tp*
typed_alloc_adapter<_Tp, _Alloc>::
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

template<typename _Tp, typename _Alloc>
template<typename... _Args>
inline _Tp*
typed_alloc_adapter<_Tp, _Alloc>::
construct(_Args&&... __args)
{
    _Tp* __mem = this->allocate(sizeof(_Tp));
    return new (__mem) _Tp{std::forward<_Args&&>(__args)...};
}

template<typename _Tp, typename _Alloc>
void
typed_alloc_adapter<_Tp, _Alloc>::
destroy(pointer __p) noexcept
{
    __p->~_Tp();
    this->deallocate(__p);
}

template<typename _Tp, typename _Alloc>
template<typename... _Args>
_Tp*
typed_alloc_adapter<_Tp, _Alloc>::
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

template<typename _Tp, typename _Alloc, bool _Move, bool _Equal>
std_alloc_adapter<_Tp, _Alloc, _Move, _Equal>::
std_alloc_adapter(const std_alloc_adapter& __o) noexcept
    : _Alloc(static_cast<_Alloc>(__o))
{ }

template<typename _Tp, typename _Alloc, bool _Move, bool _Equal>
template<typename _Up>
std_alloc_adapter<_Tp, _Alloc, _Move, _Equal>::
std_alloc_adapter(const std_alloc_adapter<_Up, _Alloc, _Move, _Equal>& __o) noexcept
    : _Alloc(static_cast<_Alloc>(__o))
{ }

template<typename _Tp, typename _Alloc, bool _Move, bool _Equal>
_Tp*
std_alloc_adapter<_Tp, _Alloc, _Move, _Equal>::
allocate(size_t __n)
{
    return static_cast<_Tp*>(this->_Alloc::allocate(sizeof(_Tp) * __n));
}

template<typename _Tp, typename _Alloc, bool _Move, bool _Equal>
void
std_alloc_adapter<_Tp, _Alloc, _Move, _Equal>::
deallocate(_Tp* __p, [[maybe_unused]] size_t __n)
{
    if constexpr (has_deallocate_1<_Alloc>)
        return this->_Alloc::deallocate(static_cast<void*>(__p));
    else // has_deallocate_2<_Alloc>
        return this->_Alloc::deallocate(static_cast<void*>(__p), sizeof(_Tp) * __n);
}

template<typename _T1, typename _T2, typename _Alloc0, bool _Move0, bool _Equal0>
bool
operator == (const std_alloc_adapter<_T1, _Alloc0, _Move0, _Equal0>& __lhs,
    const std_alloc_adapter<_T2, _Alloc0, _Move0, _Equal0>& __rhs)
{
    if constexpr (_Equal0)
        return true;
    else
        return static_cast<_Alloc0>(__lhs) == static_cast<_Alloc0>(__rhs);
}

}

#endif /* _POL_ALLOC_TCC */
