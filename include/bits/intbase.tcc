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

/** @file bits/intbase.tcc
 *  This is an internal header file, included by other library headers.
 *  Do not attempt to use it directly. @headername{integer}
 */

// Written by Jingyu Zhao.

#ifndef _POL_INTBASE_TCC
#define _POL_INTBASE_TCC 1

namespace polaris
{

inline
_Int_base::_Int_impl::
_Int_impl()
	: _M_start(), _M_finish(), _M_end_of_storage()
{
}

inline void
_Int_base::_Int_impl::
_M_swap_data(_Int_impl& __x) noexcept
{
	std::swap(_M_start, __x._M_start);
	std::swap(_M_finish, __x._M_finish);
	std::swap(_M_end_of_storage, __x._M_end_of_storage);
}

inline _Int_allocator&
_Int_base::
_M_get_allocator() noexcept
{
	return *static_cast<_Int_allocator*>(&this->_M_impl);
}

inline const _Int_allocator&
_Int_base::
_M_get_allocator() const noexcept
{
	return *static_cast<const _Int_allocator*>(&this->_M_impl);
}

inline _Int_allocator
_Int_base::
get_allocator() const noexcept
{
	return _Int_allocator(_M_get_allocator());
}

_Int_base::
_Int_base()
	: _M_impl()
{
}

_Int_base::
_Int_base(size_t __n)
	: _M_impl()
{
	this->_M_create_storage(__n);
}

_Int_base::
_Int_base(const _Int_base& __x)
	: _M_impl{}
{
	std::cerr << "copy ctor\n";
	this->_M_create_storage(__x._M_impl._M_end_of_storage - __x._M_impl._M_start);
	std::uninitialized_copy(__x._M_impl._M_start, __x._M_impl._M_end_of_storage, this->_M_impl._M_start);
}

_Int_base::
_Int_base(_Int_base&& __x)
	: _M_impl{}
{
	this->_M_impl._M_swap_data(__x._M_impl);
}

inline
_Int_base::
~_Int_base() noexcept
{
	this->_M_deallocate(this->_M_impl._M_start, \
		this->_M_impl._M_end_of_storage - this->_M_impl._M_start);
}

inline _Int_pointer
_Int_base::
_M_allocate(size_t __n)
{
	// TODO... _Int_allocator?
	return __n != 0 ? _Int_pointer(_M_impl.allocate(__n)) : nullptr;
}

inline void
_Int_base::
_M_deallocate(_Int_pointer __p, size_t __n)
{
	// TODO... _Int_allocator?
	if (__p)
		_M_impl.deallocate(__p);
}

inline _Int_pointer
_Int_base::
_M_reallocate(_Int_pointer __p, size_t __n)
{
	// TODO... _Int_allocator?
	return __n != 0 ? __p ? _Int_pointer(_M_impl.reallocate(__p, __n))
		: _Int_pointer(_M_impl.allocate(__n)) : nullptr;
}

inline void
_Int_base::
_M_create_storage(size_t __n)
{
	this->_M_impl._M_start = this->_M_allocate(__n);
	this->_M_impl._M_finish = this->_M_impl._M_start;
	this->_M_impl._M_end_of_storage = this->_M_impl._M_start + __n;
}

}

#endif /* _POL_INTBASE_TCC */
