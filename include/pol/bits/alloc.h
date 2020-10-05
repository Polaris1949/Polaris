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
    allocator() noexcept = default;

    allocator(const allocator&) noexcept = default;

    allocator(allocator&&) noexcept = default;

    ~allocator() noexcept = default;

    /** @brief    Allocate a memory block of fixed elements
     *  @param    __n  Number of elements.
     *  @return   Pointer to a memory block.
     *  @throw    std::bad_alloc  If allocation failed.
     *  @warning  Return value shall not be discarded.
    **/
    [[nodiscard]] void*
    allocate(size_t __n) const;

    /** @brief  Deallocate a memory block of fixed elements
     *  @param  __p  Pointer to a memory block.
    **/
    void
    deallocate(void* __p) const noexcept;

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
    reallocate(void* __p, size_t __n) const;
};

/** @brief  C++ nothrow allocator using @c new and @c delete
**/
class nt_allocator
{
public:
    nt_allocator() noexcept = default;

    nt_allocator(const nt_allocator&) noexcept = default;

    nt_allocator(nt_allocator&&) noexcept = default;

    ~nt_allocator() noexcept = default;

    [[nodiscard]] void*
    allocate(size_t __n) const noexcept;

    void
    deallocate(void* __p) const noexcept;

    [[nodiscard]] void*
    reallocate(void* __p, size_t __n) const noexcept;
};

/** @brief  C allocator using @c malloc, @c free and @c realloc
**/
class c_allocator
{
public:
    c_allocator() noexcept = default;

    c_allocator(const c_allocator&) noexcept = default;

    c_allocator(c_allocator&&) noexcept = default;

    ~c_allocator() noexcept = default;

    [[nodiscard]] void*
    allocate(size_t __n) const;

    void
    deallocate(void* __p) const noexcept;

    [[nodiscard]] void*
    reallocate(void* __p, size_t __n) const;
};

/** @brief  C nothrow allocator using @c malloc, @c free and @c realloc
**/
class c_nt_allocator
{
public:
    c_nt_allocator() noexcept = default;

    c_nt_allocator(const c_nt_allocator&) noexcept = default;

    c_nt_allocator(c_nt_allocator&&) noexcept = default;

    ~c_nt_allocator() noexcept = default;

    [[nodiscard]] void*
    allocate(size_t __n) const noexcept;

    void
    deallocate(void* __p) const noexcept;

    [[nodiscard]] void*
    reallocate(void* __p, size_t __n) const noexcept;
};

template<typename _Alloc, typename _Fun1, typename _Fun2, typename _Fun3>
class debug_alloc_adapter : protected _Alloc
{
public:
    debug_alloc_adapter() = default;

    debug_alloc_adapter(_Fun1&& __f1, _Fun2&& __f2, _Fun3&& __f3);

    [[nodiscard]] void*
    allocate(size_t __n);

    void
    deallocate(void* __p);

    [[nodiscard]] void*
    reallocate(void* __p, size_t __n);

protected:
    _Fun1 _M_f1;
    _Fun2 _M_f2;
    _Fun3 _M_f3;
};

constexpr auto __debug_alloc_f1 = [](size_t __n, void* __ret)
{ println(stderr, "allocate({}) = {}", __n, __ret); };
constexpr auto __debug_alloc_f2 = [](void* __p)
{ println(stderr, "deallocate({})", __p); };
constexpr auto __debug_alloc_f3 = [](void* __p, size_t __n, void* __ret)
{ println(stderr, "reallocate({}, {}) = {}", __p, __n, __ret); };

template<typename _Alloc>
using debug_alloc_default_adapter = debug_alloc_adapter<_Alloc,
    decltype(__debug_alloc_f1), decltype(__debug_alloc_f2),
    decltype(__debug_alloc_f3)>;
using debug_allocator = debug_alloc_default_adapter<allocator>;
using debug_nt_allocator = debug_alloc_default_adapter<nt_allocator>;
using debug_c_allocator = debug_alloc_default_adapter<c_allocator>;
using debug_c_nt_allocator = debug_alloc_default_adapter<c_nt_allocator>;

/** @brief  Type-safe allocator adapter
**/
template<typename _Tp, typename _Alloc>
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
using typed_allocator = typed_alloc_adapter<_Tp, allocator>;

template<typename _Tp>
using typed_nt_allocator = typed_alloc_adapter<_Tp, nt_allocator>;

template<typename _Tp>
using typed_c_allocator = typed_alloc_adapter<_Tp, c_allocator>;

template<typename _Tp>
using typed_c_nt_allocator = typed_alloc_adapter<_Tp, c_nt_allocator>;

template<typename _Tp, typename _Alloc, bool _Move, bool _Equal>
class std_alloc_adapter : protected _Alloc
{
public:
    using value_type = _Tp;
    using size_type = size_t;
    using difference_type = ptrdiff_t;
    using propagate_on_container_move_assignment = std::bool_constant<_Move>;
    using is_always_equal = std::bool_constant<_Equal>;

    template<typename _Up>
    struct rebind
    { using other = std_alloc_adapter<_Up, _Alloc, _Move, _Equal>; };

    std_alloc_adapter() noexcept = default;

    std_alloc_adapter(const std_alloc_adapter& __o) noexcept;

    template<typename _Up>
    std_alloc_adapter(const std_alloc_adapter<_Up, _Alloc, _Move, _Equal>& __o) noexcept;

    [[nodiscard]] _Tp*
    allocate(size_t __n);

    void
    deallocate(_Tp* __p, size_t __n);

    template<typename _T1, typename _T2, typename _Alloc0, bool _Move0, bool _Equal0>
    friend bool
    operator == (const std_alloc_adapter<_T1, _Alloc0, _Move0, _Equal0>& __lhs,
        const std_alloc_adapter<_T2, _Alloc0, _Move0, _Equal0>& __rhs);
};

template<typename _Tp>
using std_allocator = std_alloc_adapter<_Tp, allocator, true, true>;
template<typename _Tp>
using std_nt_allocator = std_alloc_adapter<_Tp, nt_allocator, true, true>;
template<typename _Tp>
using std_c_allocator = std_alloc_adapter<_Tp, c_allocator, true, true>;
template<typename _Tp>
using std_c_nt_allocator = std_alloc_adapter<_Tp, c_nt_allocator, true, true>;

// NOTE: Is _Equal == true? Consider callback functions?
template<typename _Tp>
using std_debug_allocator = std_alloc_adapter<_Tp, debug_allocator, true, true>;
template<typename _Tp>
using std_debug_nt_allocator = std_alloc_adapter<_Tp, debug_nt_allocator, true, true>;
template<typename _Tp>
using std_debug_c_allocator = std_alloc_adapter<_Tp, debug_c_allocator, true, true>;
template<typename _Tp>
using std_debug_c_nt_allocator = std_alloc_adapter<_Tp, debug_c_nt_allocator, true, true>;

// TODO: Make this more customizable
template<typename _Alloc>
_Alloc&
get_global_alloc()
{
    static _Alloc __alloc;
    return __alloc;
}

}

#endif /* _POL_ALLOC_H */
