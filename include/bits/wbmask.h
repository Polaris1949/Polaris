// Weak bitmask -*- C++ -*-

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

/** @file bits/bmask.h
 *  This is an internal header file, included by other library headers.
 *  Do not attempt to use it directly. @headername{bitmask}
 */

// Written by Jingyu Zhao.

#ifndef _POL_WBMASK_H
#define _POL_WBMASK_H 1

namespace polaris
{

template<typename _Tp>
class weak_bitmask
{
public:
	typedef _Tp value_type;
	typedef _Tp mask_type;
	
private:
	_Tp _M_value;
	_Tp _M_mask;
	
public:
	weak_bitmask();
	explicit weak_bitmask(const value_type& __x);
	weak_bitmask(const value_type& __x, const mask_type& __y);
	
	value_type& value();
	mask_type& mask();
	
	value_type& apply();
	value_type calc() const;
};

}

#endif /* _POL_WBMASK_H */
