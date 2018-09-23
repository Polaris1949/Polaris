// Chtholly tree classes -*- C++ -*-

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

/** @file        bits/chtree.h
 *  @headerfile  chtholly_tree
 *  @brief       Chtholly tree classes
 *  @author      Polaris Zhao
 *  @version     3.0
 *
 *  This is an internal header file, included by other library headers.
 *  Do not attempt to use it directly.
**/

#ifndef _POL_CHTREE_H
#define _POL_CHTREE_H 1

namespace polaris
{

template<typename _Tp>
class chtholly_tree_node
{
public:
    using size_type = std::size_t;
    using value_type = _Tp;

private:
    size_type _M_left;
    size_type _M_right;
    mutable value_type _M_data;

public:
    chtholly_tree_node() = default;
    chtholly_tree_node(size_type __l, size_type __r);
    chtholly_tree_node(size_type __l, size_type __r, const value_type& __v);

    size_type left() const;
    size_type right() const;
    value_type& data() const;
    size_type length() const;

    bool operator < (const chtholly_tree_node& __o) const;
};

template<typename _Tp>
class chtholly_tree
{
public:
    using size_type = std::size_t;
    using value_type = _Tp;
    using node_type = chtholly_tree_node<value_type>;
    using container_type = std::set<node_type>;
    using iterator = typename container_type::iterator;

private:
    container_type _M_sto;

    iterator
    _M_split(size_type __pos);

public:
    chtholly_tree() = default;

    template<typename _Seq>
    chtholly_tree(const _Seq& __data);

    template<typename _Seq>
    void
    init(const _Seq& __data);

    void
    plus(size_type __l, size_type __r, const value_type& __v);

    void
    assign(size_type __l, size_type __r, const value_type& __v);

    value_type
    rank(size_type __l, size_type __r, size_type __k);

    value_type
    pow_sum(size_type __l, size_type __r, value_type __exp, value_type __mod);
};

}

#endif /* _POL_CHTREE_H */
