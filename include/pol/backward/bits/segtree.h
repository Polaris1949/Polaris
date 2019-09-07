#ifndef _STDEXT_BITS_SEGTREE_S_H
#define _STDEXT_BITS_SEGTREE_S_H

#include <functional>

namespace stdext
{

template<typename _Tp, typename _MarkT>
class segment_tree_node
{
public:
	typedef _Tp                             value_type;
	typedef _MarkT                          mark_type;
	typedef segment_tree_node<_Tp, _MarkT>  node_type;
	typedef std::size_t                     size_type;
	
private:
	size_type _M_begin;
	size_type _M_end;
	segment_tree_node<_Tp, _MarkT>* _M_left;
	segment_tree_node<_Tp, _MarkT>* _M_right;
	_Tp _M_data;
	_MarkT _M_mark;
	
public:
	segment_tree_node();
	
	segment_tree_node(size_type __begin, size_type __end);
	
	~segment_tree_node() noexcept;
	
	node_type*&
	left();
	
	node_type*&
	right();
	
	value_type&
	data();
	
	mark_type&
	mark();
	
	const node_type*&
	left() const;
	
	const node_type*&
	right() const;
	
	const value_type&
	data() const;
	
	const mark_type&
	mark() const;
	
	size_type
	segment() const;
};

template<typename _Tp, typename _MarkT, typename _Func, typename _ModF>
class segment_tree
{
public:
	typedef _Tp                                      value_type;
	typedef _MarkT                                   mark_type;
	typedef _Func                                    data_func;
	typedef _ModF                                    modify_func;
	typedef std::size_t                              size_type;
	typedef segment_tree_node<_Tp, _MarkT>           node_type;
	typedef segment_tree<_Tp, _MarkT, _Func, _ModF>  tree_type;
	
private:
	segment_tree_node<_Tp, _MarkT>* _M_root;
	_Func _M_func;
	_ModF _M_mod;
	size_type _M_begin;
	size_type _M_end;
	_Tp _M_inf;
	
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
	
public:
	segment_tree();
	
	template<typename _Sequence>
	segment_tree(size_type __begin, size_type __end, const _Sequence& __data);
	
	~segment_tree() noexcept;
	
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
};

}

#endif
