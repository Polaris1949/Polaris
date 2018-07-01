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

/** @file bits/bintree.h
 *  This is an internal header file, included by other library headers.
 *  Do not attempt to use it directly. @headername{binary_tree}
 */

// Written by Jingyu Zhao.

#ifndef _POL_BINTREE_H
#define _POL_BINTREE_H 1

#include <functional>

namespace polaris
{

template<typename _Tp>
class binary_tree_node
{
public:
	typedef _Tp                    value_type;
	typedef binary_tree_node<_Tp>  node_type;
	typedef std::size_t            size_type;
	
private:
	node_type* _M_parent;
	node_type* _M_left;
	node_type* _M_right;
	value_type _M_data;
	
public:
	binary_tree_node();
	
	binary_tree_node(const value_type& __x);
	
	~binary_tree_node() noexcept;
	
	node_type&
	construct(const value_type& __x);
	
	node_type&
	destroy();
	
	node_type*&
	parent();
	
	const node_type*&
	parent() const;
	
	node_type*&
	left();
	
	const node_type*&
	left() const;
	
	node_type*&
	right();
	
	const node_type*&
	right() const;
	
	value_type&
	data();
	
	const value_type&
	data() const;
	
	bool
	is_leaf() const;
};

template<typename _Tp>
class binary_tree
{
public:
	typedef _Tp value_type;
	typedef binary_tree_node<_Tp> node_type;
	typedef binary_tree<_Tp> tree_type;
	typedef std::size_t size_type;
	
private:
	node_type* _M_root;
	
public:
	binary_tree();
	
	template<typename _Seq>
	binary_tree(const _Seq& __data);
	
private:
	template<typename _Seq>
	void
	_M_construct(node_type* __root, const _Seq& __data);
};

}

#endif
