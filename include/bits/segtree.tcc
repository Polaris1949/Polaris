// Segment tree -*- C++ -*-

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

/** @file bits/segtree.tcc
 *  This is an internal header file, included by other library headers.
 *  Do not attempt to use it directly. @headername{segment_tree}
 */

// Written by Jingyu Zhao.

#ifndef _POL_SEGTREE_TCC
#define _POL_SEGTREE_TCC 1

#pragma GCC system_header

namespace polaris
{

// @segment_tree_node
//@{
template<typename _Tp, typename _MarkT>
inline
segment_tree_node<_Tp, _MarkT>::
segment_tree_node()
	: _M_begin(), _M_end(), _M_left(), _M_right(), _M_data(), _M_mark()
{
}

template<typename _Tp, typename _MarkT>
inline
segment_tree_node<_Tp, _MarkT>::
segment_tree_node(size_type __begin, size_type __end)
	: _M_begin(__begin), _M_end(__end), _M_left(), _M_right(), _M_data(),
		_M_mark()
{
}

template<typename _Tp, typename _MarkT>
inline
segment_tree_node<_Tp, _MarkT>::
~segment_tree_node() noexcept
{
	delete _M_left;
	delete _M_right;
}

template<typename _Tp, typename _MarkT>
inline segment_tree_node<_Tp, _MarkT>&
segment_tree_node<_Tp, _MarkT>::
construct(size_type __begin, size_type __end)
{
	_M_destroy();
	_M_data = value_type();
	_M_mark = mark_type();
	_M_construct(__begin, __end);
	return *this;
}

template<typename _Tp, typename _MarkT>
inline segment_tree_node<_Tp, _MarkT>&
segment_tree_node<_Tp, _MarkT>::
destroy()
{
	_M_destroy();
	_M_left = 0;
	_M_right = 0;
	_M_begin = size_type();
	_M_end = size_type();
	_M_data = value_type();
	_M_mark = mark_type();
	return *this;
}

template<typename _Tp, typename _MarkT>
inline segment_tree_node<_Tp, _MarkT>*&
segment_tree_node<_Tp, _MarkT>::
left()
{
	return _M_left;
}

template<typename _Tp, typename _MarkT>
inline const segment_tree_node<_Tp, _MarkT>*&
segment_tree_node<_Tp, _MarkT>::
left() const
{
	return _M_left;
}

template<typename _Tp, typename _MarkT>
inline segment_tree_node<_Tp, _MarkT>*&
segment_tree_node<_Tp, _MarkT>::
right()
{
	return _M_right;
}

template<typename _Tp, typename _MarkT>
inline const segment_tree_node<_Tp, _MarkT>*&
segment_tree_node<_Tp, _MarkT>::
right() const
{
	return _M_right;
}

template<typename _Tp, typename _MarkT>
inline _Tp&
segment_tree_node<_Tp, _MarkT>::
data()
{
	return _M_data;
}

template<typename _Tp, typename _MarkT>
inline const _Tp&
segment_tree_node<_Tp, _MarkT>::
data() const
{
	return _M_data;
}

template<typename _Tp, typename _MarkT>
inline _MarkT&
segment_tree_node<_Tp, _MarkT>::
mark()
{
	return _M_mark;
}

template<typename _Tp, typename _MarkT>
inline const _MarkT&
segment_tree_node<_Tp, _MarkT>::
mark() const
{
	return _M_mark;
}

template<typename _Tp, typename _MarkT>
inline std::size_t
segment_tree_node<_Tp, _MarkT>::
begin() const
{
	return _M_begin;
}

template<typename _Tp, typename _MarkT>
inline std::size_t
segment_tree_node<_Tp, _MarkT>::
end() const
{
	return _M_end;
}

template<typename _Tp, typename _MarkT>
inline std::size_t
segment_tree_node<_Tp, _MarkT>::
middle() const
{
	return (_M_begin + _M_end) >> size_type(1);
}

template<typename _Tp, typename _MarkT>
inline std::size_t
segment_tree_node<_Tp, _MarkT>::
segment() const
{
	return _M_end - _M_begin;
}

template<typename _Tp, typename _MarkT>
inline bool
segment_tree_node<_Tp, _MarkT>::
is_leaf() const
{
	return _M_begin + size_type(1) == _M_end;
}

template<typename _Tp, typename _MarkT>
inline void
segment_tree_node<_Tp, _MarkT>::
_M_construct(size_type __begin, size_type __end)
{
	_M_begin = __begin;
	_M_end = __end;
}

template<typename _Tp, typename _MarkT>
inline void
segment_tree_node<_Tp, _MarkT>::
_M_destroy()
{
	delete _M_left;
	delete _M_right;
}

//@}

// @segment_tree_node<_Tp, void>
//@{
template<typename _Tp>
inline
segment_tree_node<_Tp, void>::
segment_tree_node()
	: _M_begin(), _M_end(), _M_left(), _M_right(), _M_data()
{
}

template<typename _Tp>
inline
segment_tree_node<_Tp, void>::
segment_tree_node(size_type __begin, size_type __end)
	: _M_begin(__begin), _M_end(__end), _M_left(), _M_right(), _M_data()
{
}

template<typename _Tp>
inline
segment_tree_node<_Tp, void>::
~segment_tree_node() noexcept
{
	delete _M_left;
	delete _M_right;
}

template<typename _Tp>
inline segment_tree_node<_Tp, void>&
segment_tree_node<_Tp, void>::
construct(size_type __begin, size_type __end)
{
	_M_destroy();
	_M_data = value_type();
	_M_construct(__begin, __end);
	return *this;
}

template<typename _Tp>
inline segment_tree_node<_Tp, void>&
segment_tree_node<_Tp, void>::
destroy()
{
	_M_destroy();
	_M_left = 0;
	_M_right = 0;
	_M_begin = size_type();
	_M_end = size_type();
	_M_data = value_type();
	return *this;
}

template<typename _Tp>
inline segment_tree_node<_Tp, void>*&
segment_tree_node<_Tp, void>::
left()
{
	return _M_left;
}

template<typename _Tp>
inline const segment_tree_node<_Tp, void>*&
segment_tree_node<_Tp, void>::
left() const
{
	return _M_left;
}

template<typename _Tp>
inline segment_tree_node<_Tp, void>*&
segment_tree_node<_Tp, void>::
right()
{
	return _M_right;
}

template<typename _Tp>
inline const segment_tree_node<_Tp, void>*&
segment_tree_node<_Tp, void>::
right() const
{
	return _M_right;
}

template<typename _Tp>
inline _Tp&
segment_tree_node<_Tp, void>::
data()
{
	return _M_data;
}

template<typename _Tp>
inline const _Tp&
segment_tree_node<_Tp, void>::
data() const
{
	return _M_data;
}

template<typename _Tp>
inline std::size_t
segment_tree_node<_Tp, void>::
begin() const
{
	return _M_begin;
}

template<typename _Tp>
inline std::size_t
segment_tree_node<_Tp, void>::
end() const
{
	return _M_end;
}

template<typename _Tp>
inline std::size_t
segment_tree_node<_Tp, void>::
middle() const
{
	return (_M_begin + _M_end) >> size_type(1);
}

template<typename _Tp>
inline std::size_t
segment_tree_node<_Tp, void>::
segment() const
{
	return _M_end - _M_begin;
}

template<typename _Tp>
inline bool
segment_tree_node<_Tp, void>::
is_leaf() const
{
	return _M_begin + size_type(1) == _M_end;
}

template<typename _Tp>
inline void
segment_tree_node<_Tp, void>::
_M_construct(size_type __begin, size_type __end)
{
	_M_begin = __begin;
	_M_end = __end;
}

template<typename _Tp>
inline void
segment_tree_node<_Tp, void>::
_M_destroy()
{
	delete _M_left;
	delete _M_right;
}

//@}

// @segment_tree
//@{

template<typename _Tp, typename _MarkT, typename _Func>
inline
segment_tree<_Tp, _MarkT, _Func>::
segment_tree()
	: _M_root(), _M_inf(), _M_func()
{
}

template<typename _Tp, typename _MarkT, typename _Func>
template<typename _Sequence>
inline
segment_tree<_Tp, _MarkT, _Func>::
segment_tree(size_type __begin, size_type __end, const _Sequence& __data)
	: _M_root(new segment_tree_node<_Tp, _MarkT>(__begin, __end)),
		_M_inf(), _M_func()
{
	_M_construct(_M_root, __data);
}

template<typename _Tp, typename _MarkT, typename _Func>
inline
segment_tree<_Tp, _MarkT, _Func>::
~segment_tree() noexcept
{
	delete _M_root;
}

template<typename _Tp, typename _MarkT, typename _Func>
template<typename _Sequence>
inline segment_tree<_Tp, _MarkT, _Func>&
segment_tree<_Tp, _MarkT, _Func>::
construct(size_type __begin, size_type __end, const _Sequence& __data)
{
	_M_destroy();
	_M_root = new segment_tree_node<_Tp, _MarkT>(__begin, __end);
	_M_construct(_M_root, __data);
	return *this;
}

template<typename _Tp, typename _MarkT, typename _Func>
inline segment_tree<_Tp, _MarkT, _Func>&
segment_tree<_Tp, _MarkT, _Func>::
destroy()
{
	_M_destroy();
	_M_root = 0;
	return *this;
}

template<typename _Tp, typename _MarkT, typename _Func>
inline segment_tree_node<_Tp, _MarkT>*&
segment_tree<_Tp, _MarkT, _Func>::
root()
{
	return _M_root;
}

template<typename _Tp, typename _MarkT, typename _Func>
inline const segment_tree_node<_Tp, _MarkT>*&
segment_tree<_Tp, _MarkT, _Func>::
root() const
{
	return _M_root;
}

template<typename _Tp, typename _MarkT, typename _Func>
inline _Tp&
segment_tree<_Tp, _MarkT, _Func>::
infinite()
{
	return _M_inf;
}

template<typename _Tp, typename _MarkT, typename _Func>
inline const _Tp&
segment_tree<_Tp, _MarkT, _Func>::
infinite() const
{
	return _M_inf;
}

template<typename _Tp, typename _MarkT, typename _Func>
inline const _Func&
segment_tree<_Tp, _MarkT, _Func>::
data_functor() const
{
	return _M_func;
}

template<typename _Tp, typename _MarkT, typename _Func>
inline std::size_t
segment_tree<_Tp, _MarkT, _Func>::
begin() const
{
	return _M_root->begin();
}

template<typename _Tp, typename _MarkT, typename _Func>
inline std::size_t
segment_tree<_Tp, _MarkT, _Func>::
end() const
{
	return _M_root->end();
}

template<typename _Tp, typename _MarkT, typename _Func>
inline segment_tree<_Tp, _MarkT, _Func>&
segment_tree<_Tp, _MarkT, _Func>::
push_up(node_type* __pos)
{
	if (__pos)
	{
		__pos->data() = _M_func(__pos->left()->data(), \
			__pos->right()->data());
	}
	
	return *this;
}

template<typename _Tp, typename _MarkT, typename _Func>
template<typename _MarkFunc>
inline segment_tree<_Tp, _MarkT, _Func>&
segment_tree<_Tp, _MarkT, _Func>::
push_down(node_type* __pos, const _MarkFunc& __mark)
{
	if (__pos)
	{
		using namespace std::rel_ops;
		
		if (__pos->mark() != mark_type())
		{
			__mark(__pos->left(), __pos->mark());
			__mark(__pos->right(), __pos->mark());
			__pos->mark() = mark_type();
		}
	}
	
	return *this;
}

template<typename _Tp, typename _MarkT, typename _Func>
template<typename _MarkFunc>
inline _Tp
segment_tree<_Tp, _MarkT, _Func>::
search(size_type __begin, size_type __end, const _MarkFunc& __mark)
{
	return (_M_root ? _M_search(_M_root, __begin, __end, __mark) : _M_inf);
}

template<typename _Tp, typename _MarkT, typename _Func>
template<typename _ModifyFunc, typename _MarkFunc>
inline segment_tree<_Tp, _MarkT, _Func>&
segment_tree<_Tp, _MarkT, _Func>::
modify(size_type __pos, const value_type& __x, const _ModifyFunc& __func,
	const _MarkFunc& __mark)
{
	if (_M_root)
		_M_modify(_M_root, __pos, __x, __func, __mark);
	
	return *this;
}

template<typename _Tp, typename _MarkT, typename _Func>
template<typename _ModifyFunc, typename _MarkFunc>
inline segment_tree<_Tp, _MarkT, _Func>&
segment_tree<_Tp, _MarkT, _Func>::
modify(size_type __begin, size_type __end, const value_type& __x,
	const _ModifyFunc& __func, const _MarkFunc& __mark)
{
	if (_M_root)
		_M_modify(_M_root, __begin, __end, __x, __func, __mark);
	
	return *this;
}

template<typename _Tp, typename _MarkT, typename _Func>
template<typename _Sequence>
void
segment_tree<_Tp, _MarkT, _Func>::
_M_construct(node_type* __root, const _Sequence& __data)
{
	if (__root->is_leaf())
		__root->data() = __data[__root->begin()];
	else
	{
		__root->left() = new node_type(__root->begin(), __root->middle());
		__root->right() = new node_type(__root->middle(), __root->end());
		
		_M_construct(__root->left(), __data);
		_M_construct(__root->right(), __data);
		
		push_up(__root);
	}
}

template<typename _Tp, typename _MarkT, typename _Func>
inline void
segment_tree<_Tp, _MarkT, _Func>::
_M_destroy()
{
	delete _M_root;
}

template<typename _Tp, typename _MarkT, typename _Func>
template<typename _MarkFunc>
_Tp
segment_tree<_Tp, _MarkT, _Func>::
_M_search(node_type* __root, size_type __begin, size_type __end,
	const _MarkFunc& __mark)
{
	if (__begin >= __root->end() || __end <= __root->begin())
		return _M_inf;
	
	if (__begin <= __root->begin() && __end >= __root->end())
		return __root->data();
	
	push_down(__root, __mark);
	
	return _M_func(_M_search(__root->left(), __begin, __end, __mark),
		_M_search(__root->right(), __begin, __end, __mark));
}

template<typename _Tp, typename _MarkT, typename _Func>
template<typename _ModifyFunc, typename _MarkFunc>
void
segment_tree<_Tp, _MarkT, _Func>::
_M_modify(node_type* __root, size_type __pos, const _Tp& __x,
	const _ModifyFunc& __func, const _MarkFunc& __mark)
{
	if (__root->is_leaf())
	{
		if (__pos == __root->begin())
			__func(__root, __x);
		
		return;
	}
	
	push_down(__root, __mark);
	
	if (__pos < __root->middle())
		_M_modify(__root->left(), __pos, __x, __func, __mark);
	else
		_M_modify(__root->right(), __pos, __x, __func, __mark);
	
	push_up(__root);
}

template<typename _Tp, typename _MarkT, typename _Func>
template<typename _ModifyFunc, typename _MarkFunc>
void
segment_tree<_Tp, _MarkT, _Func>::
_M_modify(node_type* __root, size_type __begin, size_type __end,
	const value_type& __x, const _ModifyFunc& __func,
	const _MarkFunc& __mark)
{
	if (__begin >= __root->end() || __end <= __root->begin())
		return;
	
	if (__begin <= __root->begin() && __end >= __root->end())
	{
		__func(__root, __x);
		return;
	}
	
	push_down(__root, __mark);
	
	_M_modify(__root->left(), __begin, __end, __x, __func, __mark);
	_M_modify(__root->right(), __begin, __end, __x, __func, __mark);
	
	push_up(__root);
}

//@}

// @segment_tree<_Tp, void, _Func>
//@{

template<typename _Tp, typename _Func>
inline
segment_tree<_Tp, void, _Func>::
segment_tree()
	: _M_root(), _M_inf(), _M_func()
{
}

template<typename _Tp, typename _Func>
template<typename _Sequence>
inline
segment_tree<_Tp, void, _Func>::
segment_tree(size_type __begin, size_type __end, const _Sequence& __data)
	: _M_root(new segment_tree_node<_Tp, void>(__begin, __end)),
		_M_inf(), _M_func()
{
	_M_construct(_M_root, __data);
}

template<typename _Tp, typename _Func>
inline
segment_tree<_Tp, void, _Func>::
~segment_tree() noexcept
{
	delete _M_root;
}

template<typename _Tp, typename _Func>
template<typename _Sequence>
inline segment_tree<_Tp, void, _Func>&
segment_tree<_Tp, void, _Func>::
construct(size_type __begin, size_type __end, const _Sequence& __data)
{
	_M_destroy();
	_M_root = new segment_tree_node<_Tp, void>(__begin, __end);
	_M_construct(_M_root, __data);
	return *this;
}

template<typename _Tp, typename _Func>
inline segment_tree<_Tp, void, _Func>&
segment_tree<_Tp, void, _Func>::
destroy()
{
	_M_destroy();
	_M_root = 0;
	return *this;
}

template<typename _Tp, typename _Func>
inline segment_tree_node<_Tp, void>*&
segment_tree<_Tp, void, _Func>::
root()
{
	return _M_root;
}

template<typename _Tp, typename _Func>
inline const segment_tree_node<_Tp, void>*&
segment_tree<_Tp, void, _Func>::
root() const
{
	return _M_root;
}

template<typename _Tp, typename _Func>
inline _Tp&
segment_tree<_Tp, void, _Func>::
infinite()
{
	return _M_inf;
}

template<typename _Tp, typename _Func>
inline const _Tp&
segment_tree<_Tp, void, _Func>::
infinite() const
{
	return _M_inf;
}

template<typename _Tp, typename _Func>
inline const _Func&
segment_tree<_Tp, void, _Func>::
data_functor() const
{
	return _M_func;
}

template<typename _Tp, typename _Func>
inline std::size_t
segment_tree<_Tp, void, _Func>::
begin() const
{
	return _M_root->begin();
}

template<typename _Tp, typename _Func>
inline std::size_t
segment_tree<_Tp, void, _Func>::
end() const
{
	return _M_root->end();
}

template<typename _Tp, typename _Func>
inline segment_tree<_Tp, void, _Func>&
segment_tree<_Tp, void, _Func>::
push_up(node_type* __pos)
{
	if (__pos)
	{
		__pos->data() = _M_func(__pos->left()->data(), \
			__pos->right()->data());
	}
	
	return *this;
}

template<typename _Tp, typename _Func>
inline _Tp
segment_tree<_Tp, void, _Func>::
search(size_type __begin, size_type __end)
{
	return (_M_root ? _M_search(_M_root, __begin, __end) : _M_inf);
}

template<typename _Tp, typename _Func>
template<typename _ModifyFunc>
inline segment_tree<_Tp, void, _Func>&
segment_tree<_Tp, void, _Func>::
modify(size_type __pos, const value_type& __x, const _ModifyFunc& __func)
{
	if (_M_root)
		_M_modify(_M_root, __pos, __x, __func);
	
	return *this;
}

template<typename _Tp, typename _Func>
template<typename _ModifyFunc>
inline segment_tree<_Tp, void, _Func>&
segment_tree<_Tp, void, _Func>::
modify(size_type __begin, size_type __end, const value_type& __x,
	const _ModifyFunc& __func)
{
	if (_M_root)
		_M_modify(_M_root, __begin, __end, __x, __func);
	
	return *this;
}

template<typename _Tp, typename _Func>
template<typename _Sequence>
void
segment_tree<_Tp, void, _Func>::
_M_construct(node_type* __root, const _Sequence& __data)
{
	if (__root->is_leaf())
		__root->data() = __data[__root->begin()];
	else
	{
		__root->left() = new node_type(__root->begin(), __root->middle());
		__root->right() = new node_type(__root->middle(), __root->end());
		
		_M_construct(__root->left(), __data);
		_M_construct(__root->right(), __data);
		
		push_up(__root);
	}
}

template<typename _Tp, typename _Func>
inline void
segment_tree<_Tp, void, _Func>::
_M_destroy()
{
	delete _M_root;
}

template<typename _Tp, typename _Func>
_Tp
segment_tree<_Tp, void, _Func>::
_M_search(node_type* __root, size_type __begin, size_type __end)
{
	if (__begin >= __root->end() || __end <= __root->begin())
		return _M_inf;
	
	if (__begin <= __root->begin() && __end >= __root->end())
		return __root->data();
	
	return _M_func(_M_search(__root->left(), __begin, __end),
		_M_search(__root->right(), __begin, __end));
}

template<typename _Tp, typename _Func>
template<typename _ModifyFunc>
void
segment_tree<_Tp, void, _Func>::
_M_modify(node_type* __root, size_type __pos, const _Tp& __x,
	const _ModifyFunc& __func)
{
	if (__root->is_leaf())
	{
		if (__pos == __root->begin())
			__func(__root, __x);
		
		return;
	}
	
	if (__pos < __root->middle())
		_M_modify(__root->left(), __pos, __x, __func);
	else
		_M_modify(__root->right(), __pos, __x, __func);
	
	push_up(__root);
}

template<typename _Tp, typename _Func>
template<typename _ModifyFunc>
void
segment_tree<_Tp, void, _Func>::
_M_modify(node_type* __root, size_type __begin, size_type __end,
	const value_type& __x, const _ModifyFunc& __func)
{
	if (__begin >= __root->end() || __end <= __root->begin())
		return;
	
	if (__begin <= __root->begin() && __end >= __root->end())
	{
		__func(__root, __x);
		return;
	}
	
	_M_modify(__root->left(), __begin, __end, __x, __func);
	_M_modify(__root->right(), __begin, __end, __x, __func);
	
	push_up(__root);
}

//@}

#ifndef POL_DEPRECATED
// @segment_tree_simple
//@{

template<typename _Tp, typename _MarkT, typename _Func, typename _ModF>
inline
segment_tree_simple<_Tp, _MarkT, _Func, _ModF>::
segment_tree_simple()
	: _M_root(), _M_func(), _M_mod(), _M_begin(), _M_end(), _M_inf()
{
}

template<typename _Tp, typename _MarkT, typename _Func, typename _ModF>
template<typename _Sequence>
inline
segment_tree_simple<_Tp, _MarkT, _Func, _ModF>::
segment_tree_simple(size_type __begin, size_type __end,
	const _Sequence& __data)
	: _M_root(new segment_tree_node<_Tp, _MarkT>(__begin, __end)),
		_M_func(), _M_mod(), _M_begin(__begin), _M_end(__end), _M_inf()
{
	_M_construct(_M_root, __data, _M_begin, _M_end);
}

template<typename _Tp, typename _MarkT, typename _Func, typename _ModF>
inline
segment_tree_simple<_Tp, _MarkT, _Func, _ModF>::
~segment_tree_simple() noexcept
{
	delete _M_root;
}

template<typename _Tp, typename _MarkT, typename _Func, typename _ModF>
inline segment_tree_node<_Tp, _MarkT>*&
segment_tree_simple<_Tp, _MarkT, _Func, _ModF>::
root()
{
	return _M_root;
}

template<typename _Tp, typename _MarkT, typename _Func, typename _ModF>
inline const segment_tree_node<_Tp, _MarkT>*&
segment_tree_simple<_Tp, _MarkT, _Func, _ModF>::
root() const
{
	return _M_root;
}

template<typename _Tp, typename _MarkT, typename _Func, typename _ModF>
inline _Tp&
segment_tree_simple<_Tp, _MarkT, _Func, _ModF>::
infinite()
{
	return _M_inf;
}

template<typename _Tp, typename _MarkT, typename _Func, typename _ModF>
template<typename _Sequence>
inline segment_tree_simple<_Tp, _MarkT, _Func, _ModF>&
segment_tree_simple<_Tp, _MarkT, _Func, _ModF>::
construct(size_type __begin, size_type __end, const _Sequence& __data)
{
	_M_destroy();
	_M_root = new segment_tree_node<_Tp, _MarkT>(__begin, __end);
	_M_begin = __begin;
	_M_end = __end;
	_M_construct(_M_root, __data, __begin, __end);
	return *this;
}

template<typename _Tp, typename _MarkT, typename _Func, typename _ModF>
inline segment_tree_simple<_Tp, _MarkT, _Func, _ModF>&
segment_tree_simple<_Tp, _MarkT, _Func, _ModF>::
destroy()
{
	_M_destroy();
	return *this;
}

template<typename _Tp, typename _MarkT, typename _Func, typename _ModF>
inline _Tp
segment_tree_simple<_Tp, _MarkT, _Func, _ModF>::
search(size_type __begin, size_type __end)
{
	return (_M_root ? _M_search(_M_root, _M_begin, _M_end, __begin, __end)
		: _M_inf);
}

template<typename _Tp, typename _MarkT, typename _Func, typename _ModF>
segment_tree_simple<_Tp, _MarkT, _Func, _ModF>&
segment_tree_simple<_Tp, _MarkT, _Func, _ModF>::
push_down(node_type* __pos)
{
	if (__pos != 0)
		if (__pos->mark() != mark_type())
		{
			_M_mod(__pos->left(), __pos->mark());
			_M_mod(__pos->right(), __pos->mark());
			__pos->mark() = mark_type();
		}
	
	return *this;
}

template<typename _Tp, typename _MarkT, typename _Func, typename _ModF>
inline segment_tree_simple<_Tp, _MarkT, _Func, _ModF>&
segment_tree_simple<_Tp, _MarkT, _Func, _ModF>::
modify(size_type __pos, const value_type& __x)
{
	if (_M_root)
		_M_modify(_M_root, _M_begin, _M_end, __pos, __x);
	
	return *this;
}

template<typename _Tp, typename _MarkT, typename _Func, typename _ModF>
inline segment_tree_simple<_Tp, _MarkT, _Func, _ModF>&
segment_tree_simple<_Tp, _MarkT, _Func, _ModF>::
modify(size_type __begin, size_type __end, const value_type& __x)
{
	if (_M_root)
		_M_modify(_M_root, _M_begin, _M_end, __begin, __end, __x);
	
	return *this;
}

template<typename _Tp, typename _MarkT, typename _Func, typename _ModF>
template<typename _Sequence>
void
segment_tree_simple<_Tp, _MarkT, _Func, _ModF>::
_M_construct(node_type* __root, const _Sequence& __data,
	size_type __begin, size_type __end)
{
	if (__begin == __end - size_type(1))
		__root->data() = __data[__begin];
	else
	{
		size_type __mid = (__begin + __end) >> size_type(1);
		
		__root->left() = new segment_tree_node<_Tp, _MarkT>(__begin, __mid);
		__root->right() = new segment_tree_node<_Tp, _MarkT>(__mid, __end);
		
		_M_construct(__root->left(), __data, __begin, __mid);
		_M_construct(__root->right(), __data, __mid, __end);
		
		__root->data() = _M_func(__root->left()->data(),
			__root->right()->data());
	}
}

template<typename _Tp, typename _MarkT, typename _Func, typename _ModF>
inline void
segment_tree_simple<_Tp, _MarkT, _Func, _ModF>::
_M_destroy()
{
	delete _M_root;
	_M_root = 0;
}

template<typename _Tp, typename _MarkT, typename _Func, typename _ModF>
_Tp
segment_tree_simple<_Tp, _MarkT, _Func, _ModF>::
_M_search(node_type* __root, size_type __begin, size_type __end,
	size_type __first, size_type __last)
{
	if (__first >= __end || __last <= __begin)
		return _M_inf;
	
	if (__first <= __begin && __last >= __end)
		return __root->data();
	
	push_down(__root);
	
	size_type __mid = (__begin + __end) >> size_type(1);
	
	return _M_func(_M_search(__root->left(), __begin, __mid, __first,
		__last), _M_search(__root->right(), __mid, __end, __first, __last));
}

template<typename _Tp, typename _MarkT, typename _Func, typename _ModF>
void
segment_tree_simple<_Tp, _MarkT, _Func, _ModF>::
_M_modify(node_type* __root, size_type __begin, size_type __end,
	size_type __pos, const _Tp& __x)
{
	if (__begin == __end - size_type(1))
	{
		if (__pos == __begin)
			_M_mod(__root, __x);
		
		return;
	}
	
	push_down(__root);
	
	size_type __mid = (__begin + __end) >> size_type(1);
	
	if (__pos < __mid)
		_M_modify(__root->left(), __begin, __mid, __pos, __x);
	else
		_M_modify(__root->right(), __mid, __end, __pos, __x);
	
	__root->data() = _M_func(__root->left()->data(),
		__root->right()->data());
}

template<typename _Tp, typename _MarkT, typename _Func, typename _ModF>
void
segment_tree_simple<_Tp, _MarkT, _Func, _ModF>::
_M_modify(node_type* __root, size_type __begin, size_type __end,
	size_type __first, size_type __last, const value_type& __x)
{
	if (__first >= __end || __last <= __begin)
		return;
	
	if (__first <= __begin && __last >= __end)
	{
		_M_mod(__root, __x);
		return;
	}
	
	push_down(__root);
	
	size_type __mid = (__begin + __end) >> size_type(1);
	
	_M_modify(__root->left(), __begin, __mid, __first, __last, __x);
	_M_modify(__root->right(), __mid, __end, __first, __last, __x);
	
	__root->data() = _M_func(__root->left()->data(),
		__root->right()->data());
}

//@}
#endif

}

#endif /* _POL_SEGTREE_TCC */
