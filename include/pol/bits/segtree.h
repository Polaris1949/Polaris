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

/** @file        bits/segtree.h
 *  @brief       Segment tree
 *  @author      Polaris Zhao
 *  @version     0.8.0
 *  @todo        Revision.
 *
 *  This is an internal header file, included by other library headers.
 *  Do not attempt to use it directly. @headername{segment_tree}
**/

#ifndef _POL_SEGTREE_H
#define _POL_SEGTREE_H 1

// TODO: Dynamic segment tree

namespace pol
{

// @segment_tree_node_data
template<typename _Tp, typename _MarkT>
struct segment_tree_node_data
{
	using data_type = _Tp;
	using mark_type = _MarkT;
	_Tp data;
	_MarkT mark;
};

template<typename _Tp>
struct segment_tree_node_data<_Tp, void>
{
	using data_type = _Tp;
	using mark_type = void;
	_Tp data;
};

// @segment_tree_node
template<typename _Tp, typename _MarkT>
class segment_tree_node
{
public:
	typedef _Tp                             value_type;
	typedef _MarkT                          mark_type;
	typedef segment_tree_node<_Tp, _MarkT>  node_type;
	typedef std::size_t                     size_type;

private:
	node_type* _M_left;
	node_type* _M_right;
	size_type _M_begin;
	size_type _M_end;
	value_type _M_data;
	mark_type _M_mark;

public:
	segment_tree_node();

	segment_tree_node(size_type __begin, size_type __end);

	~segment_tree_node() noexcept;

	node_type&
	construct(size_type __begin, size_type __end);

	node_type&
	destroy() noexcept;

	node_type*&
	left() noexcept;

	const node_type*&
	left() const noexcept;

	node_type*&
	left_d();

	node_type*&
	right() noexcept;

	const node_type*&
	right() const noexcept;

	node_type*&
	right_d();

	value_type&
	data() noexcept;

	const value_type&
	data() const noexcept;

	mark_type&
	mark() noexcept;

	const mark_type&
	mark() const noexcept;

	size_type
	begin() const noexcept;

	size_type
	end() const noexcept;

	size_type
	middle() const noexcept;

	size_type
	segment() const noexcept;

	bool
	is_leaf() const noexcept;

private:
	void _M_construct(size_type __begin, size_type __end);

	void _M_destroy() noexcept;
};

// @segment_tree_node<_Tp, void>
template<typename _Tp>
class segment_tree_node<_Tp, void>
{
public:
	typedef _Tp                           value_type;
	typedef void                          mark_type;
	typedef segment_tree_node<_Tp, void>  node_type;
	typedef std::size_t                   size_type;

private:
	node_type* _M_left;
	node_type* _M_right;
	size_type _M_begin;
	size_type _M_end;
	value_type _M_data;

public:
	segment_tree_node();

	segment_tree_node(size_type __begin, size_type __end);

	~segment_tree_node() noexcept;

	node_type&
	construct(size_type __begin, size_type __end);

	node_type&
	destroy();

	node_type*&
	left();

	const node_type*&
	left() const;

	node_type*&
	right();

	const node_type*&
	right() const;

	value_type&
	data();

	const value_type&
	data() const;

	size_type
	begin() const;

	size_type
	end() const;

	size_type
	middle() const;

	size_type
	segment() const;

	bool
	is_leaf() const;

private:
	void _M_construct(size_type __begin, size_type __end);

	void _M_destroy();
};

// TODO: Iterators & Compability
template<typename _Tp, typename _MarkT>
class segment_tree_iterator
// : public tree_iterator<segment_tree_node<_Tp, _MarkT>>
{
public:
	typedef _Tp data_type;
	typedef _MarkT mark_type;
	typedef segment_tree_node<_Tp, _MarkT> node_type;
	typedef segment_tree_iterator<_Tp, _MarkT> iterator;

private:
	node_type* _M_p;

public:
	iterator& operator++ ();
	iterator& operator-- ();
};

// @segment_tree
template<typename _Tp, typename _MarkT, typename _Func>
class segment_tree
{
public:
	typedef _Tp                               value_type; // TODO: Compatibility
	typedef _MarkT                            mark_type;
	typedef _Func                             data_func;
	typedef std::size_t                       size_type;
	typedef segment_tree_node<_Tp, _MarkT>    node_type;
	typedef segment_tree<_Tp, _MarkT, _Func>  tree_type;
	typedef segment_tree_iterator<_Tp, _MarkT> iterator;
	typedef const segment_tree_iterator<_Tp, _MarkT> const_iterator;

private:
	node_type* _M_root;
	value_type _M_inf; // FIXME: What is this? Do we need it?
	data_func _M_func;

public:
	segment_tree();

	segment_tree(size_type __beg, size_type __end);

	template<typename _Sequence>
	segment_tree(size_type __begin, size_type __end, const _Sequence& __data);

	~segment_tree() noexcept;

	tree_type&
	construct(size_type __begin, size_type __end);

	template<typename _Sequence>
	tree_type&
	construct(size_type __begin, size_type __end, const _Sequence& __data);

	tree_type&
	destroy();

	node_type*&
	root();

	const node_type*&
	root() const;

	value_type&
	infinite();

	const value_type&
	infinite() const;

	const data_func&
	data_functor() const;

	size_type
	begin() const;

	size_type
	end() const;

	tree_type&
	push_up(node_type* __pos);

	template<typename _MarkFunc>
	tree_type&
	push_down(node_type* __pos, const _MarkFunc& __mark);

	template<typename _MarkFunc>
	value_type
	search(size_type __begin, size_type __end, const _MarkFunc& __mark);

