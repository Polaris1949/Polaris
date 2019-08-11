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

/** @file        bits/djset.h
 *  @brief       Disjoint set data structure
 *  @author      Polaris Zhao
 *  @version     0.8.0
 *
 *  This is an internal header file, included by other library headers.
 *  Do not attempt to use it directly. @headername{djset}
**/

#ifndef _POL_DJSET_H
#define _POL_DJSET_H 1

#include <map>
#include <vector>
#include <type_traits>

namespace pol
{

// Store data in node.
// For sequence based djset, e.g. std::vector
template<typename _Tp>
class djset_data_node_base
{
public:
	using value_type = _Tp;
	using base_type = djset_data_node_base<_Tp>;

	value_type parent() const noexcept;
	value_type& parent_d() noexcept;

protected:
	_Tp _M_parent;
};

template<typename _Tp, typename _Rank>
class djset_data_node
	: public djset_data_node_base<_Tp>
{
public:
	using rank_type = _Rank;
	using node_type = djset_data_node<_Tp, _Rank>;

	rank_type rank() const noexcept;
	rank_type& rank_d() noexcept;

protected:
	_Rank _M_rank;
};

template<typename _Tp>
class djset_data_node<_Tp, void>
	: public djset_data_node_base<_Tp>
{
public:
	using rank_type = void;
	using node_type = djset_data_node<_Tp, void>;

	void rank() = delete;
	void rank_d() = delete;
};

// Store iterator (type erased) in node.
// For tree/hash based djset, e.g. std::map, std::unordered_map
template<typename _Tp>
class djset_iter_node_base
{
public:
	using value_type = _Tp;
	using base_type = djset_iter_node_base<_Tp>;

	uintptr_t parent() const noexcept;
	uintptr_t& parent_d() noexcept;

protected:
	// Assume that the iterator can be stored in an uintptr_t.
	// Using type erasure.
	uintptr_t _M_parent;
};

template<typename _Tp, typename _Rank>
class djset_iter_node
	: public djset_iter_node_base<_Tp>
{
public:
	using rank_type = _Rank;
	using node_type = djset_iter_node<_Tp, _Rank>;

	rank_type& rank_d() noexcept;
	rank_type rank() const noexcept;

protected:
	_Rank _M_rank;
};

template<typename _Tp>
class djset_iter_node<_Tp, void>
	: public djset_iter_node_base<_Tp>
{
public:
	using node_type = djset_iter_node<_Tp, void>;
};

template<typename _Tp, typename _Rank, typename _Iter>
class djset_auto_node
	: public std::conditional_t<(sizeof(_Tp) <= sizeof(_Iter)),
		djset_data_node<_Tp, _Rank>, djset_iter_node<_Tp, _Rank>>
{ };

template<typename _Tp, typename _Rank>
class seq_djset
{
public:
	static_assert(std::is_integral_v<_Tp>, "need an integral value type");

	using value_type = _Tp;
	using size_type = size_t;
	using rank_type = _Rank;
	using node_type = djset_data_node<_Tp, _Rank>;
	using container_type = std::vector<node_type>;

	seq_djset() = default;
	explicit seq_djset(size_type __n);

	~seq_djset() noexcept = default;

	void init(size_type __n);
	void clear() noexcept;
	size_type size() const noexcept;
	bool empty() const noexcept;

	value_type& parent(const value_type& __x);
	const value_type& parent(const value_type& __x) const;
	rank_type& rank(const value_type& __x);
	const rank_type& rank(const value_type& __x) const;

	value_type& find(const value_type& __x);
	bool merge(const value_type& __x, const value_type& __y);
	bool is_sibling(const value_type& __x, const value_type& __y);

	value_type& at(const value_type&);
	value_type& operator[] (const value_type& __x);

	container_type& data();
	const container_type& data() const;

private:
	container_type _M_data;
};

template<typename _Tp>
class seq_djset<_Tp, void>
{
public:
	static_assert(std::is_integral_v<_Tp>, "need an integral value type");

	using value_type = _Tp;
	using size_type = size_t;
	using rank_type = void;
	using node_type = djset_data_node<_Tp, void>;
	using container_type = std::vector<node_type>;

	seq_djset() = default;
	explicit seq_djset(size_type __n);

	~seq_djset() noexcept = default;

	void init(size_type __n);
	void clear() noexcept;
	size_type size() const noexcept;
	bool empty() const noexcept;

	value_type& parent(const value_type& __x);
	const value_type& parent(const value_type& __x) const;

	value_type& find(const value_type& __x);
	bool merge(const value_type& __x, const value_type& __y);
	bool is_sibling(const value_type& __x, const value_type& __y);

	value_type& at(const value_type&);
	value_type& operator[] (const value_type& __x);

	container_type& data();
	const container_type& data() const;

private:
	container_type _M_data;
};

template<typename _Tp, typename _Rank>
class tree_djset
{
public:
	using value_type = _Tp;
	using rank_type = _Rank;
	using size_type = size_t;
	using node_type = djset_iter_node<_Tp, _Rank>;
	using container_type = std::map<_Tp, node_type>;
	using iterator = container_type::iterator;

public:
	tree_djset() = default;
	~tree_djset() noexcept = default;

	bool insert(const value_type& __x);

	uintptr_t& parent_d(const uintptr_t& __x);
	value_type parent(const value_type& __x);

	rank_type& rank_d(const uintptr_t& __x);
	rank_type rank(const value_type& __x);

	uintptr_t& find_d(const uintptr_t& __x);
	value_type find(const value_type& __x);
	bool merge(const value_type& __x, const value_type& __y);
	bool is_sibling(const value_type& __x, const value_type& __y);

	value_type operator[] (const value_type& __x);

	void* data();

private:
	static uintptr_t _S_itou(iterator __i) noexcept;
	static iterator _S_utoi(uintptr_t __u) noexcept;

	std::map<_Tp, djset_iter_node<_Tp, _Rank>> _M_data;
};

}

#endif /* _POL_DJSET_H */
