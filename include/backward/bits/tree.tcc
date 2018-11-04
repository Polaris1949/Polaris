// Tree -*- C++ -*-

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

/** @file        bits/tree.tcc
 *  @headerfile  tree
 *  @brief       Tree implementation
 *  @author      Polaris Zhao
 *  @version     3.0
 *
 *  This is an internal header file, included by other library headers.
 *  Do not attempt to use it directly.
**/

#ifndef _POL_TREE_TCC
#define _POL_TREE_TCC 1

namespace polaris
{

tree_node_base::
tree_node_base()
    : _M_parent{(POL_DBG_VAR("Ctor: Init parent"), nullptr)},
        _M_child{(POL_DBG_VAR("Ctor: Init child"), nullptr)},
        _M_left{(POL_DBG_VAR("Ctor: Init left"), this)},
        _M_right{(POL_DBG_VAR("Ctor: Init right"), this)},
        _M_layer{(POL_DBG_VAR("Ctor: Init layer"),
            std::move(this->_M_init_layer()))}
{ POL_DBG_FUN("Ctor") }

tree_node_base::
tree_node_base(base_ptr __node, relation::parent_t)
    : base_type{}
{ POL_DBG_FUN("Ctor") this->link_parent(__node); }

tree_node_base::
tree_node_base(base_ptr __node, relation::child_t)
    : base_type{}
{ POL_DBG_FUN("Ctor") this->link_child(__node); }

tree_node_base::
tree_node_base(base_ptr __node, relation::left_t)
    : base_type{}
{ POL_DBG_FUN("Ctor") this->link_left(__node); }

tree_node_base::
tree_node_base(base_ptr __node, relation::right_t)
    : base_type{}
{ POL_DBG_FUN("Ctor") this->link_right(__node); }

tree_node_base::
~tree_node_base() noexcept
{
    POL_DBG_FUN("Dtor")
    base_observer_ptr __iter{this->_M_right};

    while (__iter.get() != this)
    {
        base_shared_ptr __tmp{__iter.get()};
        __iter = __iter->_M_right;
    }
}

typename tree_node_base::base_ptr
tree_node_base::
ptr()
{
    POL_DBG_FUN("Get default pointer")
    return std::move(base_ptr{this});
}

typename tree_node_base::const_base_ptr
tree_node_base::
cptr() const
{
    POL_DBG_FUN("Get const default pointer")
    return std::move(const_base_ptr{this});
}

unique_ptr<tree_node_base>
tree_node_base::
ptr_unique()
{
    POL_DBG_FUN("Get unique pointer")
    return std::move(base_unique_ptr{this});
}

unique_ptr<const tree_node_base>
tree_node_base::
cptr_unique() const
{
    POL_DBG_FUN("Get const unique pointer")
    return std::move(const_base_unique_ptr{this});
}

shared_ptr<tree_node_base>
tree_node_base::
ptr_shared()
{
    POL_DBG_FUN("Get shared pointer")
    return std::move(base_shared_ptr{this});
}

shared_ptr<const tree_node_base>
tree_node_base::
cptr_shared() const
{
    POL_DBG_FUN("Get const shared pointer")
    return std::move(const_base_shared_ptr{this});
}

weak_ptr<tree_node_base>
tree_node_base::
ptr_weak()
{
    POL_DBG_FUN("Get weak pointer")
    return std::move(base_weak_ptr{this->ptr_shared()});
}

weak_ptr<const tree_node_base>
tree_node_base::
cptr_weak() const
{
    POL_DBG_FUN("Get const weak pointer")
    return std::move(const_base_weak_ptr{this->cptr_shared()});
}

observer_ptr<tree_node_base>
tree_node_base::
ptr_observer()
{
    POL_DBG_FUN("Get observer pointer")
    return std::move(base_observer_ptr{this});
}

observer_ptr<const tree_node_base>
tree_node_base::
cptr_observer() const
{
    POL_DBG_FUN("Get const observer pointer")
    return std::move(const_base_observer_ptr{this});
}

typename tree_node_base::base_ptr
tree_node_base::
parent() const
{
    POL_DBG_FUN("Get parent pointer")
    return this->_M_parent;
}

typename tree_node_base::base_ptr
tree_node_base::
child(size_type __pos) const
{
    POL_DBG_FUN(std::string("Get child pointer (") + std::to_string(__pos)
        + ')')
    base_observer_ptr __it{this->_M_child.get()};
    while (__pos--) //++__it;
        __it = __it->_M_right;
    return __it;
}

typename tree_node_base::base_ptr
tree_node_base::
left() const
{
    POL_DBG_FUN("Get left pointer")
    return this->_M_left;
}

typename tree_node_base::base_ptr
tree_node_base::
right() const
{
    POL_DBG_FUN("Get right pointer")
    return this->_M_right;
}

typename tree_node_base::base_ptr
tree_node_base::
root()
{
    POL_DBG_FUN("Get root pointer")
    base_ptr __iter{this};
    while (__iter->_M_parent)
        __iter = __iter->_M_parent;
    return std::move(__iter);
}

bool
tree_node_base::
is_root() const
{
    POL_DBG_FUN("Check whether root")
    return this->_M_parent == nullptr;
}

bool
tree_node_base::
is_leaf() const
{
    POL_DBG_FUN("Check whether leaf")
    return this->_M_child == nullptr;
}

bool
tree_node_base::
is_unique() const
{
    POL_DBG_FUN("Check whether unique")
    return this->_M_left == this->_M_right;
}

typename tree_node_base::base_ptr
tree_node_base::
link(base_ptr __node, relation::parent_t)
{
    POL_DBG_FUN("Link parent by overloading")
    return std::move(this->link_parent(__node));
}

typename tree_node_base::base_ptr
tree_node_base::
link(base_ptr __node, relation::child_t)
{
    POL_DBG_FUN("Link child by overloading")
    return std::move(this->link_child(__node));
}

typename tree_node_base::base_ptr
tree_node_base::
link(base_ptr __node, relation::left_t)
{
    POL_DBG_FUN("Link left by overloading")
    return std::move(this->link_left(__node));
}

typename tree_node_base::base_ptr
tree_node_base::
link(base_ptr __node, relation::right_t)
{
    POL_DBG_FUN("Link right by overloading")
    return std::move(this->link_right(__node));
}

typename tree_node_base::base_ptr
tree_node_base::
link_parent(base_ptr __node)
{
    POL_DBG_FUN("Link parent")
    if (this->_M_parent)
    {
        base_ptr __tmp{this->_M_parent};
        this->_M_parent->push_child(std::move(__node->root()));
        this->_M_parent = __node;
        return std::move(__tmp);
    }

    this->_M_parent = __node;
    return nullptr;
}

typename tree_node_base::base_ptr
tree_node_base::
link_child(base_ptr __node)
{
    POL_DBG_FUN("Link child")
    // TODO: Any other situation & Redesign
    return std::move(this->push_child(__node));
}

typename tree_node_base::base_ptr
tree_node_base::
link_left(base_ptr __node)
{
    POL_DBG_FUN("Link left")
    // TODO: Any other situation
    base_ptr __tmp{this->_M_left};
    this->_M_left->_M_right = __node;
    this->_M_left = __node;
    return std::move(__tmp);
}

typename tree_node_base::base_ptr
tree_node_base::
link_right(base_ptr __node)
{
    POL_DBG_FUN("Link right")
    // TODO: Any other situation
    base_ptr __tmp{this->_M_right};
    this->_M_right->_M_left = __node;
    this->_M_right = __node;
    return std::move(__tmp);
}

typename tree_node_base::base_ptr
tree_node_base::
cut(relation::parent_t)
{
    POL_DBG_FUN("Cut parent by overloading")
    return std::move(this->cut_parent());
}

typename tree_node_base::base_ptr
tree_node_base::
cut(relation::child_t)
{
    POL_DBG_FUN("Cut child by overloading")
    return std::move(this->cut_child());
}

typename tree_node_base::base_ptr
tree_node_base::
cut(relation::left_t)
{
    POL_DBG_FUN("Cut left by overloading")
    return std::move(this->cut_left());
}

typename tree_node_base::base_ptr
tree_node_base::
cut(relation::right_t)
{
    POL_DBG_FUN("Cut right by overloading")
    return std::move(this->cut_right());
}

typename tree_node_base::base_ptr
tree_node_base::
cut_parent()
{
    POL_DBG_FUN("Cut parent")
    // TODO: Implement
    base_ptr __tmp{this->_M_parent};
    return std::move(__tmp);
}

typename tree_node_base::base_ptr
tree_node_base::
cut_child()
{
    POL_DBG_FUN("Cut child")
    // TODO: Implement
    base_ptr __tmp{this->_M_child.get()};
    return std::move(__tmp);
}

typename tree_node_base::base_ptr
tree_node_base::
cut_left()
{
    POL_DBG_FUN("Cut left")
    base_ptr __tmp{this->_M_left};
    this->_M_left->_M_left->_M_right = this->ptr();
    this->_M_left = this->_M_left->_M_left;
    __tmp->_M_left = __tmp->_M_right = __tmp;
    return std::move(__tmp);
}

typename tree_node_base::base_ptr
tree_node_base::
cut_right()
{
    POL_DBG_FUN("Cut right")
    base_ptr __tmp{this->_M_right};
    this->_M_right->_M_right->_M_left = this->ptr();
    this->_M_right = this->_M_right->_M_right;
    __tmp->_M_left = __tmp->_M_right = __tmp;
    return std::move(__tmp);
}

typename tree_node_base::base_ptr
tree_node_base::
push_child(base_ptr __c)
{
    POL_DBG_FUN("Push child")
    return std::move(this->_M_child->link_left(__c));
}

typename tree_node_base::base_ptr
tree_node_base::
pop_child()
{
    POL_DBG_FUN("Pop child")
    return std::move(this->_M_child->cut_left());
}

shared_ptr<tree_layer>
tree_node_base::
layer() const
{
    POL_DBG_FUN("Get layer pointer")
    return this->_M_layer;
}

shared_ptr<tree_layer>
tree_node_base::
_M_init_layer()
{
    POL_DBG_FUN("Init layer")
    return std::move(layer_ptr{new layer_type{this->ptr()}});
}

template<typename _Tp>
tree_node<_Tp>::
tree_node()
    : base_type{(POL_DBG_VAR("Ctor: Init base"), nullptr)},
        _M_data{(POL_DBG_VAR("Ctor: Init data"), std::move(_Tp{}))}
{ POL_DBG_FUN("Ctor") }

template<typename _Tp>
tree_node<_Tp>::
~tree_node() noexcept
{ POL_DBG_FUN("Dtor") }

tree_layer::
tree_layer()
    : _M_node{(POL_DBG_VAR("Ctor: Init node"), nullptr)},
        _M_depth{(POL_DBG_VAR("Ctor: Init depth"), 0)},
        _M_width{(POL_DBG_VAR("Ctor: Init width"), 0)}
{ POL_DBG_FUN("Ctor") }

tree_layer::
tree_layer(base_ptr __node)
    : _M_node{(POL_DBG_VAR("Ctor(base_ptr): Init node"), __node)},
        _M_depth{(POL_DBG_VAR("Ctor(base_ptr): Init depth"), 1)},
        _M_width{(POL_DBG_VAR("Ctor(base_ptr): Init width"), 1)}
{
    POL_DBG_FUN("Ctor(base_ptr)")
    if (__node->parent())
        this->_M_depth = __node->parent()->layer()->_M_depth + 1;

    if (__node->right() != __node)
    {
        base_ptr __iter = __node->right();

        while (__iter != __node)
        {
            ++this->_M_width;
            __iter = __iter->right();
        }
    }
}

tree_layer::
~tree_layer() noexcept
{ POL_DBG_FUN("Dtor") }

typename tree_layer::base_ptr
tree_layer::
node() const
{
    POL_DBG_FUN("Get node pointer")
    return this->_M_node;
}

size_t
tree_layer::
depth() const
{
    POL_DBG_FUN("Get depth")
    return this->_M_depth;
}

size_t
tree_layer::
width() const
{
    POL_DBG_FUN("Get width")
    return this->_M_width;
}

template<typename _Tp>
tree_iterator<_Tp>::
tree_iterator()
    : _M_ptr{(POL_DBG_VAR("Ctor: Init ptr"), nullptr)}
{ POL_DBG_FUN("Ctor") }

template<typename _Tp>
tree_iterator<_Tp>::
~tree_iterator() noexcept
{ POL_DBG_FUN("Dtor") }

template<typename _Tp>
tree<_Tp>::
tree()
    : _M_root{(POL_DBG_VAR("Ctor: Init root"), nullptr)}
{ POL_DBG_FUN("Ctor") }

template<typename _Tp>
tree<_Tp>::
~tree() noexcept
{ POL_DBG_FUN("Dtor") }

template<typename _Tp>
typename tree<_Tp>::node_ptr
tree<_Tp>::
root() const
{
    POL_DBG_FUN("Get root pointer")
    return this->_M_root;
}

template<typename _Tp>
bool
tree<_Tp>::
is_forest() const
{
    return !this->_M_root->is_unique();
}

}

#endif
