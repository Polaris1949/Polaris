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

/** @file        bits/tree.h
 *  @headerfile  tree
 *  @brief       Tree classes
 *  @author      Polaris Zhao
 *  @version     3.0
 *
 *  This is an internal header file, included by other library headers.
 *  Do not attempt to use it directly.
**/

#ifndef _POL_TREE_H
#define _POL_TREE_H 1

namespace polaris
{

/** @class  tree_node_base
 *  @brief  Tree node base class
**/
class tree_node_base
#if POL_DEBUG
    : public debug_helper
#endif
{
public:
    using size_type = size_t; ///< Size type
    using difference_type = ptrdiff_t;
    using self_type = tree_node_base;
    using pointer = self_type*;
    using const_pointer = const self_type*;
    using reference = self_type&;
    using const_reference = const self_type&;

    /** @brief    Default node pointer type
     *  @note     You could change it to @c shared_ptr, @c weak_ptr or @c
     *            observer_ptr.
     *  @warning  Do @b NOT change it to @c unique_ptr.
    **/
    template<typename _Tp>
    using default_node_ptr = observer_ptr<_Tp>;

    using base_type = tree_node_base;     ///< Node base type
    using const_base_type = const base_type; ///< Const node base type
    using base_ptr = default_node_ptr<base_type>; // Default node base pointer
    using const_base_ptr = default_node_ptr<const_base_type>;
    using base_unique_ptr = unique_ptr<base_type>;
    using const_base_unique_ptr = unique_ptr<const_base_type>;
    using base_shared_ptr = shared_ptr<base_type>;
    using const_base_shared_ptr = shared_ptr<const_base_type>;
    using base_weak_ptr = weak_ptr<base_type>;
    using const_base_weak_ptr = weak_ptr<const_base_type>;
    using base_observer_ptr = observer_ptr<base_type>;
    using const_base_observer_ptr = observer_ptr<const_base_type>;

    template<typename _Tp>
    using node_type = tree_node<_Tp>;
    template<typename _Tp>
    using const_node_type = const node_type<_Tp>;
    template<typename _Tp>
    using node_ptr = default_node_ptr<node_type<_Tp>>;
    template<typename _Tp>
    using const_node_ptr = default_node_ptr<const_node_type<_Tp>>;
    template<typename _Tp>
    using node_unique_ptr = unique_ptr<node_type<_Tp>>;
    template<typename _Tp>
    using const_node_unique_ptr = unique_ptr<const_node_type<_Tp>>;
    template<typename _Tp>
    using node_shared_ptr = shared_ptr<node_type<_Tp>>;
    template<typename _Tp>
    using const_node_shared_ptr = shared_ptr<const_node_type<_Tp>>;
    template<typename _Tp>
    using node_weak_ptr = weak_ptr<node_type<_Tp>>;
    template<typename _Tp>
    using const_node_weak_ptr = weak_ptr<const_node_type<_Tp>>;
    template<typename _Tp>
    using node_observer_ptr = observer_ptr<node_type<_Tp>>;
    template<typename _Tp>
    using const_node_observer_ptr = observer_ptr<const_node_type<_Tp>>;

    template<typename _Tp>
    using default_layer_ptr = shared_ptr<_Tp>;

    using layer_type = tree_layer;
    using const_layer_type = const layer_type;
    using layer_ptr = default_layer_ptr<layer_type>;
    using const_layer_ptr = default_layer_ptr<const_layer_type>;

    /** @brief  Tree node relation **/
    struct relation
    {
        /** @brief  Type of a parent relation **/
        struct parent_t {};
        static constexpr parent_t parent{}; ///< A parent relation

        /** @brief  Type of a child relation **/
        struct child_t {};
        static constexpr child_t child{}; ///< A child relation

        /** @brief  Type of a left relation **/
        struct left_t {};
        static constexpr left_t left{}; ///< A left relation

        /** @brief  Type of a right relation **/
        struct right_t {};
        static constexpr right_t right{}; ///< A right relation
    };

protected:
    base_observer_ptr _M_parent;
    base_shared_ptr _M_child;
    base_observer_ptr _M_left;
    base_observer_ptr _M_right;
    layer_ptr _M_layer;

public:
    /** @brief  Construct an empty @c tree_node_base
     *  @note   It would create a layer by default.
     *  @todo   Test.
    **/
    tree_node_base();

    /** @brief    Construct a @c tree_node_base linked to a parent one
     *  @warning  Unimplemented yet.
     *  @todo     Implement & Test.
    **/
    tree_node_base(base_ptr __node, relation::parent_t);

    /** @brief    Construct a @c tree_node_base linked to a child one
     *  @warning  Unimplemented yet.
     *  @todo     Implement & Test.
    **/
    tree_node_base(base_ptr __node, relation::child_t);

    /** @brief    Construct a @c tree_node_base linked to a left one
     *  @warning  Unimplemented yet.
     *  @todo     Implement & Test.
    **/
    tree_node_base(base_ptr __node, relation::left_t);

    /** @brief    Construct a @c tree_node_base linked to a right one
     *  @warning  Unimplemented yet.
     *  @todo     Implement & Test.
    **/
    tree_node_base(base_ptr __node, relation::right_t);

    /** @brief    Destroy a @c tree_node_base
     *  @warning  Untested yet.
     *  @todo     Test.
    **/
    ~tree_node_base() noexcept;

    /** @brief  Get a default pointer to @c this
     *  @todo   Test.
    **/
    base_ptr
    ptr();

    /** @brief  Get a const default pointer to @c this
     *  @todo   Test.
    **/
    const_base_ptr
    cptr() const;

    /** @brief    Get an unique pointer to @c this
     *  @warning  It could only be used in limited situations.
     *  @todo     Test.
    **/
    base_unique_ptr
    ptr_unique();

    /** @brief    Get a const unique pointer to @c this
     *  @warning  It could only be used in limited situations.
     *  @todo     Test.
    **/
    const_base_unique_ptr
    cptr_unique() const;

    /** @brief    Get a shared pointer to @c this
     *  @todo     Test.
    **/
    base_shared_ptr
    ptr_shared();

    /** @brief    Get a const shared pointer to @c this
     *  @todo     Test.
    **/
    const_base_shared_ptr
    cptr_shared() const;

    /** @brief    Get a weak pointer to @c this
     *  @todo     Test.
    **/
    base_weak_ptr
    ptr_weak();

    /** @brief    Get a const weak pointer to @c this
     *  @todo     Test.
    **/
    const_base_weak_ptr
    cptr_weak() const;

    /** @brief    Get an observer pointer to @c this
     *  @todo     Test.
    **/
    base_observer_ptr
    ptr_observer();

    /** @brief    Get a const observer pointer to @c this
     *  @todo     Test.
    **/
    const_base_observer_ptr
    cptr_observer() const;

    /** @brief    Get a parent pointer
     *  @return  A pointer referring to father.
     *  @todo     Test.
    **/
    base_ptr
    parent() const;

    /** @brief    Get a child pointer
     *  @param  __pos  Index of a child.
     *  @return  A pointer referring to child.
     *  @todo     Test.
    **/
    base_ptr
    child(size_type __pos = 0) const;

    /** @brief    Get a left pointer
     *  @return  A pointer referring to left.
     *  @todo     Test.
    **/
    base_ptr
    left() const;

    /** @brief    Get a right pointer
     *  @return  A pointer referring to right.
     *  @todo     Test.
    **/
    base_ptr
    right() const;

    /** @brief    Get a root pointer
     *  @return  A pointer referring to root.
     *  @todo     Test. Add @c const?
    **/
    base_ptr
    root();

    /** @brief  Check whether a root
     *  @return  A @c bool result.
    **/
    bool
    is_root() const;

    /** @brief  Check whether a leaf
     *  @return  A @c bool result.
    **/
    bool
    is_leaf() const;

    /** @brief  Check whether unique
     *  @return  A @c bool result.
    **/
    bool
    is_unique() const;

    base_ptr
    link(base_ptr __node, relation::parent_t);

    base_ptr
    link(base_ptr __node, relation::child_t);

    base_ptr
    link(base_ptr __node, relation::left_t);

    base_ptr
    link(base_ptr __node, relation::right_t);

    base_ptr
    link_parent(base_ptr __p);

    base_ptr
    link_child(base_ptr __c);

    base_ptr
    link_left(base_ptr __l);

    base_ptr
    link_right(base_ptr __r);

    base_ptr
    cut(relation::parent_t);

    base_ptr
    cut(relation::child_t);

    base_ptr
    cut(relation::left_t);

    base_ptr
    cut(relation::right_t);

    base_ptr
    cut_parent();

    base_ptr
    cut_child();

    base_ptr
    cut_left();

    base_ptr
    cut_right();

    base_ptr
    push_child(base_ptr __c);

    base_ptr
    pop_child();

    /** @brief   Get layer pointer
     *  @return  A pointer.
    **/
    layer_ptr
    layer() const;

protected:
    layer_ptr
    _M_init_layer();
};

template<typename _Tp>
class tree_node : public tree_node_base
{
public:
    typedef _Tp             value_type;
    typedef size_t          size_type;
    typedef tree_node_base  base_type;
    typedef tree_node<_Tp>  node_type;
    typedef observer_ptr<node_type> node_ptr;

protected:
    value_type _M_data;

public:
    tree_node();

