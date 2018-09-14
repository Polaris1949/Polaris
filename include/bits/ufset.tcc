// Union find set implementation -*- C++ -*-

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

/** @file        bits/ufset.tcc
 *  @headerfile  ufset
 *  @brief       Union find set implementation
 *  @author      Polaris Zhao
 *  @version     3.0
 *
 *  This is an internal header file, included by other library headers.
 *  Do not attempt to use it directly.
**/

#ifndef _POL_UFSET_TCC
#define _POL_UFSET_TCC 1

namespace polaris
{

template<typename _Tp>
basic_ufset<_Tp>::
basic_ufset()
	: _M_parent{}, _M_rank{}
{}

template<typename _Tp>
_Tp&
basic_ufset<_Tp>::
parent(const value_type& __x)
{
	value_type& __res = this->_M_parent[__x];
	if (__res == value_type{}) __res = __x;
	return __res;
}

template<typename _Tp>
std::size_t&
basic_ufset<_Tp>::
rank(const value_type& __x)
{ return this->_M_rank[__x]; }

template<typename _Tp>
_Tp&
basic_ufset<_Tp>::
find(const value_type& __x)
{
	return this->parent(__x) == __x ? this->parent(__x)
		: this->parent(__x) = this->find(this->parent(__x));
}

template<typename _Tp>
bool
basic_ufset<_Tp>::
merge(const value_type& __x, const value_type& __y)
{
	value_type __rx{this->find(__x)};
	value_type __ry{this->find(__y)};

	if (__rx == __ry) return false;

	if (this->rank(__rx) < this->rank(__ry))
		this->parent(__rx) = __ry;
	else
	{
		this->parent(__ry) = __rx;

		if (this->rank(__rx) == this->rank(__ry))
			++this->rank(__rx);
	}

	return true;
}

template<typename _Tp>
bool
basic_ufset<_Tp>::
is_brother(const value_type& __x, const value_type& __y)
{ return this->find(__x) == this->find(__y); }

template<typename _Tp>
_Tp&
basic_ufset<_Tp>::
operator[] (const value_type& __x)
{ return this->find(__x); }

seq_ufset::
seq_ufset()
	: _M_parent{}, _M_rank{}
{}

seq_ufset::
seq_ufset(size_type __n)
	: _M_parent{}, _M_rank{}
{ this->init(__n); }

void
seq_ufset::
init(size_type __n)
{
	this->_M_parent.resize(__n);
	this->_M_rank.resize(__n);

	for (size_type __i{}; __i < __n; ++__i)
		this->_M_parent[__i] = __i;
}

std::size_t&
seq_ufset::
parent(const value_type& __x)
{ return this->_M_parent[__x]; }

const std::size_t&
seq_ufset::
parent(const value_type& __x) const
{ return this->_M_parent[__x]; }

std::size_t&
seq_ufset::
rank(const value_type& __x)
{ return this->_M_rank[__x]; }

const std::size_t&
seq_ufset::
rank(const value_type& __x) const
{ return this->_M_rank[__x]; }

std::size_t&
seq_ufset::
find(const value_type& __x)
{
	return this->_M_parent[__x] == __x ? this->_M_parent[__x]
		: this->_M_parent[__x] = this->find(this->_M_parent[__x]);
}

bool
seq_ufset::
merge(const value_type& __x, const value_type& __y)
{
	value_type __rx{this->find(__x)};
	value_type __ry{this->find(__y)};

	if (__rx == __ry) return false;

	if (this->_M_rank[__rx] < this->_M_rank[__ry])
		this->_M_parent[__rx] = __ry;
	else
	{
		this->_M_parent[__ry] = __rx;

		if (this->_M_rank[__rx] == this->_M_rank[__ry])
			++this->_M_rank[__rx];
	}

	return true;
}

bool
seq_ufset::
is_brother(const value_type& __x, const value_type& __y)
{ return this->find(__x) == this->find(__y); }

std::size_t&
seq_ufset::
operator[] (const value_type& __x)
{ return this->find(__x); }

}

#endif /* _POL_UFSET_TCC */
