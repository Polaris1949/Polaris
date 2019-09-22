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

/** @brief       General allocator
 *  @tparam      _Tp  Type for dynamic memory management.
 *  @headerfile  allocator <pol/allocator>
 *
 *  This is a general allocator for dynamic memory management of a type.
 *  It supports not only low level memory management, including @c allocate(),
 *  @c deallocate() and @c reallocate(), but also object memory management,
 *  including @c construct(), @c destroy() and @c reconstruct().
**/
template<typename _Tp>
class allocator
{
public:
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
     *  @bug      The old pointer would always be deallocated,
     *            even if reallocation failed.
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
    [[nodiscard]] pointer
    construct(_Args&&... __args);

    /** @brief  Destroy an object
     *  @param  __p  Pointer to an object.
    **/
    void
    destroy(pointer __p) noexcept;

    /** @brief    Reconstruct an object
     *  @tparam   _Args   Types of parameters.
     *  @param    __p     Old pointer to an object.
     *  @param    __args  Parameters given to constructor.
     *  @return   New pointer to an object.
     *  @warning  Return value shall not be discarded.
     *  @bug      The old pointer would always be destroyed,
     *            even if recontruction failed.
    **/
    template<typename... _Args>
    [[nodiscard]] pointer
    reconstruct(pointer __p, _Args&&... __args);
};

/** @brief       Weak allocator
 *  @note        For erased types.
 *  @headerfile  allocator  <pol/allocator>
**/
template<>
class allocator<void>
{
public:
    using pointer = void*;
    using size_type = size_t;

    /** @brief  Allocate a memory block of fixed bytes.
     *  @param  __n  Number of bytes.
     *  @return   Pointer to a memory block.
     *  @throw    std::bad_alloc  If allocation failed.
     *  @warning  Return value shall not be discarded.
    **/
    [[nodiscard]] pointer
    allocate(size_type __n);

    /** @brief  Deallocate a memory block of fixed bytes
     *  @param  __p  Pointer to a memory block.
    **/
    void
    deallocate(pointer __p) noexcept;

    /** @brief    Reallocate a memory block of fixed bytes
     *  @param    __p  Old pointer to a memory block.
     *  @param    __n  Number of bytes.
     *  @return   New pointer to a memory block.
     *  @throw    std::bad_alloc  If reallocation failed.
     *  @warning  Return value shall not be discarded.
     *  @bug      The old pointer would always be deallocated,
     *            even if reallocation failed.
    **/
    [[nodiscard]] pointer
    reallocate(pointer __p, size_type __n);
};

}

#endif /* _POL_ALLOC_H */
