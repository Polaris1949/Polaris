// Binary tree -*- C++ -*-

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

/** @file        bits/bintree.h
 *  @brief       Binary tree
 *  @author      Polaris Zhao
 *  @version     0.8.0
 *  @todo        Incomplete.
 *
 *  This is an internal header file, included by other library headers.
 *  Do not attempt to use it directly. @headername{binary_tree}
**/

#ifndef _POL_BINTREE_H
#define _POL_BINTREE_H 1

namespace pol
{

// TODO: Allocator support (optional?)
// 1. Make it a template parameter [static/member?]
// 2. Make it a function parameter [maybe better?]
#if POL_NEWLIB
template<typename _Alloc>
#endif
class binary_tree_node_base
{
public:
    using base_type = binary_tree_node_base;
    using size_type = size_t;
#if POL_NEWLIB
    using allocator_type = _Alloc;
#endif

protected:
    base_type* _M_parent;
    base_type* _M_left;
    base_type* _M_right;
#if POL_NEWLIB
    // TODO: Static approach?
    _Alloc* _M_alloc;
#endif

public:
    binary_tree_node_base() noexcept;

    ~binary_tree_node_base() noexcept = default;

    base_type*&
    parent() noexcept;

    base_type*
    parent() const noexcept;

    base_type*&
    child(bool __n) noexcept;

    base_type*
    child(bool __n) const noexcept;

    base_type*&
    child(size_type __n);

    base_type*
    child(size_type __n) const;

    template<typename _IntTp>
    base_type*&
    child(_IntTp __n);

    template<typename _IntTp>
    base_type*
    child(_IntTp __n) const;

    base_type*&
    left() noexcept;

    base_type*
    left() const noexcept;

    base_type*&
    left_d();

    template<typename _Al>
    base_type*&
    left_d(_Al& __alloc);

    base_type*&
    right() noexcept;

    base_type*
    right() const noexcept;

    base_type*&
    right_d();

    template<typename _Al>
    base_type*&
    right_d(_Al& __alloc);

    bool
    is_branch() const noexcept;

    bool
    is_leaf() const noexcept;

    size_type
    degree() const noexcept;

    size_type
    depth() const noexcept;
};

// @binary_tree_node
template<typename _Tp>
class binary_tree_node : public binary_tree_node_base
{
public:
    using value_type = _Tp;
    using base_type = binary_tree_node_base;
    using node_type = binary_tree_node<_Tp>;
    using size_type = size_t;

protected:
    value_type _M_data;

public:
    binary_tree_node();

    binary_tree_node(const value_type& __x);

    binary_tree_node(value_type&& __x);

    ~binary_tree_node() noexcept = default;

    node_type&
    construct(const value_type& __x);

    node_type&
    destroy();

    node_type&
    assign(const value_type& __x);

    node_type&
    assign(value_type&& __x);

    node_type&
    operator = (const value_type& __x);

    node_type&
    operator = (value_type&& __x);

    node_type*&
    parent() noexcept;

    node_type*
    parent() const noexcept;

    node_type*&
    child(bool __n) noexcept;

    node_type*
    child(bool __n) const noexcept;

    node_type*&
    child(size_type __n);

    node_type*
    child(size_type __n) const;

    template<typename _IntTp>
    node_type*&
    child(_IntTp __n);

    template<typename _IntTp>
    node_type*
    child(_IntTp __n) const;

    node_type*&
    left() noexcept;

    node_type*
    left() const noexcept;

    template<typename _Al>
    node_type*&
    left_d(_Al& __alloc);

    node_type*&
    right() noexcept;

    node_type*
    right() const noexcept;

    template<typename _Al>
    node_type*&
    right_d(_Al& __alloc);

    value_type&
    data() noexcept;

    value_type
    data() const noexcept;

private:
    void
    _M_construct(std::string_view __s);
#if POL_NEWLIB
    template<typename _Al>
    void
    _M_construct(std::string_view __s, _Al& __a);
#endif

    // TODO: Remove this.
    void
    _M_construct(const value_type& __x);

    // NOTE: Only destroy child nodes.
    // TODO: Using global allocator?
    void
    _M_destroy();
#if POL_NEWLIB
    // TODO: With allocator.
    template<typename _Al>
    void
    _M_destroy(_Al& __a);
#endif
};

template<typename _Tp>
class binary_tree
{
public:
    using value_type = _Tp;
    using base_type = binary_tree_node_base;
    using node_type = binary_tree_node<_Tp>;
    using tree_type = binary_tree<_Tp>;
    using size_type = size_t;

protected:
    node_type* _M_root;

public:
    binary_tree();

    binary_tree(node_type* __root);

    template<typename _Seq>
    binary_tree(const _Seq& __data);

    ~binary_tree() noexcept;

    template<typename _Seq>
    tree_type&
    construct(const _Seq& __data);

    tree_type&
    destroy();

    size_type
    degree() const;

    node_type*
    root() const;

    template<typename _Func>
    void
    preorder_travel(_Func&& __f);

    template<typename _Func>
    void
    postorder_travel(_Func&& __f);

private:
    template<typename _Seq>
    void
    _M_construct(node_type* __root, const _Seq& __data);

    void
    _M_destroy(node_type* __root);
};

}

#endif /* _POL_BINTREE_H */
