#ifndef _POL_TREE_H
#define _POL_TREE_H 1

#include <list>
#include <stack>

namespace pol
{

class tree_node_base
{
public:
    using base_type = tree_node_base;
    using size_type = std::size_t;
    using child_iterator = std::list<base_type*>::iterator;
    using child_const_iterator = std::list<base_type*>::const_iterator;

    tree_node_base();

    base_type* parent() const;
    base_type* child(size_type __n) const;

    bool empty() const;
    base_type* front() const;
    base_type* back() const;

    void push_back(base_type* __p);
    void push_front(base_type* __p);

    base_type* next_child(base_type* __p) const;
    base_type* prev_child(base_type* __p) const;

    child_iterator begin();
    child_iterator end();
    child_const_iterator cbegin() const;
    child_const_iterator cend() const;

protected:
    base_type* _M_parent;
    std::list<base_type*> _M_child;
};

template<typename _Tp>
class tree_node : public tree_node_base
{
public:
    using value_type = _Tp;
    using base_type = tree_node_base;
    using node_type = tree_node<_Tp>;
    using size_type = std::size_t;

    tree_node() = default;
    tree_node(const value_type& __x);

    void data(const value_type& __x);
    value_type data() const;

    bool empty() const;
    node_type* front() const;
    node_type* back() const;

    void push_back(node_type* __p);
    void push_front(node_type* __p);

    void emplace_back();
    void emplace_back(const value_type& __x);

    node_type* parent() const;
    node_type* child(size_type __n) const;

    node_type* operator[] (size_type __n) const;

private:
    friend class tree<_Tp>;

    void _M_construct(std::string_view __s);
    void _M_destroy() noexcept;

    value_type _M_data;
};

class tree_base_iterator
{
public:
    using base_type = tree_node_base;
    using base_iterator = tree_base_iterator;

    tree_base_iterator();

    base_iterator& operator++ ();
    base_iterator& operator-- ();

protected:
    tree_base_iterator(base_type* __root, bool __t);
    friend bool operator == (const tree_base_iterator& __lhs,
        const tree_base_iterator& __rhs);
    friend bool operator != (const tree_base_iterator& __lhs,
        const tree_base_iterator& __rhs);

    base_type* _M_root;
    // TODO: Replace this with std::list<base_type*>::iterator
    std::stack<base_type*> _M_st;
};

template<typename _Tp>
class tree_iterator : public tree_base_iterator
{
public:
    using value_type = _Tp;
    using base_type = tree_node_base;
    using base_iterator = tree_base_iterator;
    using node_type = tree_node<_Tp>;
    using node_iterator = tree_iterator<_Tp>;

    tree_iterator() = default;

    node_iterator& operator++ ();
    node_iterator& operator-- ();
    value_type& operator* ();
    value_type operator* () const;
    value_type* operator-> () const;
    base_type* base_ptr() const;
    node_type* node_ptr() const;

private:
    friend class tree<_Tp>;

    tree_iterator(node_type* __root, bool __t);
};

template<typename _Tp>
class tree
{
public:
    using value_type = _Tp;
    using base_type = tree_node_base;
    using base_iterator = tree_base_iterator;
    using node_type = tree_node<_Tp>;
    using node_iterator = tree_iterator<_Tp>;
    using size_type = std::size_t;

    tree();
    tree(std::string_view __s);
    ~tree() noexcept;

    void emplace();
    void emplace(const value_type& __x);

    void clear() noexcept;

    node_type* root() const;

    node_iterator begin();
    node_iterator end();

private:
    node_type* _M_root;
};

}

#endif /* _POL_TREE_H */
