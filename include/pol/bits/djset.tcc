// Disjoint set data structure -*- C++ -*-

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

/** @file        bits/djset.tcc
 *  @brief       Disjoint set data structure
 *  @author      Polaris Zhao
 *  @version     0.8.0
 *
 *  This is an internal header file, included by other library headers.
 *  Do not attempt to use it directly. @headername{djset}
**/

#ifndef _POL_DJSET_TCC
#define _POL_DJSET_TCC 1

namespace pol
{

template<typename _Tp>
_Tp
djset_data_node_base<_Tp>::
parent() const noexcept
{ return this->_M_parent; }

template<typename _Tp>
_Tp&
djset_data_node_base<_Tp>::
parent_d() noexcept
{ return this->_M_parent; }

template<typename _Tp, typename _Rank>
_Rank
djset_data_node<_Tp, _Rank>::
rank() const noexcept
{ return this->_M_rank; }

template<typename _Tp, typename _Rank>
_Rank&
djset_data_node<_Tp, _Rank>::
rank_d() noexcept
{ return this->_M_rank; }

template<typename _Tp>
uintptr_t
djset_iter_node_base<_Tp>::
parent() const noexcept
{ return this->_M_parent; }

template<typename _Tp>
uintptr_t&
djset_iter_node_base<_Tp>::
parent_d() noexcept
{ return this->_M_parent; }

template<typename _Tp, typename _Rank>
_Rank
djset_iter_node<_Tp, _Rank>::
rank() const noexcept
{ return this->_M_rank; }

template<typename _Tp, typename _Rank>
_Rank&
djset_iter_node<_Tp, _Rank>::
rank_d() noexcept
{ return this->_M_rank; }

template<typename _Tp, typename _Rank>
seq_djset<_Tp, _Rank>::
seq_djset(size_type __n)
	: _M_data{}
{ this->init(__n); }

template<typename _Tp, typename _Rank>
void
seq_djset<_Tp, _Rank>::
init(size_type __n)
{
	this->_M_data.resize(__n);

	for (size_t __i{}; __i < __n; ++__i)
		this->parent(__i) = __i;
}

template<typename _Tp, typename _Rank>
void
seq_djset<_Tp, _Rank>::
clear() noexcept
{ this->_M_data.clear(); }

template<typename _Tp, typename _Rank>
_Tp&
seq_djset<_Tp, _Rank>::
parent(const value_type& __x)
{ return this->_M_data[__x].parent_d(); }

template<typename _Tp, typename _Rank>
const _Tp&
seq_djset<_Tp, _Rank>::
parent(const value_type& __x) const
{ return this->_M_data[__x].parent(); }

template<typename _Tp, typename _Rank>
_Rank&
seq_djset<_Tp, _Rank>::
rank(const value_type& __x)
{ return this->_M_data[__x].rank_d(); }

template<typename _Tp, typename _Rank>
const _Rank&
seq_djset<_Tp, _Rank>::
rank(const value_type& __x) const
{ return this->_M_data[__x].rank(); }

template<typename _Tp, typename _Rank>
_Tp&
seq_djset<_Tp, _Rank>::
find(const value_type& __x)
{
    _Tp& __p{this->parent(__x)};
	return __p == __x ? __p : __p = this->find(__p);
}

template<typename _Tp, typename _Rank>
bool
seq_djset<_Tp, _Rank>::
merge(const value_type& __x, const value_type& __y)
{
	_Tp& __px{this->find(__x)};
	_Tp& __py{this->find(__y)};

	if (__px == __py)
		return false;

	if (this->rank(__px) < this->rank(__py))
		this->parent(__px) = __py;
	else
	{
		this->parent(__py) = __px;

		if (this->rank(__px) == this->rank(__py))
			++this->rank(__px);
	}

	return true;
}

template<typename _Tp, typename _Rank>
bool
seq_djset<_Tp, _Rank>::
is_sibling(const value_type& __x, const value_type& __y)
{ return this->find(__x) == this->find(__y); }

template<typename _Tp, typename _Rank>
size_t
seq_djset<_Tp, _Rank>::
size() const noexcept
{ return this->_M_data.size(); }

template<typename _Tp, typename _Rank>
bool
seq_djset<_Tp, _Rank>::
empty() const noexcept
{ return this->_M_data.empty(); }

template<typename _Tp, typename _Rank>
_Tp&
seq_djset<_Tp, _Rank>::
at(const value_type& __x)
{
	expect(__x < this->size(), "runtime error: out of range");
	return this->find(__x);
}

template<typename _Tp, typename _Rank>
_Tp&
seq_djset<_Tp, _Rank>::
operator[] (const value_type& __x)
{ return this->find(__x); }

template<typename _Tp>
seq_djset<_Tp, void>::
seq_djset(size_type __n)
	: _M_data{}
{ this->init(__n); }

template<typename _Tp>
void
seq_djset<_Tp, void>::
init(size_type __n)
{
	this->_M_data.resize(__n);

	for (size_t __i{}; __i < __n; ++__i)
		this->parent(__i) = __i;
}

template<typename _Tp>
void
seq_djset<_Tp, void>::
clear() noexcept
{ this->_M_data.clear(); }

template<typename _Tp>
_Tp&
seq_djset<_Tp, void>::
parent(const value_type& __x)
{ return this->_M_data[__x].parent_d(); }

template<typename _Tp>
const _Tp&
seq_djset<_Tp, void>::
parent(const value_type& __x) const
{ return this->_M_data[__x].parent(); }

template<typename _Tp>
_Tp&
seq_djset<_Tp, void>::
find(const value_type& __x)
{
    _Tp& __p{this->parent(__x)};
	return __p == __x ? __p : __p = this->find(__p);
}

template<typename _Tp>
bool
seq_djset<_Tp, void>::
merge(const value_type& __x, const value_type& __y)
{
	_Tp& __px{this->find(__x)};
	_Tp& __py{this->find(__y)};

	if (__px == __py)
		return false;

	this->parent(__py) = __px;
	return true;
}

template<typename _Tp>
bool
seq_djset<_Tp, void>::
is_sibling(const value_type& __x, const value_type& __y)
{ return this->find(__x) == this->find(__y); }

template<typename _Tp>
size_t
seq_djset<_Tp, void>::
size() const noexcept
{ return this->_M_data.size(); }

template<typename _Tp>
bool
seq_djset<_Tp, void>::
empty() const noexcept
{ return this->_M_data.empty(); }

template<typename _Tp>
_Tp&
seq_djset<_Tp, void>::
at(const value_type& __x)
{
	expect(__x < this->size(), "runtime error: out of range");
	return this->find(__x);
}

template<typename _Tp>
_Tp&
seq_djset<_Tp, void>::
operator[] (const value_type& __x)
{ return this->find(__x); }

template<typename _Tp, typename _Rank>
uintptr_t
tree_djset<_Tp, _Rank>::
_S_itou(iterator __i) noexcept
{ return bit_cast<uintptr_t>(__i); }

template<typename _Tp, typename _Rank>
std::map<_Tp, djset_iter_node<_Tp, _Rank>>::iterator
tree_djset<_Tp, _Rank>::
_S_utoi(uintptr_t __u) noexcept
{ return bit_cast<iterator>(__u); }

template<typename _Tp, typename _Rank>
bool
tree_djset<_Tp, _Rank>::
insert(const value_type& __x)
{
	std::pair<iterator, bool> __res{this->_M_data.insert({__x, node_type{}})};
	if (!__res.second) return false;
	__res.first->second.parent_d() = _S_itou(__res.first);
	return true;
}

template<typename _Tp, typename _Rank>
uintptr_t&
tree_djset<_Tp, _Rank>::
parent_d(const uintptr_t& __x)
{
	return _S_utoi(__x)->second.parent_d();
}

template<typename _Tp, typename _Rank>
_Tp
tree_djset<_Tp, _Rank>::
parent(const value_type& __x)
{
	iterator __it{this->_M_data.find(__x)};
	assert(__it != this->_M_data.end(),
		"runtime error: element not found");
	return _S_utoi(this->parent_d(_S_itou(__it)))->first;
}

template<typename _Tp, typename _Rank>
_Rank&
tree_djset<_Tp, _Rank>::
rank_d(const uintptr_t& __x)
{
	return _S_utoi(__x)->second.rank_d();
}

template<typename _Tp, typename _Rank>
_Rank
tree_djset<_Tp, _Rank>::
rank(const value_type& __x)
{
	iterator __it{this->_M_data.find(__x)};
	assert(__it != this->_M_data.end(),
		"runtime error: element not found");
	return this->rank_d(_S_itou(__it));
}

template<typename _Tp, typename _Rank>
uintptr_t&
tree_djset<_Tp, _Rank>::
find_d(const uintptr_t& __x)
{
	uintptr_t& __p{this->parent_d(__x)};
	return __p == __x ? __p : __p = this->find_d(__p);
}

template<typename _Tp, typename _Rank>
_Tp
tree_djset<_Tp, _Rank>::
find(const value_type& __x)
{
	iterator __it{this->_M_data.find(__x)};
	assert(__it != this->_M_data.end(),
		"runtime error: element not found");
	return _S_utoi(_S_utoi(this->find_d(_S_itou(__it)))
		->second.parent())->first;
}

template<typename _Tp, typename _Rank>
bool
tree_djset<_Tp, _Rank>::
merge(const value_type& __x, const value_type& __y)
{
	iterator __ix{this->_M_data.find(__x)};
	assert(__ix != this->_M_data.end(),
		"runtime error: element __x not found");
	iterator __iy{this->_M_data.find(__y)};
	assert(__iy != this->_M_data.end(),
		"runtime error: element __y not found");

	uintptr_t& __px{this->find_d(_S_itou(__ix))};
	uintptr_t& __py{this->find_d(_S_itou(__iy))};

	if (__px == __py)
		return false;

	if (this->rank_d(__px) < this->rank_d(__py))
		this->parent_d(__px) = __py;
	else
	{
		this->parent_d(__py) = __px;

		if (this->rank_d(__px) == this->rank_d(__py))
			++this->rank_d(__px);
	}

	return true;
}

template<typename _Tp, typename _Rank>
bool
tree_djset<_Tp, _Rank>::
is_sibling(const value_type& __x, const value_type& __y)
{ return this->find(__x) == this->find(__y); }

template<typename _Tp, typename _Rank>
_Tp
tree_djset<_Tp, _Rank>::
operator[] (const value_type& __x)
{ return this->find(__x); }

template<typename _Tp, typename _Rank>
void*
tree_djset<_Tp, _Rank>::
data()
{ return std::addressof(this->_M_data); }

}

#endif /* _POL_DJSET_TCC */
