// Integer base -*- C++ -*-

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

/** @file bits/intbase.h
 *  This is an internal header file, included by other library headers.
 *  Do not attempt to use it directly. @headername{integer}
 */

// Written by Jingyu Zhao.

#ifndef _POL_INTBASE_H
#define _POL_INTBASE_H 1

// #include <vector>

namespace polaris
{

struct _Int_base
{
	// typedef _Int_data data_type;
	// typedef _Int_radix radix_type;
	// typedef size_t size_type;
	
	struct _Int_impl
		: public _Int_allocator
	{
		_Int_pointer _M_start;
		_Int_pointer _M_finish;
		_Int_pointer _M_end_of_storage;
		
		_Int_impl();
		
		void _M_swap_data(_Int_impl& __x) noexcept;
	};
	
public:
	_Int_allocator& _M_get_allocator() noexcept;
	const _Int_allocator& _M_get_allocator() const noexcept;
	_Int_allocator get_allocator() const noexcept;
	
	_Int_base();
	_Int_base(size_t __n);
	~_Int_base() noexcept;
	
public:
	_Int_impl _M_impl;
	
	_Int_pointer _M_allocate(size_t __n);
	void _M_deallocate(_Int_pointer __p, size_t __n);
	_Int_pointer _M_reallocate(_Int_pointer __p, size_t __n);
	
private:
	void _M_create_storage(size_t __n);
};

}

#endif /* _POL_INTBASE_H */
