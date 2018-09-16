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

/** @file bits/seq.h
 *  This is an internal header file, included by other library headers.
 *  Do not attempt to use it directly. @headername{sequence}
 */

// Written by Jingyu Zhao.

#ifndef _POL_SEQ_H
#define _POL_SEQ_H 1

#include <deque>
#include <polaris/type_traits>

namespace polaris
{

// TODO: Move to <concepts>?
inline namespace __detail
{

template<typename _C>
using __c_value_type = typename _C::value_type;

template<typename _C>
using __c_reference = typename _C::reference;

template<typename _C>
using __c_const_reference = typename _C::const_reference;

template<typename _C>
using __c_iterator = typename _C::iterator;

template<typename _C>
using __c_const_iterator = typename _C::const_iterator;

template<typename _C>
using __c_difference_type = typename _C::difference_type;

template<typename _C>
using __c_size_type = typename _C::size_type;

template<typename _C>
using __c_reverse_iterator = typename _C::reverse_iterator;

template<typename _C>
using __c_const_reverse_iterator = typename _C::const_reverse_iterator;

template<typename _C>
using __c_allocator_type = typename _C::allocator_type;

template<typename _C>
concept bool __has_begin = requires(_C& __c)
{
	{__c.begin()}->__c_iterator<_C>;
} && requires(const _C& __c)
{
	{__c.begin()}->__c_const_iterator<_C>;
};

template<typename _C>
concept bool __has_end = requires(_C& __c)
{
	{__c.end()}->__c_iterator<_C>;
} && requires(const _C& __c)
{
	{__c.end()}->__c_const_iterator<_C>;
};

template<typename _C>
concept bool __has_cbegin = requires(_C& __c)
{
	{__c.cbegin()}->__c_const_iterator<_C>;
};

template<typename _C>
concept bool __has_cend = requires(_C& __c)
{
	{__c.cend()}->__c_const_iterator<_C>;
};

template<typename _C>
concept bool __has_swap = requires(_C& __cx, _C& __cy)
{
	{__cx.swap(__cy)}->void;
};

template<typename _C>
concept bool __has_size = requires(_C& __c)
{
	{__c.size()}->__c_size_type<_C>;
};

template<typename _C>
concept bool __has_max_size = requires(_C& __c)
{
	{__c.max_size()}->__c_size_type<_C>;
};

template<typename _C>
concept bool __has_empty = requires(_C& __c)
{
	{__c.empty()}->bool;
};

template<typename _C>
concept bool __has_rbegin = requires(_C& __c)
{
	{__c.rbegin()}->__c_reverse_iterator<_C>;
} && requires(const _C& __c)
{
	{__c.rbegin()}->__c_const_reverse_iterator<_C>;
};

template<typename _C>
concept bool __has_rend = requires(_C& __c)
{
	{__c.rend()}->__c_reverse_iterator<_C>;
} && requires(const _C& __c)
{
	{__c.rend()}->__c_const_reverse_iterator<_C>;
};

template<typename _C>
concept bool __has_crbegin = requires(_C& __c)
{
	{__c.crbegin()}->__c_const_reverse_iterator<_C>;
};

template<typename _C>
concept bool __has_crend = requires(_C& __c)
{
	{__c.crend()}->__c_const_reverse_iterator<_C>;
};

template<typename _C>
concept bool __has_get_allocator = requires(_C& __c)
{
	{__c.get_allocator()}->__c_allocator_type<_C>;
};

template<typename _C, typename... _Args>
concept bool __has_emplace = requires(_C& __c, __c_const_iterator<_C>& __p, \
	_Args&&... __args)
{
	{__c.emplace(__p, __args...)}->__c_iterator<_C>;
};

template<typename _C, typename _Tp, typename... _Args>
concept bool has_emplace = __has_emplace<_C, _Args...>\
	&& std::is_convertible<_Tp, __c_value_type<_C>>::value;

template<typename _Seq, typename _Tp>
concept bool __has_push_front = requires(_Seq __c, const _Tp& __x)
{
	{__c.push_front(__x)}->void;
} || requires(_Seq __c, _Tp&& __x)
{
	{__c.push_front(__x)}->void;
};

template<typename _Seq>
concept bool has_push_front = __has_push_front<_Seq, __c_value_type<_Seq>>;

template<typename _Seq, typename _Tp>
concept bool has_push_front_c = __has_push_front<_Seq, _Tp> \
	&& std::is_convertible<_Tp, __c_value_type<_Seq>>::value;

template<typename _Seq, typename _Tp>
concept bool __has_push_back = requires(_Seq __c, const _Tp& __x)
{
	{__c.push_back(__x)}->void;
} || requires(_Seq __c, _Tp&& __x)
{
	{__c.push_back(__x)}->void;
};

template<typename _Seq>
concept bool has_push_back = __has_push_back<_Seq, __c_value_type<_Seq>>;

template<typename _Seq, typename _Tp = typename _Seq::value_type>
concept bool __has_front = requires(_Seq __c)
{
	{__c.front()}->_Tp&;
} || requires(const _Seq __c)
{
	{__c.front()}->const _Tp&;
};

template<typename _Seq, typename _Tp = typename _Seq::value_type>
concept bool __has_back = requires(_Seq __c)
{
	{__c.back()}->_Tp&;
} || requires(_Seq __c)
{
	{__c.back()}->const _Tp&;
};

template<typename _Seq, typename _Tp = typename _Seq::value_type, \
	typename... _Args>
concept bool __has_emplace_front = requires(_Seq __c, _Args&&... __args)
{
	{__c.emplace_front(__args...)}->_Tp&;
};

template<typename _Seq, typename _Tp = typename _Seq::value_type, \
	typename... _Args>
concept bool __has_emplace_back = requires(_Seq __c, _Args&&... __args)
{
	{__c.emplace_back(__args...)}->_Tp&;
};

template<typename _Seq, typename _Tp = typename _Seq::value_type>
concept bool __has_resize = requires(_Seq __c, size_t __size)
{
	{__c.resize(__size)}->void;
} && (requires(_Seq __c, size_t __size, const _Tp& __x)
{
	{__c.resize(__size, __x)}->void;
} || requires(_Seq __c, size_t __size, _Tp&& __x)
{
	{__c.resize(__size, __x)}->void;
});

template<typename _Seq, typename _Tp = typename _Seq::value_type>
concept bool __has_ops = requires(_Seq __c, size_t __pos)
{
	{__c[__pos]}->_Tp&;
} || requires(_Seq __c, size_t __pos)
{
	{__c[__pos]}->const _Tp&;
};

template<typename _C, typename _Tp>
concept bool __has_insert = requires(_C& __c, __c_const_iterator<_C>& __p, \
	const _Tp& __x)
{
	{__c.insert(__p, __x)}->__c_iterator<_C>;
};

template<typename _C, typename _Tp>
concept bool __has_erase = requires(_C& __c, __c_const_iterator<_C>& __p)
{
	{__c.erase(__p)}->__c_iterator<_C>;
};

/*
template<typename _C, typename _Tp>
concept bool __has_[TODO...] = requires([TODO...])
{
	{__c.[TODO...]()}->__c_[TODO...]<_C>;
};
*/

#if _POL_NEWLIB
// TODO: Concepts macros and macro struct-helpers
// TODO: And add them into library components
#if _POL_ENABLE_CONCEPT
template<bool _Con, typename _Tp>
using concept_if_t = std::enable_if_t<_Con, _Tp>;
#define POL_ENABLE_CONCEPT_IF_T(_Con, _Tp) concept_if_t<_Con, _Tp>
#else
template<bool, typename>
struct concept_if_t {};
#define POL_ENABLE_CONCEPT_IF_T(_Con, _Tp) _Tp
#endif
#endif

}

template<typename _Tp, typename _Seq = std::deque<_Tp>>
class sequence
{
public:
	typedef _Tp value_type;
	typedef _Seq container_type;
	typedef size_t size_type;
	typedef _Tp& reference;
	typedef const _Tp& const_reference;

private:
	_Seq _M_storage;

public:
	sequence();
	sequence(const container_type& __c);

//	POL_ENABLE_CONCEPT_IF_T((__has_size<_Seq, _Tp>), size_t)
//	std::enable_if_t<__has_size<container_type>>
	size_type
	size() const;

//	POL_ENABLE_CONCEPT_IF_T(__has_push_front<_Seq, _Tp>, void)
//	std::enable_if_t<__has_push_front<container_type, value_type>>
	void
	push_front(const value_type& __x);

//	POL_ENABLE_CONCEPT_IF_T(__has_push_back<_Seq, _Tp>, void)
//	std::enable_if_t<__has_push_back<container_type, value_type>>
	void
	push_back(const value_type& __x);

	reference
	front();

//	POL_ENABLE_CONCEPT_IF_T(__has_front<_Seq, _Tp>, const _Tp&)
//	std::enable_if_t<__has_front<container_type, value_type>, \
		const value_type&>
	const_reference
	front() const;

	reference
	back();

//	POL_ENABLE_CONCEPT_IF_T(__has_back<_Seq, _Tp>, const _Tp&)
//	std::enable_if_t<__has_back<container_type, value_type>, \
		const value_type&>
	const_reference
	back() const;

//	POL_ENABLE_CONCEPT_IF_T(__has_resize<_Seq, _Tp>, void)
//	std::enable_if_t<__has_resize<container_type, value_type>>
	void
	resize(size_type __new_size);

//	POL_ENABLE_CONCEPT_IF_T(__has_ops<_Seq, _Tp>, _Tp&)
//	std::enable_if_t<__has_ops<container_type, value_type>, value_type&>
	reference
	operator[] (size_type __pos);

//	POL_ENABLE_CONCEPT_IF_T(__has_ops<_Seq, _Tp>, const _Tp&)
//	std::enable_if_t<__has_ops<container_type, value_type>, const value_type&>
	const_reference
	operator[] (size_type __pos) const;
};

}

#endif /* _POL_SEQ_H */
