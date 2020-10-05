// Binary tree implementation -*- C++ -*-

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

/** @file        bits/bintree.tcc
 *  @brief       Binary tree implementation
 *  @author      Polaris Zhao
 *  @version     0.8.0
 *  @todo        Incomplete.
 *
 *  This is an internal header file, included by other library headers.
 *  Do not attempt to use it directly. @headername{binary_tree}
**/

#ifndef _POL_BINTREE_TCC
#define _POL_BINTREE_TCC 1

namespace pol
{

inline
binary_tree_node_base::
binary_tree_node_base() noexcept
    : _M_parent(), _M_left(), _M_right()
{ }

inline binary_tree_node_base*&
binary_tree_node_base::
parent() noexcept
{ return this->_M_parent; }

inline binary_tree_node_base*
binary_tree_node_base::
parent() const noexcept
{ return this->_M_parent; }

inline binary_tree_node_base*&
binary_tree_node_base::
child(bool __n) noexcept
{ return __n ? this->_M_right : this->_M_left; }

inline binary_tree_node_base*
binary_tree_node_base::
child(bool __n) const noexcept
{ return __n ? this->_M_right : this->_M_left; }

inline binary_tree_node_base*&
binary_tree_node_base::
child(size_type __n)
{
    if (__n >= size_type(2))
        throw std::out_of_range("binary_tree_node_base::child");
    return this->child(bool(__n));
}

inline binary_tree_node_base*
binary_tree_node_base::
child(size_type __n) const
{
    if (__n >= size_type(2))
        throw std::out_of_range("binary_tree_node_base::child");
    return this->child(bool(__n));
}

template<typename _IntTp>
inline binary_tree_node_base*&
binary_tree_node_base::
child(_IntTp __n)
{ return this->child(size_type(__n)); }

template<typename _IntTp>
inline binary_tree_node_base*
binary_tree_node_base::
child(_IntTp __n) const
{ return this->child(size_type(__n)); }

inline binary_tree_node_base*&
binary_tree_node_base::
left() noexcept
{ return this->_M_left; }

inline binary_tree_node_base*
binary_tree_node_base::
left() const noexcept
{ return this->_M_left; }

#if POL_NEWLIB
template<typename _Alloc>
inline binary_tree_node_base*&
binary_tree_node_base<_Alloc>::
left_d()
{
    if (this->_M_left == nullptr)
        this->_M_left = get_global_alloc<_Alloc>().allocate(sizeof(binary_tree_node_base<_Alloc>));
        // this->_M_left = this->_M_alloc->allocate(sizeof(binary_tree_node_base<_Alloc>));
    return this->_M_left;
}

template<typename _Al>
inline binary_tree_node_base*&
binary_tree_node_base::
left_d(_Al& __alloc)
{
    if (this->_M_left == nullptr)
        this->_M_left = __alloc.allocate(sizeof(binary_tree_node_base));
    return this->_M_left;
}
#endif

inline binary_tree_node_base*&
binary_tree_node_base::
right() noexcept
{ return this->_M_right; }

inline binary_tree_node_base*
binary_tree_node_base::
right() const noexcept
{ return this->_M_right; }

#if POL_NEWLIB
inline binary_tree_node_base*&
binary_tree_node_base<_Alloc>::
right_d()
{
    if (this->_M_right == nullptr)
        this->_M_right = get_global_alloc<_Alloc>().allocate(sizeof(binary_tree_node_base<_Alloc>));
        //this->_M_right = this->_M_alloc->allocate(sizeof(binary_tree_node_base<_Alloc>));
    return this->_M_right;
}
#endif

inline bool
binary_tree_node_base::
is_branch() const noexcept
{ return this->degree() > 0; }

inline bool
binary_tree_node_base::
is_leaf() const noexcept
{ return this->degree() == 0; }

inline size_t
binary_tree_node_base::
degree() const noexcept
{
    return size_type{this->_M_left != nullptr}
        + size_type{this->_M_right != nullptr};
}

size_t
binary_tree_node_base::
depth() const noexcept
{
    size_t __ret = 0;
    base_type const* __root = this;
    while ((__root = __root->parent()) != nullptr)
        ++__ret;
    return __ret;
}

template<typename _Tp>
binary_tree_node<_Tp>::
binary_tree_node()
    : binary_tree_node_base(), _M_data()
{ }

template<typename _Tp>
binary_tree_node<_Tp>::
binary_tree_node(const value_type& __x)
    : binary_tree_node_base(), _M_data(__x)
{ }

template<typename _Tp>
binary_tree_node<_Tp>::
binary_tree_node(value_type&& __x)
    : binary_tree_node_base(), _M_data(std::move(__x))
{ }

template<typename _Tp>
inline binary_tree_node<_Tp>&
binary_tree_node<_Tp>::
construct(const value_type& __x)
{
    this->_M_construct(__x);
    return *this;
}

template<typename _Tp>
inline binary_tree_node<_Tp>&
binary_tree_node<_Tp>::
destroy()
{
    this->_M_destroy();
    return *this;
}

template<typename _Tp>
inline binary_tree_node<_Tp>*&
binary_tree_node<_Tp>::
parent() noexcept
{ return this->base_type::parent(); }

template<typename _Tp>
inline binary_tree_node<_Tp>*
binary_tree_node<_Tp>::
parent() const noexcept
{ return this->base_type::parent(); }

template<typename _Tp>
inline binary_tree_node<_Tp>*&
binary_tree_node<_Tp>::
child(bool __n) noexcept
{ return this->base_type::child(__n); }

template<typename _Tp>
inline binary_tree_node<_Tp>*
binary_tree_node<_Tp>::
child(bool __n) const noexcept
{ return this->base_type::child(__n); }

template<typename _Tp>
inline binary_tree_node<_Tp>*&
binary_tree_node<_Tp>::
child(size_type __n)
{ return this->base_type::child(__n); }

template<typename _Tp>
inline binary_tree_node<_Tp>*
binary_tree_node<_Tp>::
child(size_type __n) const
{ return this->base_type::child(__n); }

template<typename _Tp>
template<typename _IntTp>
inline binary_tree_node<_Tp>*&
binary_tree_node<_Tp>::
child(_IntTp __n)
{ return this->base_type::child(__n); }

template<typename _Tp>
template<typename _IntTp>
inline binary_tree_node<_Tp>*
binary_tree_node<_Tp>::
child(_IntTp __n) const
{ return this->base_type::child(__n); }

template<typename _Tp>
inline binary_tree_node<_Tp>*&
binary_tree_node<_Tp>::
left() noexcept
{ return this->base_type::left(); }

template<typename _Tp>
inline binary_tree_node<_Tp>*
binary_tree_node<_Tp>::
left() const noexcept
{ return this->base_type::left(); }

template<typename _Tp>
inline binary_tree_node<_Tp>*&
binary_tree_node<_Tp>::
right() noexcept
{ return this->base_type::right(); }

template<typename _Tp>
inline binary_tree_node<_Tp>*
binary_tree_node<_Tp>::
right() const noexcept
{ return this->base_type::right(); }

template<typename _Tp>
inline _Tp&
binary_tree_node<_Tp>::
data() noexcept
{ return this->_M_data; }

template<typename _Tp>
inline _Tp
binary_tree_node<_Tp>::
data() const noexcept
{ return this->_M_data; }

template<typename _Tp>
void
binary_tree_node<_Tp>::
_M_construct(const value_type& __x)
{
    // NOTE: Here we should not do this.
#if 0
    new (&this->data()) value_type{__x};
#endif
}

template<typename _Tp>
void
binary_tree_node<_Tp>::
_M_destroy()
{
    if (this->left())
    {
        delete this->left();
        this->left() = nullptr;
    }

    if (this->right())
    {
        delete this->right();
        this->right() = nullptr;
    }

    // Note: Here we should not do this.
#if 0
    this->data().~value_type();
#endif
}

template<typename _Tp>
template<typename _Seq>
inline binary_tree<_Tp>&
binary_tree<_Tp>::
construct(const _Seq& __data)
{
    this->_M_construct(this->_M_root, __data);
    return *this;
}

template<typename _Tp>
inline binary_tree<_Tp>&
binary_tree<_Tp>::
destroy()
{
    this->_M_destroy(this->_M_root);
    return *this;
}

template<typename _Tp>
template<typename _Seq>
void
binary_tree<_Tp>::
_M_construct(node_type* __root, const _Seq& __data)
{
    // TODO...
}

template<typename _Tp>
void
binary_tree<_Tp>::
_M_destroy(node_type* __root)
{
    // TODO...
}

}

#endif
