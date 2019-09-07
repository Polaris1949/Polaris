#ifndef _POL_TREE_H
#define _POL_TREE_H 1

#include <list>

namespace polaris
{

class tree_node_base
{
public:
    using base_type = tree_node_base;
    using size_type = std::size_t;

protected:
    base_type* _M_parent;
    std::list<base_type*> _M_child;

public:
    tree_node_base() = default;

    base_type*& parent();
    const base_type*& parent() const;

    base_type*& child(size_type __n);
    const base_type*& child(size_type __n) const;
};

template<typename _Tp>
class tree_node : public tree_node_base
{
public:
    using value_type = _Tp;
    using base_type = tree_node_base;
    using node_type = tree_node<_Tp>;

private:
    value_type _M_data;

public:
    value_type& data();
    const value_type& data() const;
};

}

#endif /* _POL_TREE_H */
