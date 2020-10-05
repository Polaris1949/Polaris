// Link-cut tree -*- C++ -*-

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

/** @file        bits/lctree.h
 *  @brief       Link-cut tree
 *  @author      Polaris Zhao
 *  @version     0.8.0
 *
 *  This is an internal header file, included by other library headers.
 *  Do not attempt to use it directly. @headername{link_cut_tree}
**/

#ifndef _POL_LCTREE_H
#define _POL_LCTREE_H 1

namespace pol
{

template<typename _Tp>
class link_cut_tree_node
    : public binary_tree_node<_Tp>
{
public:
    using base_type = binary_tree_node<_Tp>;
    using value_type = _Tp;
    using node_type = link_cut_tree_node<_Tp>;

protected:
    value_type _M_value;
    bool _M_mark;

public:
    link_cut_tree_node() = default;

    link_cut_tree_node(const value_type& __x);

    ~link_cut_tree_node() noexcept = default;

    value_type&
    value();

    const value_type&
    value() const;

    bool&
    mark();

    // TODO: Fundamental types should not have const& qualifiers
    bool
    mark() const;

    void reverse();
};

template<typename _Tp>
class link_cut_tree
{
public:
    using value_type = _Tp;
    using node_base = binary_tree_node<_Tp>;
    using node_type = link_cut_tree_node<_Tp>;
    using tree_type = link_cut_tree<_Tp>;
    using size_type = std::size_t;

private:
    std::vector<node_type*> _M_node;

public:
    link_cut_tree() = default;

    template<typename _Seq>
    link_cut_tree(const _Seq& __data);

    ~link_cut_tree() noexcept;

    template<typename _Seq>
    tree_type&
    construct(const _Seq& __data);

    tree_type&
    destroy();

    void
    cut(size_type __x, size_type __y);

    void
    link(size_type __x, size_type __y);

    void
    assign(size_type __x, const value_type& __y);

    value_type
    xor_sum(size_type __x, size_type __y);

private:
    void
    _M_push_up(node_type* __x);

    void
    _M_push_down(node_type* __x);

    bool
    _M_is_root(node_type* __x);

    void
    _M_rotate(node_type* __x);

    void
    _M_splay(node_type* __x);

    void
    _M_access(node_type* __x);

    void
    _M_make_root(node_type* __x);

    node_type*
    _M_find(node_type* __x);

    void
    _M_split(node_type* __x, node_type* __y);

    void
    _M_link(node_type* __x, node_type* __y);

    void
    _M_cut(node_type* __x, node_type* __y);

    void
    _M_assign(node_type* __x, const value_type& __y);

    value_type
    _M_xor_sum(node_type* __x, node_type* __y);
};

}

#endif /* _POL_LCTREE_H */
