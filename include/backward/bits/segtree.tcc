#ifndef _STDEXT_BITS_SEGTREE_S_TCC
#define _STDEXT_BITS_SEGTREE_S_TCC

#include <polext/backward/bits/segtree.h>

namespace stdext
{

template<typename _Tp, typename _MarkT>
segment_tree_node<_Tp, _MarkT>::
segment_tree_node()
	: _M_begin(), _M_end(), _M_left(), _M_right(), _M_data(), _M_mark()
{
}

template<typename _Tp, typename _MarkT>
segment_tree_node<_Tp, _MarkT>::
segment_tree_node(size_type __begin, size_type __end)
	: _M_begin(__begin), _M_end(__end), _M_left(), _M_right(), _M_data(),
		_M_mark()
{
}

template<typename _Tp, typename _MarkT>
segment_tree_node<_Tp, _MarkT>::
~segment_tree_node() noexcept
{
	delete _M_left;
	delete _M_right;
}

template<typename _Tp, typename _MarkT>
inline segment_tree_node<_Tp, _MarkT>*&
segment_tree_node<_Tp, _MarkT>::
left()
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
inline _Tp&
segment_tree_node<_Tp, _MarkT>::
data()
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
inline const segment_tree_node<_Tp, _MarkT>*&
segment_tree_node<_Tp, _MarkT>::
left() const
{
	return _M_left;
}

template<typename _Tp, typename _MarkT>
inline const segment_tree_node<_Tp, _MarkT>*&
segment_tree_node<_Tp, _MarkT>::
right() const
{
	return _M_right;
}

template<typename _Tp, typename _MarkT>
inline const _Tp&
segment_tree_node<_Tp, _MarkT>::
data() const
{
	return _M_data;
}

template<typename _Tp, typename _MarkT>
inline const _MarkT&
segment_tree_node<_Tp, _MarkT>::
mark() const
{
	return _M_mark;
}

template<typename _Tp, typename _MarkT>
std::size_t
segment_tree_node<_Tp, _MarkT>::
segment() const
{
	return _M_end - _M_begin;
}

template<typename _Tp, typename _MarkT, typename _Func, typename _ModF>
segment_tree<_Tp, _MarkT, _Func, _ModF>::
segment_tree()
	: _M_root(), _M_func(), _M_mod(), _M_begin(), _M_end(), _M_inf()
{
}

template<typename _Tp, typename _MarkT, typename _Func, typename _ModF>
template<typename _Sequence>
segment_tree<_Tp, _MarkT, _Func, _ModF>::
segment_tree(size_type __begin, size_type __end, const _Sequence& __data)
	: _M_root(new segment_tree_node<_Tp, _MarkT>(__begin, __end)), _M_func(),
		_M_mod(), _M_begin(__begin), _M_end(__end), _M_inf()
{
	_M_construct(_M_root, __data, _M_begin, _M_end);
}

template<typename _Tp, typename _MarkT, typename _Func, typename _ModF>
segment_tree<_Tp, _MarkT, _Func, _ModF>::
~segment_tree() noexcept
{
	delete _M_root;
}

template<typename _Tp, typename _MarkT, typename _Func, typename _ModF>
inline segment_tree_node<_Tp, _MarkT>*&
segment_tree<_Tp, _MarkT, _Func, _ModF>::
root()
{
	return _M_root;
}

template<typename _Tp, typename _MarkT, typename _Func, typename _ModF>
inline const segment_tree_node<_Tp, _MarkT>*&
segment_tree<_Tp, _MarkT, _Func, _ModF>::
root() const
{
	return _M_root;
}

template<typename _Tp, typename _MarkT, typename _Func, typename _ModF>
inline _Tp&
segment_tree<_Tp, _MarkT, _Func, _ModF>::
infinite()
{
	return _M_inf;
}

template<typename _Tp, typename _MarkT, typename _Func, typename _ModF>
template<typename _Sequence>
segment_tree<_Tp, _MarkT, _Func, _ModF>&
segment_tree<_Tp, _MarkT, _Func, _ModF>::
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
segment_tree<_Tp, _MarkT, _Func, _ModF>&
segment_tree<_Tp, _MarkT, _Func, _ModF>::
destroy()
{
	_M_destroy();
	return *this;
}

template<typename _Tp, typename _MarkT, typename _Func, typename _ModF>
_Tp
segment_tree<_Tp, _MarkT, _Func, _ModF>::
search(size_type __begin, size_type __end)
{
	return (_M_root ? _M_search(_M_root, _M_begin, _M_end, __begin, __end)
		: _M_inf);
}

template<typename _Tp, typename _MarkT, typename _Func, typename _ModF>
segment_tree<_Tp, _MarkT, _Func, _ModF>&
segment_tree<_Tp, _MarkT, _Func, _ModF>::
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
segment_tree<_Tp, _MarkT, _Func, _ModF>&
segment_tree<_Tp, _MarkT, _Func, _ModF>::
modify(size_type __pos, const value_type& __x)
{
	if (_M_root)
		_M_modify(_M_root, _M_begin, _M_end, __pos, __x);
	
	return *this;
}

template<typename _Tp, typename _MarkT, typename _Func, typename _ModF>
segment_tree<_Tp, _MarkT, _Func, _ModF>&
segment_tree<_Tp, _MarkT, _Func, _ModF>::
modify(size_type __begin, size_type __end, const value_type& __x)
{
	if (_M_root)
		_M_modify(_M_root, _M_begin, _M_end, __begin, __end, __x);
	
	return *this;
}

template<typename _Tp, typename _MarkT, typename _Func, typename _ModF>
template<typename _Sequence>
void
segment_tree<_Tp, _MarkT, _Func, _ModF>::
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
void
segment_tree<_Tp, _MarkT, _Func, _ModF>::
_M_destroy()
{
	delete _M_root;
	_M_root = 0;
}

template<typename _Tp, typename _MarkT, typename _Func, typename _ModF>
_Tp
segment_tree<_Tp, _MarkT, _Func, _ModF>::
_M_search(node_type* __root, size_type __begin, size_type __end,
	size_type __first, size_type __last)
{
	if (__first >= __end || __last <= __begin)
		return _M_inf;
	
	if (__first <= __begin && __last >= __end)
		return __root->data();
	
	push_down(__root);
	
	size_type __mid = (__begin + __end) >> size_type(1);
	
	return _M_func(_M_search(__root->left(), __begin, __mid, __first, __last),
		_M_search(__root->right(), __mid, __end, __first, __last));
}

template<typename _Tp, typename _MarkT, typename _Func, typename _ModF>
void
segment_tree<_Tp, _MarkT, _Func, _ModF>::
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
	
	__root->data() = _M_func(__root->left()->data(), __root->right()->data());
}

template<typename _Tp, typename _MarkT, typename _Func, typename _ModF>
void
segment_tree<_Tp, _MarkT, _Func, _ModF>::
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
	
	__root->data() = _M_func(__root->left()->data(), __root->right()->data());
}

}

#endif
