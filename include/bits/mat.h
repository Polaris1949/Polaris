// Matrix -*- C++ -*-

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

/** @file bits/mat.h
 *  This is an internal header file, included by other library headers.
 *  Do not attempt to use it directly. @headername{matrix}
 */

// Written by Jingyu Zhao.

#ifndef _POL_MAT_H
#define _POL_MAT_H 1

// TODO...

namespace polaris
{

template<typename _Tp, typename _Mat = std::deque<std::deque<_Tp>>>
class matrix
{
	typedef typename _Mat::value_type _Seq;
	
public:
	typedef _Tp value_type;
	typedef _Seq sequence_type;
	typedef _Mat container_type;
	typedef size_t size_type;
	
private:
	_Mat _M_storage;
	
public:
	matrix();
	matrix(const container_type& __c);
	
	std::enable_if_t<has_resize<container_type, sequence_type>>
	resize(size_type __new_size);
	
	std::enable_if_t<has_ops<container_type, sequence_type>, \
		sequence_type&>
	operator[] (size_type __pos);
	
	std::enable_if_t<has_ops<container_type, sequence_type>, \
		const sequence_type&>
	operator[] (size_type __pos) const;
};

}

#endif /* _POL_MAT_H */
