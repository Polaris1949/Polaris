// Sequence -*- C++ -*-

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

/** @file bits/seq.tcc
 *  This is an internal header file, included by other library headers.
 *  Do not attempt to use it directly. @headername{sequence}
 */

// Written by Polaris Zhao.

#ifndef _POL_SEQ_TCC
#define _POL_SEQ_TCC 1

namespace pol
{

template<typename _Tp, typename _Seq>
sequence<_Tp, _Seq>::
sequence()
	: _M_storage()
{ }

template<typename _Tp, typename _Seq>
size_t
sequence<_Tp, _Seq>::
size() const
{
	static_assert(__has_size<_Seq>);
	return _M_storage.size();
}

template<typename _Tp, typename _Seq>
void
sequence<_Tp, _Seq>::
push_front(const value_type& __x)
{
	static_assert(__has_push_front<_Seq, _Tp>);
	_M_storage.push_front(__x);
}

template<typename _Tp, typename _Seq>
void
sequence<_Tp, _Seq>::
push_back(const value_type& __x)
{
	static_assert(__has_push_back<_Seq, _Tp>);
	_M_storage.push_back(__x);
}

template<typename _Tp, typename _Seq>
_Tp&
sequence<_Tp, _Seq>::
front()
{
	static_assert(__has_front<_Seq, _Tp>);
	return _M_storage.front();
}

template<typename _Tp, typename _Seq>
const _Tp&
sequence<_Tp, _Seq>::
front() const
{
	static_assert(__has_front<_Seq, _Tp>);
	return _M_storage.front();
}

template<typename _Tp, typename _Seq>
_Tp&
sequence<_Tp, _Seq>::
back()
{
	static_assert(__has_back<_Seq, _Tp>);
	return _M_storage.back();
}

template<typename _Tp, typename _Seq>
const _Tp&
sequence<_Tp, _Seq>::
back() const
{
	static_assert(__has_back<_Seq, _Tp>);
	return _M_storage.back();
}

template<typename _Tp, typename _Seq>
void
sequence<_Tp, _Seq>::
resize(size_type __new_size)
{
	static_assert(__has_resize<_Seq, _Tp>);
	_M_storage.resize(__new_size);
}

template<typename _Tp, typename _Seq>
_Tp&
sequence<_Tp, _Seq>::
operator[] (size_type __pos)
{
	static_assert(__has_ops<_Seq, _Tp>);
	return _M_storage[__pos];
}

template<typename _Tp, typename _Seq>
const _Tp&
sequence<_Tp, _Seq>::
operator[] (size_type __pos) const
{
	static_assert(__has_ops<_Seq, _Tp>);
	return _M_storage[__pos];
}

}

#endif /* _POL_SEQ_TCC */
