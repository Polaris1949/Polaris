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

/** @file bits/tree.tcc
 *  This is an internal header file, included by other library headers.
 *  Do not attempt to use it directly. @headername{tree}
 */

// Written by Jingyu Zhao.

#ifndef _POL_TREE_TCC
#define _POL_TREE_TCC 1

namespace polaris
{

tree_node_base::
tree_node_base()
	: _M_parent(), _M_child()
{
}

tree_node_base*
tree_node_base::
parent() const
{
	return _M_parent;
}

tree_node_base*
tree_node_base::
child(size_type __pos) const
{
	std::list<base_type*>::iterator __it = _M_child.begin();
	while (__pos--) ++__it;
	return *__it;
}

}

#endif
