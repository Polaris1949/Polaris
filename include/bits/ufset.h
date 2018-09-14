// Union find set classes -*- C++ -*-

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

/** @file        bits/ufset.h
 *  @headerfile  ufset
 *  @brief       Union find set classes
 *  @author      Polaris Zhao
 *  @version     3.0
 *
 *  This is an internal header file, included by other library headers.
 *  Do not attempt to use it directly.
**/

#ifndef _POL_UFSET_H
#define _POL_UFSET_H 1

#include <map>
#include <vector>

namespace polaris
{

template<typename _Tp>
class basic_ufset
{
public:
	using value_type = _Tp;
	using size_type = std::size_t;

private:
	std::map<_Tp, _Tp> _M_parent;
	std::map<_Tp, std::size_t> _M_rank;

public:
	basic_ufset();

	value_type& parent(const value_type& __x);
	size_type& rank(const value_type& __x);

	value_type& find(const value_type& __x);
	bool merge(const value_type& __x, const value_type& __y);
	bool is_brother(const value_type& __x, const value_type& __y);

	value_type& operator[] (const value_type& __x);
};

class seq_ufset
{
public:
	using value_type = std::size_t;
	using size_type = std::size_t;

private:
	std::vector<std::size_t> _M_parent;
	std::vector<std::size_t> _M_rank;

public:
	seq_ufset();
	explicit seq_ufset(size_type __n);

	void init(size_type __n);

	value_type& parent(const value_type& __x);
	const value_type& parent(const value_type& __x) const;
	size_type& rank(const value_type& __x);
	const value_type& rank(const value_type& __x) const;

	value_type& find(const value_type& __x);
	bool merge(const value_type& __x, const value_type& __y);
	bool is_brother(const value_type& __x, const value_type& __y);

	value_type& operator[] (const value_type& __x);
};

}

#endif /* _POL_UFSET_H */
