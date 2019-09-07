// Tree array implementation -*- C++ -*-

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

/** @file        bits/treearr.tcc
 *  @headerfile  tree_array
 *  @brief       Tree array implementation
 *  @author      Polaris Zhao
 *  @version     3.0
 *
 *  This is an internal header file, included by other library headers.
 *  Do not attempt to use it directly.
**/

#ifndef _POL_TREEARR_TCC
#define _POL_TREEARR_TCC 1

namespace polaris
{

inline std::size_t
tree_array_base::
_S_lowbit(size_type __x)
{ return (__x + 1) & (~__x); }

template<typename _Tp>
template<typename _Seq>
tree_array<_Tp, tree_array_mode::mpir>::
tree_array(const _Seq& __data)
{ this->init(__data); }

template<typename _Tp>
template<typename _Seq>
void
tree_array<_Tp, tree_array_mode::mpir>::
init(const _Seq& __data)
{
    this->clear();
    this->resize(__data.size());

    for (size_type __i{}; __i < __data.size(); ++__i)
        this->modify(__i, __data[__i]);
}

template<typename _Tp>
bool
tree_array<_Tp, tree_array_mode::mpir>::
empty() const
{ return this->_M_tree.empty(); }

template<typename _Tp>
void
tree_array<_Tp, tree_array_mode::mpir>::
clear()
{ this->_M_tree.clear(); }

template<typename _Tp>
inline std::size_t
tree_array<_Tp, tree_array_mode::mpir>::
size() const
{ return this->_M_tree.size(); }

template<typename _Tp>
inline void
tree_array<_Tp, tree_array_mode::mpir>::
resize(size_type __s)
{ this->_M_tree.resize(__s); }

template<typename _Tp>
const _Tp&
tree_array<_Tp, tree_array_mode::mpir>::
at(size_type __pos) const
{ return this->_M_tree.at(__pos); }

template<typename _Tp>
const _Tp&
tree_array<_Tp, tree_array_mode::mpir>::
operator[] (size_type __pos) const
{ return this->_M_tree[__pos]; }

template<typename _Tp>
void
tree_array<_Tp, tree_array_mode::mpir>::
modify(size_type __x, const value_type& __k)
{
    for (size_type __i{__x}; __i < this->size(); __i += _S_lowbit(__i))
        this->_M_tree[__i] += __k;
}

template<typename _Tp>
inline _Tp
tree_array<_Tp, tree_array_mode::mpir>::
inquire(size_type __x, size_type __y)
{ return this->_M_prefix(__y) - this->_M_prefix(__x); }

template<typename _Tp>
_Tp
tree_array<_Tp, tree_array_mode::mpir>::
_M_prefix(size_type __x)
{
    value_type __res{};
    size_type __i{__x - 1};
    size_type __j{__x};

    while (__i < __j)
    {
        __res += this->_M_tree[__i];
        __j = __i;
        __i -= _S_lowbit(__i);
    }

    return __res;
}

template<typename _Tp>
template<typename _Seq>
tree_array<_Tp, tree_array_mode::mrip>::
tree_array(const _Seq& __data)
{ this->init(__data); }

template<typename _Tp>
template<typename _Seq>
void
tree_array<_Tp, tree_array_mode::mrip>::
init(const _Seq& __data)
{
    this->clear();
    this->resize(__data.size());

    for (size_type __i{}; __i < __data.size(); ++__i)
        this->modify(__i, __i + 1, __data[__i]);
}

template<typename _Tp>
inline bool
tree_array<_Tp, tree_array_mode::mrip>::
empty() const
{ return this->_M_delta.empty(); }

template<typename _Tp>
inline void
tree_array<_Tp, tree_array_mode::mrip>::
clear()
{ this->_M_delta.clear(); }

template<typename _Tp>
inline std::size_t
tree_array<_Tp, tree_array_mode::mrip>::
size() const
{ return this->_M_delta.size(); }

template<typename _Tp>
inline void
tree_array<_Tp, tree_array_mode::mrip>::
resize(size_type __s)
{ this->_M_delta.resize(__s); }

template<typename _Tp>
const _Tp&
tree_array<_Tp, tree_array_mode::mrip>::
at(size_type __pos) const
{ return this->_M_delta.at(__pos); }

template<typename _Tp>
const _Tp&
tree_array<_Tp, tree_array_mode::mrip>::
operator[] (size_type __pos) const
{ return this->_M_delta[__pos]; }

template<typename _Tp>
void
tree_array<_Tp, tree_array_mode::mrip>::
modify(size_type __x, size_type __y, const value_type& __k)
{
    for (size_type __i{__x}; __i < this->size(); __i += _S_lowbit(__i))
        this->_M_delta[__i] += __k;
    for (size_type __i{__y}; __i < this->size(); __i += _S_lowbit(__i))
        this->_M_delta[__i] -= __k;
}

template<typename _Tp>
_Tp
tree_array<_Tp, tree_array_mode::mrip>::
inquire(size_type __x)
{
    value_type __res{};
    size_type __i{__x};
    size_type __j{__x + 1};

    while (__i < __j)
    {
        __res += this->_M_delta[__i];
        __j = __i;
        __i -= _S_lowbit(__i);
    }

    return __res;
}

}

#endif /* _POL_TREEARR_TCC */
