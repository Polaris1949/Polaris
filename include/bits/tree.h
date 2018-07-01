// Tree -*- C++ -*-

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

/** @file bits/tree.h
 *  This is an internal header file, included by other library headers.
 *  Do not attempt to use it directly. @headername{tree}
 */

// Written by Jingyu Zhao.

#ifndef _POL_TREE_H
#define _POL_TREE_H 1

#include <list>

namespace polaris
{

class tree_node_base
{
public:
	typedef size_t size_type;
	typedef tree_node_base base_type;
	
private:
	base_type* _M_parent;
	std::list<base_type*> _M_child;
	
public:
	tree_node_base();
	
	base_type*
	parent() const;
	
	base_type*
	child(size_type __pos) const;
};

template<typename _Tp>
class tree_node
{
public:
	typedef _Tp value_type;
	typedef size_t size_type;
	typedef tree_node<_Tp> node_type;
	
private:
	value_type _M_storage;
	node_type* _M_parent;
	std::list<node_type*> _M_children;
	
public:
	tree_node() = default;
	tree_node(const value_type& __x);
};

template<typename _Tp>
class tree_iterator
{
public:
	typedef _Tp value_type;
	typedef size_t size_type;
	typedef tree_node<_Tp> node_type;
	typedef tree_iterator<_Tp> iterator;
	
private:
	node_type* _M_ptr;
	node_type* _M_child;
	size_type _M_cur;
	
public:
	tree_iterator();
	
	iterator&
	operator++ ();
	
	iterator
	operator++ (int);
	
	iterator&
	operator-- ();
	
	iterator
	operator-- (int);
	
	value_type&
	operator* ();
	
	const value_type&
	operator* () const;
	
	node_type*&
	operator-> ();
	
	const node_type*&
	operator-> () const;
};

template<typename _Tp>
class tree
{
public:
	typedef tree_node<_Tp> node_type;
	
private:
	node_type* _M_root;
};

}

#endif /* _POL_TREE_H */