    explicit
    tree_node(const value_type& __x);

    tree_node(const base_type& __base, const value_type& __x);

    ~tree_node() noexcept;

    node_ptr
    parent() const;

    node_ptr
    child(size_type __pos = 0) const;

    node_ptr
    left() const;

    node_ptr
    right() const;

    value_type&
    data();

    const value_type&
    data() const;
};

class tree_layer
#if POL_DEBUG
    : public debug_helper
#endif
{
public:
    typedef tree_node_base base_type;
    typedef observer_ptr<base_type> base_ptr;
    typedef weak_ptr<base_type> base_weak_ptr;
    typedef observer_ptr<base_type> base_observer_ptr;
    typedef tree_layer layer_type;
    typedef shared_ptr<layer_type> layer_ptr;
    typedef size_t size_type;

protected:
    base_observer_ptr _M_node;
    size_type _M_depth;
    size_type _M_width;

public:
    tree_layer();

    explicit
    tree_layer(base_ptr __node);

    ~tree_layer() noexcept;

    base_ptr
    node() const;

    size_type
    depth() const;

    size_type
    width() const;
};

template<typename _Tp>
class tree_iterator
#if POL_DEBUG
    : public debug_helper
#endif
{
public:
    typedef _Tp value_type;
    typedef size_t size_type;
    typedef tree_node<_Tp> node_type;
    typedef observer_ptr<node_type> node_ptr;
    typedef tree_iterator<_Tp> iterator;

private:
    node_ptr _M_ptr;
    node_ptr _M_child;
    size_type _M_cur;

public:
    tree_iterator();

    ~tree_iterator() noexcept;

    iterator&
    operator++ ();

    iterator
    operator++ (int);

    iterator&
    operator-- ();

    iterator
    operator-- (int);

    value_type&
    operator* ();

    const value_type&
    operator* () const;

    node_type*&
    operator-> ();

    const node_type*&
    operator-> () const;
};

template<typename _Tp>
class tree
#if POL_DEBUG
    : public debug_helper
#endif
{
public:
    typedef _Tp value_type;
    typedef tree_node<_Tp> node_type;
    typedef std::shared_ptr<node_type> node_ptr;

private:
    node_ptr _M_root;

public:
    tree();

    tree(node_ptr __root);

    ~tree() noexcept;

    node_ptr root() const;

    bool is_forest() const;
};

}

#endif /* _POL_TREE_H */
