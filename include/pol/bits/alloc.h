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

/** @file        bits/alloc.h
 *  @brief       Allocator support
 *  @author      Polaris Zhao
 *  @version     0.8.0
 *
 *  This is an internal header file, included by other library headers.
 *  Do not attempt to use it directly. @headername{allocator}
**/

#ifndef _POL_ALLOC_H
#define _POL_ALLOC_H 1

namespace pol
{

/** @brief  C++ allocator using @c new and @c delete
**/
class allocator
{
public:
    /** @brief    Allocate a memory block of fixed elements
     *  @param    __n  Number of elements.
     *  @return   Pointer to a memory block.
     *  @throw    std::bad_alloc  If allocation failed.
     *  @warning  Return value shall not be discarded.
    **/
    [[nodiscard]] void*
    allocate(size_t __n);

    /** @brief  Deallocate a memory block of fixed elements
     *  @param  __p  Pointer to a memory block.
    **/
    void
    deallocate(void* __p) noexcept;

    /** @brief    Reallocate a memory block of fixed elements
     *  @param    __p  Old pointer to a memory block.
     *  @param    __n  Number of elements.
     *  @return   New pointer to a memory block.
     *  @throw    std::bad_alloc  If reallocation failed.
     *  @warning  Return value shall not be discarded.
     *  @note     The old pointer would always be deallocated
     *            when macro @c POL_UNSAFE was set to 1.
    **/
    [[nodiscard]] void*
    reallocate(void* __p, size_t __n);
};

/** @brief  C++ nothrow allocator using @c new and @c delete
**/
class nt_allocator
{
public:
    [[nodiscard]] void*
    allocate(size_t __n) noexcept;

    void
    deallocate(void* __p) noexcept;

    [[nodiscard]] void*
    reallocate(void* __p, size_t __n) noexcept;
};

/** @brief  C allocator using @c malloc, @c free and @c realloc
**/
class c_allocator
{
public:
    [[nodiscard]] void*
    allocate(size_t __n);

    void
    deallocate(void* __p) noexcept;

    [[nodiscard]] void*
    reallocate(void* __p, size_t __n);
};

/** @brief  C nothrow allocator using @c malloc, @c free and @c realloc
**/
class c_nt_allocator
{
public:
    [[nodiscard]] void*
    allocate(size_t __n) noexcept;

    void
    deallocate(void* __p) noexcept;

    [[nodiscard]] void*
    reallocate(void* __p, size_t __n) noexcept;
};

/** @brief  Type-safe allocator adapter
**/
template<typename _Alloc, typename _Tp>
class typed_alloc_adapter : protected _Alloc
{
public:
    using allocator_type = _Alloc;
    using value_type = _Tp;
    using pointer = _Tp*;
    using size_type = size_t;

    /** @brief    Allocate a memory block of fixed elements
     *  @param    __n  Number of elements.
     *  @return   Pointer to a memory block.
     *  @throw    std::bad_alloc  If allocation failed.
     *  @warning  Return value shall not be discarded.
    **/
    [[nodiscard]] pointer
    allocate(size_type __n);

    /** @brief  Deallocate a memory block of fixed elements
     *  @param  __p  Pointer to a memory block.
    **/
    void
    deallocate(pointer __p) noexcept;

    /** @brief    Reallocate a memory block of fixed elements
     *  @param    __p  Old pointer to a memory block.
     *  @param    __n  Number of elements.
     *  @return   New pointer to a memory block.
     *  @throw    std::bad_alloc  If reallocation failed.
     *  @warning  Return value shall not be discarded.
     *  @note     The old pointer would always be deallocated
     *            when macro @c POL_UNSAFE was set to 1.
    **/
    [[nodiscard]] pointer
    reallocate(pointer __p, size_type __n);

    /** @brief    Construct an object
     *  @tparam   _Args   Types of parameters.
     *  @param    __args  Parameters given to constructor.
     *  @return   Pointer to an object.
     *  @warning  Return value shall not be discarded.
    **/
    template<typename... _Args>
    [[deprecated]] [[nodiscard]] pointer
    construct(_Args&&... __args);

    /** @brief  Destroy an object
     *  @param  __p  Pointer to an object.
    **/
    [[deprecated]] void
    destroy(pointer __p) noexcept;

    /** @brief    Reconstruct an object
     *  @tparam   _Args   Types of parameters.
     *  @param    __p     Old pointer to an object.
     *  @param    __args  Parameters given to constructor.
     *  @return   New pointer to an object.
     *  @warning  Return value shall not be discarded.
     *  @note     The old pointer would always be deallocated
     *            if macro @c POL_UNSAFE was set to 1.
    **/
    template<typename... _Args>
    [[deprecated]] [[nodiscard]] pointer
    reconstruct(pointer __p, _Args&&... __args);
};

template<typename _Tp>
using typed_allocator = typed_alloc_adapter<allocator, _Tp>;

template<typename _Tp>
using typed_nt_allocator = typed_alloc_adapter<nt_allocator, _Tp>;

template<typename _Tp>
using typed_c_allocator = typed_alloc_adapter<c_allocator, _Tp>;

template<typename _Tp>
using typed_c_nt_allocator = typed_alloc_adapter<c_nt_allocator, _Tp>;

template<typename _Alloc, bool _Move, bool _Equal, typename _Tp>
class std_alloc_adapter : protected _Alloc
{
public:
    using value_type = _Tp;
    using size_type = size_t;
    using difference_type = ptrdiff_t;
    using propagate_on_container_move_assignment = std::bool_constant<_Move>;
    using is_always_equal = std::bool_constant<_Equal>;

    std_alloc_adapter() noexcept = default;

    std_alloc_adapter(const std_alloc_adapter& __o) noexcept;

    template<typename _Up>
    std_alloc_adapter(const std_alloc_adapter<_Up>& __o) noexcept;

    [[nodiscard]]
    _Tp* allocate(size_t __n);

    void
    deallocate(_Tp* __p, size_t __n);

    template<typename _T1, typename _T2>
    friend bool
    operator == (const std_alloc_adapter<_T1>& __lhs, const std_alloc_adapter<_T2>& __rhs);
};

}

#endif /* _POL_ALLOC_H */
