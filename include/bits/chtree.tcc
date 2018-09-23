// Chtholly tree implementation -*- C++ -*-

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

/** @file        bits/chtree.tcc
 *  @headerfile  chtholly_tree
 *  @brief       Chtholly tree implementation
 *  @author      Polaris Zhao
 *  @version     3.0
 *
 *  This is an internal header file, included by other library headers.
 *  Do not attempt to use it directly.
**/

#ifndef _POL_CHTREE_TCC
#define _POL_CHTREE_TCC 1

namespace polaris
{

template<typename _Tp>
chtholly_tree_node<_Tp>::
chtholly_tree_node(size_type __l, size_type __r)
    : _M_left{__l}, _M_right{__r}, _M_data{}
{}

template<typename _Tp>
chtholly_tree_node<_Tp>::
chtholly_tree_node(size_type __l, size_type __r, const value_type& __v)
    : _M_left{__l}, _M_right{__r}, _M_data{__v}
{}

template<typename _Tp>
inline std::size_t
chtholly_tree_node<_Tp>::
left() const
{ return this->_M_left; }

template<typename _Tp>
inline std::size_t
chtholly_tree_node<_Tp>::
right() const
{ return this->_M_right; }

template<typename _Tp>
inline _Tp&
chtholly_tree_node<_Tp>::
data() const
{ return this->_M_data; }

template<typename _Tp>
inline std::size_t
chtholly_tree_node<_Tp>::
length() const
{ return this->right() - this->left(); }

template<typename _Tp>
inline bool
chtholly_tree_node<_Tp>::
operator < (const chtholly_tree_node& __o) const
{ return this->left() < __o.left(); }

template<typename _Tp>
template<typename _Seq>
chtholly_tree<_Tp>::
chtholly_tree(const _Seq& __data)
{ this->init(__data); }

template<typename _Tp>
template<typename _Seq>
void
chtholly_tree<_Tp>::
init(const _Seq& __data)
{
    size_type __n{__data.size()};

    for (size_type __i{}; __i < __n; ++__i)
        this->_M_sto.insert(node_type{__i, __i + 1, __data[__i]});

    this->_M_sto.insert(node_type{__n, __n + 1});
}

template<typename _Tp>
void
chtholly_tree<_Tp>::
plus(size_type __l, size_type __r, const value_type& __v)
{
    iterator __itl{this->_M_split(__l)};
    iterator __itr{this->_M_split(__r)};

    for (; __itl != __itr; ++__itl)
        __itl->data() += __v;
}

template<typename _Tp>
void
chtholly_tree<_Tp>::
assign(size_type __l, size_type __r, const value_type& __v)
{
    iterator __itl{this->_M_split(__l)};
    iterator __itr{this->_M_split(__r)};

    this->_M_sto.erase(__itl, __itr);
    this->_M_sto.insert(node_type{__l, __r, __v});
}

template<typename _Tp>
_Tp
chtholly_tree<_Tp>::
rank(size_type __l, size_type __r, size_type __k)
{
    using _Pair_t = std::pair<value_type, size_type>;
    std::vector<_Pair_t> __tmp;
    iterator __itl{this->_M_split(__l)};
    iterator __itr{this->_M_split(__r)};

    for (; __itl != __itr; ++__itl)
        __tmp.push_back(_Pair_t{__itl->data(), __itl->length()});

    std::sort(__tmp.begin(), __tmp.end());
    size_type __cnt{};
    using _Iter_t = typename std::vector<_Pair_t>::iterator;

    for (_Iter_t __it{__tmp.begin()}; __it != __tmp.end(); ++__it)
    {
        __cnt += __it->second;
        if (__k < __cnt) return __it->first;
    }

    throw std::logic_error{"never reached here"};
}

template<typename _Tp>
_Tp
chtholly_tree<_Tp>::
pow_sum(size_type __l, size_type __r, value_type __exp, value_type __mod)
{
    iterator __itl{this->_M_split(__l)};
    iterator __itr{this->_M_split(__r)};
    value_type __res{};

    for (; __itl != __itr; ++__itl)
        __res = (__res + value_type{__itl->length()}
            * pol::qpow(__itl->data(), __exp, __mod)) % __mod;

    return __res;
}

template<typename _Tp>
typename std::set<chtholly_tree_node<_Tp>>::iterator
chtholly_tree<_Tp>::
_M_split(size_type __pos)
{
    iterator __it{this->_M_sto.lower_bound(node_type{__pos, ~0u})};

    if (__it != _M_sto.end() && __it->left() == __pos)
        return __it;
    --__it;

    size_type __l{__it->left()};
    size_type __r{__it->right()};
    value_type __v{__it->data()};

    this->_M_sto.erase(__it);
    this->_M_sto.insert(node_type{__l, __pos, __v});
    return this->_M_sto.insert(node_type{__pos, __r, __v}).first;
}

}

#endif /* _POL_CHTREE_TCC */
