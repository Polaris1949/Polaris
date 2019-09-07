#ifndef _POL_TREE_TCC
#define _POL_TREE_TCC 1

namespace polaris
{

tree_node_base*&
tree_node_base::
parent()
{ return this->_M_parent; }

const tree_node_base*&
tree_node_base::
parent() const
{ return this->_M_parent; }

tree_node_base*&
tree_node_base::
child(size_type __n) const
{
#if POL_DEBUG
    if (__n >= this->_M_child.size())
        throw std::out_of_range{"tree_node_base::child"};
#endif

    using _Iter = std::list<base_type*>::iterator;
    _Iter __i{this->_M_child.begin()};
    size_type __j{};

    while (__i != this->_M_child.end())
    {
        if (__n == __j) return *__i;
        ++__i; ++__j;
    }

    return nullptr;
}

const tree_node_base*&
tree_node_base::
child(size_type __n) const
{
#if POL_DEBUG
    if (__n >= this->_M_child.size())
        throw std::out_of_range{"tree_node_base::child"};
#endif

    using _Iter = std::list<base_type*>::const_iterator;
    _Iter __i{this->_M_child.cbegin()};
    size_type __j{};

    while (__i != this->_M_child.cend())
    {
        if (__n == __j) return *__i;
        ++__i; ++__j;
    }

    return nullptr;
}

}

#endif /* _POL_TREE_TCC */