	template<typename _ModifyFunc, typename _MarkFunc>
	tree_type&
	modify(size_type __pos, const value_type& __x, const _ModifyFunc& __func,
		const _MarkFunc& __mark);

	template<typename _ModifyFunc, typename _MarkFunc>
	tree_type&
	modify(size_type __begin, size_type __end, const value_type& __x,
		const _ModifyFunc& __func, const _MarkFunc& __mark);

	template<typename _ModifyFunc, typename _MarkFunc>
	tree_type&
	modify_d(size_type __begin, size_type __end, const value_type& __x,
		const _ModifyFunc& __func, const _MarkFunc& __mark);

private:
	template<typename _Sequence>
	void
	_M_construct(node_type* __root, const _Sequence& __data);

	void
	_M_destroy();

	template<typename _MarkFunc>
	_Tp
	_M_search(node_type* __root, size_type __begin, size_type __end,
		const _MarkFunc& __mark);

	template<typename _ModifyFunc, typename _MarkFunc>
	void
	_M_modify(node_type* __root, size_type __pos, const value_type& __x,
		const _ModifyFunc& __func, const _MarkFunc& __mark);

	template<typename _ModifyFunc, typename _MarkFunc>
	void
	_M_modify(node_type* __root, size_type __begin, size_type __end,
		const value_type& __x, const _ModifyFunc& __func,
		const _MarkFunc& __mark);

	template<typename _ModifyFunc, typename _MarkFunc>
	void
	_M_modify_d(node_type* __root, size_type __begin, size_type __end,
		const value_type& __x, const _ModifyFunc& __func,
		const _MarkFunc& __mark);
};

// @segment_tree<_Tp, void, _Func>
template<typename _Tp, typename _Func>
class segment_tree<_Tp, void, _Func>
{
public:
	typedef _Tp                             value_type;
	typedef void                            mark_type;
	typedef _Func                           data_func;
	typedef std::size_t                     size_type;
	typedef segment_tree_node<_Tp, void>    node_type;
	typedef segment_tree<_Tp, void, _Func>  tree_type;

private:
	node_type* _M_root;
	value_type _M_inf;
	data_func _M_func;

public:
	segment_tree();

	template<typename _Sequence>
	segment_tree(size_type __begin, size_type __end, const _Sequence& __data);

	~segment_tree() noexcept;

	template<typename _Sequence>
	tree_type&
	construct(size_type __begin, size_type __end, const _Sequence& __data);

	tree_type&
	destroy();

	node_type*&
	root();

	const node_type*&
	root() const;

	value_type&
	infinite();

	const value_type&
	infinite() const;

	const data_func&
	data_functor() const;

	size_type
	begin() const;

	size_type
	end() const;

	tree_type&
	push_up(node_type* __pos);

	value_type
	search(size_type __begin, size_type __end);

	template<typename _ModifyFunc>
	tree_type&
	modify(size_type __pos, const value_type& __x, const _ModifyFunc& __func);

	template<typename _ModifyFunc>
	tree_type&
	modify(size_type __begin, size_type __end, const value_type& __x,
		const _ModifyFunc& __func);

private:
	template<typename _Sequence>
	void
	_M_construct(node_type* __root, const _Sequence& __data);

	void
	_M_destroy();

	_Tp
	_M_search(node_type* __root, size_type __begin, size_type __end);

	template<typename _ModifyFunc>
	void
	_M_modify(node_type* __root, size_type __pos, const value_type& __x,
		const _ModifyFunc& __func);

	template<typename _ModifyFunc>
	void
	_M_modify(node_type* __root, size_type __begin, size_type __end,
		const value_type& __x, const _ModifyFunc& __func);
};

#if !POL_DEPRECATED
// @segment_tree_simple
template<typename _Tp, typename _MarkT, typename _Func, typename _ModF>
class segment_tree_simple
{
public:
	typedef _Tp                                             value_type;
	typedef _MarkT                                          mark_type;
	typedef _Func                                           data_func;
	typedef _ModF                                           modify_func;
	typedef std::size_t                                     size_type;
	typedef segment_tree_node<_Tp, _MarkT>                  node_type;
	typedef segment_tree_simple<_Tp, _MarkT, _Func, _ModF>  tree_type;

private:
	node_type* _M_root;
	size_type _M_begin;
	size_type _M_end;
	value_type _M_inf;
	data_func _M_func;
	modify_func _M_mod;

public:
	segment_tree_simple();

	template<typename _Sequence>
	segment_tree_simple(size_type __begin, size_type __end,
		const _Sequence& __data);

	~segment_tree_simple() noexcept;

	node_type*&
	root();

	value_type&
	infinite();

	const node_type*&
	root() const;

	const value_type&
	infinite() const;

	template<typename _Sequence>
	tree_type&
	construct(size_type __begin, size_type __end, const _Sequence& __data);

	tree_type&
	destroy();

	value_type
	search(size_type __begin, size_type __end);

	tree_type&
	push_down(node_type* __pos);

	tree_type&
	modify(size_type __pos, const value_type& __x);

	tree_type&
	modify(size_type __begin, size_type __end, const value_type& __x);

private:
	template<typename _Sequence>
	void
	_M_construct(node_type* __root, const _Sequence& __data,
		size_type __begin, size_type __end);

	void
	_M_destroy();

	_Tp
	_M_search(node_type* __root, size_type __begin, size_type __end,
		size_type __first, size_type __last);

	void
	_M_modify(node_type* __root, size_type __begin, size_type __end,
		size_type __pos, const value_type& __x);

	void
	_M_modify(node_type* __root, size_type __begin, size_type __end,
		size_type __first, size_type __last, const value_type& __x);
};
#endif

}

#endif /* _POL_SEGTREE_H */
