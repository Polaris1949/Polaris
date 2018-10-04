// Binary tree implementation -*- C++ -*-

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

/** @file        bits/bintree.tcc
 *  @headerfile  binary_tree
 *  @brief       Binary tree implementation
 *  @author      Polaris Zhao
 *  @version     3.0
 *  @todo        Incomplete.
 *
 *  This is an internal header file, included by other library headers.
 *  Do not attempt to use it directly.
**/

#ifndef _POL_BINTREE_TCC
#define _POL_BINTREE_TCC 1

namespace polaris
{

template<typename _Tp>
binary_tree_node<_Tp>::
binary_tree_node()
	: _M_parent{nullptr}, _M_left{nullptr}, _M_right{nullptr}, _M_data{}
{}

template<typename _Tp>
binary_tree_node<_Tp>::
binary_tree_node(const value_type& __x)
	: _M_parent{nullptr}, _M_left{nullptr}, _M_right{nullptr}, _M_data{__x}
{}

template<typename _Tp>
binary_tree_node<_Tp>::
~binary_tree_node() noexcept
{}

template<typename _Tp>
inline binary_tree_node<_Tp>&
binary_tree_node<_Tp>::
construct(const value_type& __x)
{
	this->_M_construct(__x);
	return *this;
}

template<typename _Tp>
inline binary_tree_node<_Tp>&
binary_tree_node<_Tp>::
destroy()
{
	this->_M_destroy();
	return *this;
}

template<typename _Tp>
inline binary_tree_node<_Tp>*&
binary_tree_node<_Tp>::
parent()
{ return this->_M_parent; }

template<typename _Tp>
inline const binary_tree_node<_Tp>*&
binary_tree_node<_Tp>::
parent() const
{ return this->_M_parent; }

template<typename _Tp>
inline binary_tree_node<_Tp>*&
binary_tree_node<_Tp>::
child(bool __x)
{ return __x ? this->right() : this->left(); }

template<typename _Tp>
inline const binary_tree_node<_Tp>*&
binary_tree_node<_Tp>::
child(bool __x) const
{ return __x ? this->right() : this->left(); }

template<typename _Tp>
inline binary_tree_node<_Tp>*&
binary_tree_node<_Tp>::
left()
{ return this->_M_left; }

template<typename _Tp>
inline const binary_tree_node<_Tp>*&
binary_tree_node<_Tp>::
left() const
{ return this->_M_left; }

template<typename _Tp>
inline binary_tree_node<_Tp>*&
binary_tree_node<_Tp>::
right()
{ return this->_M_right; }

template<typename _Tp>
inline const binary_tree_node<_Tp>*&
binary_tree_node<_Tp>::
right() const
{ return this->_M_right; }

template<typename _Tp>
inline _Tp&
binary_tree_node<_Tp>::
data()
{ return this->_M_data; }

template<typename _Tp>
inline const _Tp&
binary_tree_node<_Tp>::
data() const
{ return this->_M_data; }

template<typename _Tp>
inline bool
binary_tree_node<_Tp>::
is_branch() const
{ return this->degree() > 0; }

template<typename _Tp>
inline bool
binary_tree_node<_Tp>::
is_leaf() const
{ return this->degree() == 0; }

template<typename _Tp>
inline std::size_t
binary_tree_node<_Tp>::
degree() const
{
	return size_type{this->_M_left != nullptr}
		+ size_type{this->_M_right != nullptr};
}

template<typename _Tp>
void
binary_tree_node<_Tp>::
_M_construct(const value_type& __x)
{
	new (&this->data()) value_type{__x};
}

template<typename _Tp>
void
binary_tree_node<_Tp>::
_M_destroy()
{
	if (this->left())
	{
		delete this->left();
		this->left() = nullptr;
	}

	if (this->right())
	{
		delete this->right();
		this->right() = nullptr;
	}

	this->data().~value_type();
}

template<typename _Tp>
template<typename _Seq>
inline binary_tree<_Tp>&
binary_tree<_Tp>::
construct(const _Seq& __data)
{
	this->_M_construct(this->_M_root, __data);
	return *this;
}

template<typename _Tp>
inline binary_tree<_Tp>&
binary_tree<_Tp>::
destroy()
{
	this->_M_destroy(this->_M_root);
	return *this;
}

template<typename _Tp>
template<typename _Seq>
void
binary_tree<_Tp>::
_M_construct(node_type* __root, const _Seq& __data)
{
	// TODO...
}

template<typename _Tp>
void
binary_tree<_Tp>::
_M_destroy(node_type* __root)
{
	// TODO...
}

}

#endif
