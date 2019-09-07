// Link-cut tree implementation -*- C++ -*-

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

/** @file        bits/lctree.tcc
 *  @headerfile  link_cut_tree
 *  @brief       Link-cut tree implementation
 *  @author      Polaris Zhao
 *  @version     3.0
 *
 *  This is an internal header file, included by other library headers.
 *  Do not attempt to use it directly.
**/

#ifndef _POL_LCTREE_TCC
#define _POL_LCTREE_TCC 1

namespace polaris
{

template<typename _Tp>
link_cut_tree_node<_Tp>::
link_cut_tree_node(const value_type& __x)
    : base_type{__x}, _M_value{__x}, _M_mark{false}
{}

template<typename _Tp>
inline _Tp&
link_cut_tree_node<_Tp>::
value()
{ return this->_M_value; }

template<typename _Tp>
inline const _Tp&
link_cut_tree_node<_Tp>::
value() const
{ return this->_M_value; }

template<typename _Tp>
inline bool&
link_cut_tree_node<_Tp>::
mark()
{ return this->_M_mark; }

template<typename _Tp>
inline const bool&
link_cut_tree_node<_Tp>::
mark() const
{ return this->_M_mark; }

template<typename _Tp>
void
link_cut_tree_node<_Tp>::
reverse()
{
    std::swap(this->left(), this->right());
    this->mark() ^= true;
}

template<typename _Tp>
template<typename _Seq>
link_cut_tree<_Tp>::
link_cut_tree(const _Seq& __data)
{ this->construct(__data); }

template<typename _Tp>
link_cut_tree<_Tp>::
~link_cut_tree() noexcept
{ this->destroy(); }

template<typename _Tp>
template<typename _Seq>
link_cut_tree<_Tp>&
link_cut_tree<_Tp>::
construct(const _Seq& __data)
{
    for (const value_type& __elem : __data)
        this->_M_node.push_back(new node_type{__elem});

    return *this;
}

template<typename _Tp>
link_cut_tree<_Tp>&
link_cut_tree<_Tp>::
destroy()
{
    for (node_type*& __elem : this->_M_node)
        delete __elem;

    return *this;
}

template<typename _Tp>
inline void
link_cut_tree<_Tp>::
link(size_type __x, size_type __y)
{ this->_M_link(this->_M_node[__x], this->_M_node[__y]); }

template<typename _Tp>
inline void
link_cut_tree<_Tp>::
cut(size_type __x, size_type __y)
{ this->_M_cut(this->_M_node[__x], this->_M_node[__y]); }

template<typename _Tp>
inline void
link_cut_tree<_Tp>::
assign(size_type __x, const value_type& __y)
{ this->_M_assign(this->_M_node[__x], __y); }

template<typename _Tp>
inline _Tp
link_cut_tree<_Tp>::
xor_sum(size_type __x, size_type __y)
{ return this->_M_xor_sum(this->_M_node[__x], this->_M_node[__y]); }

template<typename _Tp>
void
link_cut_tree<_Tp>::
_M_push_up(node_type* __x)
{
    value_type __ld{};
    value_type __rd{};

    if (__x->left()) __ld = __x->left()->data();
    if (__x->right()) __rd = __x->right()->data();

    __x->data() = __ld ^ __rd ^ __x->value();
}

template<typename _Tp>
void
link_cut_tree<_Tp>::
_M_push_down(node_type* __x)
{
    if (!__x->mark()) return;

    __x->mark() = false;

    node_type* __l{static_cast<node_type*>(__x->left())};
    node_type* __r{static_cast<node_type*>(__x->right())};

    if (__l) __l->reverse();
    if (__r) __r->reverse();
}

template<typename _Tp>
inline bool
link_cut_tree<_Tp>::
_M_is_root(node_type* __x)
{
    node_base* __p{__x->parent()};
    if (__p == nullptr) return true;
    return __p->left() != __x && __p->right() != __x;
}

template<typename _Tp>
void
link_cut_tree<_Tp>::
_M_rotate(node_type* __x)
{
    node_type* __y{static_cast<node_type*>(__x->parent())};
    node_type* __z{static_cast<node_type*>(__y->parent())};
    bool __l{__y->right() == __x};
    bool __r{__l ^ true};

    if (!this->_M_is_root(__y))
    {
        if (__z->left() == __y) __z->left() = __x;
        else __z->right() = __x;
    }

    __x->parent() = __z;
    __y->parent() = __x;
    if (__x->child(__r)) __x->child(__r)->parent() = __y;
    __y->child(__l) = __x->child(__r);
    __x->child(__r) = __y;

    this->_M_push_up(__y);
    this->_M_push_up(__x);
}

template<typename _Tp>
void
link_cut_tree<_Tp>::
_M_splay(node_type* __x)
{
    std::stack<node_type*> __st;
    __st.push(__x);

    for (node_type* __i{__x}; !this->_M_is_root(__i);
            __i = static_cast<node_type*>(__i->parent()))
        __st.push(static_cast<node_type*>(__i->parent()));

    while (!__st.empty())
    {
        this->_M_push_down(__st.top());
        __st.pop();
    }

    while (!this->_M_is_root(__x))
    {
        node_type* __y{static_cast<node_type*>(__x->parent())};
        node_type* __z{static_cast<node_type*>(__y->parent())};

        if (!this->_M_is_root(__y))
        {
            if ((__y->left() == __x) ^ (__z->left() == __y))
                this->_M_rotate(__x);
            else
                this->_M_rotate(__y);
        }

        this->_M_rotate(__x);
    }
}

template<typename _Tp>
void
link_cut_tree<_Tp>::
_M_access(node_type* __x)
{
    node_type* __t{nullptr};

    while (__x)
    {
        this->_M_splay(__x);
        __x->right() = __t;
        this->_M_push_up(__x);
        __t = __x;
        __x = static_cast<node_type*>(__x->parent());
    }
}

template<typename _Tp>
inline void
link_cut_tree<_Tp>::
_M_make_root(node_type* __x)
{
    this->_M_access(__x);
    this->_M_splay(__x);
    __x->reverse();
}

template<typename _Tp>
link_cut_tree_node<_Tp>*
link_cut_tree<_Tp>::
_M_find(node_type* __x)
{
    this->_M_access(__x);
    this->_M_splay(__x);

    while (__x->left())
        __x = static_cast<node_type*>(__x->left());

    return __x;
}

template<typename _Tp>
inline void
link_cut_tree<_Tp>::
_M_split(node_type* __x, node_type* __y)
{
    this->_M_make_root(__x);
    this->_M_access(__y);
    this->_M_splay(__y);
}

template<typename _Tp>
void
link_cut_tree<_Tp>::
_M_link(node_type* __x, node_type* __y)
{
    if (this->_M_find(__x) == this->_M_find(__y))
        return;

    this->_M_make_root(__x);
    __x->parent() = __y;
}

template<typename _Tp>
void
link_cut_tree<_Tp>::
_M_cut(node_type* __x, node_type* __y)
{
    if (this->_M_find(__x) != this->_M_find(__y))
        return;

    this->_M_split(__x, __y);

    if (__y->left() == __x && __x->right() == nullptr)
    {
        __y->left() = nullptr;
        __x->parent() = nullptr;
    }
}

template<typename _Tp>
inline void
link_cut_tree<_Tp>::
_M_assign(node_type* __x, const value_type& __y)
{
    this->_M_access(__x);
    this->_M_splay(__x);
    __x->value() = __y;
    this->_M_push_up(__x);
}

template<typename _Tp>
inline _Tp
link_cut_tree<_Tp>::
_M_xor_sum(node_type* __x, node_type* __y)
{
    this->_M_split(__x, __y);
    return __y->data();
}

}

#endif /* _POL_LCTREE_TCC */
