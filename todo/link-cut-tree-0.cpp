#include <algorithm>
#include <vector>
#include <stack>
// #include <polaris/binary_tree>

namespace polaris
{

template<typename>
class binary_tree_node;

template<typename _Tp>
class link_cut_tree_node
    : public binary_tree_node<_Tp>
{
public:
    using value_type = _Tp;
    using node_type = link_cut_tree_node<_Tp>;

private:
    value_type _M_value;
    bool _M_mark;

public:
    link_cut_tree_node() = default;
    link_cut_tree_node(const value_type& __x);

    value_type& value();
    const value_type& value() const;

    bool& mark();
    const bool& mark() const;

    void reverse()
    {
        std::swap(this->left(), this->right());
        this->mark() ^= true;
        // this->mark() = !this->mark();
    }
};

template<typename _Tp>
class link_cut_tree
{
public:
    using value_type = _Tp;
    using node_type = link_cut_tree_node<_Tp>;

private:
    std::vector<node_type*> _M_node;
    //int top,c[300005][2],f[300005],q[300005],rv[300005];

    void push_up(node_type* __x)
    {
        // TODO: More modifications
        __x->data() = __x->left()->data() ^ __x->right()->data()
            ^ __x->value();
    }

    void push_down(node_type* __x)
    {
        if (__x->mark())
        {
            __x->mark() = false;
            node_type*& __l{__x->left()};
            node_type*& __r{__x->right()};
            if (__l) __l->reverse();
            if (__r) __r->reverse();
        }
    }

    inline bool is_root(node_type* __x)
    {
        // return __x->is_root();
        node_type*& __p{__x->parent()};
        return __p->left() != __x && __p->right() != __x;
    }

    void rotate(node_type* __x)
    {
        node_type*& __y{__x->parent()};
        node_type*& __z{__y->parent()};
        bool __l{__y->right() == __x};
        bool __r{__l ^ true};

        if (!this->is_root(__y))
        {
            if (__z->left() == __y) __z->left() = __x;
            else __z->right() = __x;
        }

        __x->parent() = __z;
        __y->parent() = __x;
        __x->child(__r)->parent() = __y;
        __y->child(__l) = __x->child(__r);
        __x->child(__r) = __y;

        this->push_up(__y);
        this->push_up(__x);
    }

    void splay(node_type* __x)
    {
        std::stack<node_type*> __st;
        __st.push(__x);

        for (node_type*& __i{__x}; !this->is_root(__i); __i = __i->parent())
            __st.push(__i->parent());

        while (!__st.empty())
        {
            this->push_down(__st.top());
            __st.pop();
        }

        while (!this->is_root(__x))
        {
            node_type*& __y{__x->parent()};
            node_type*& __z{__y->parent()};

            if (!this->is_root(__y))
            {
                if ((__y->left() == __x) ^ (__z->left() == __y))
                    this->rotate(__x);
                else
                    this->rotate(__y);
            }

            this->rotate(__x);
        }
    }

    void access(node_type* __x)
    {
        for (node_type* __t{}; __x; __t = __x, __x = __x->parent())
        {
            this->splay(__x);
            __x->right() = __t;
            this->push_up(__x);
        }
    }

    inline void make_root(node_type* __x)
    {
        this->access(__x);
        this->splay(__x);
        __x->reverse();
    }

    node_type* find(node_type* __x)
    {
        this->access(__x);
        this->splay(__x);
        while (__x->left()) __x = __x->left();
        return __x;
    }

    inline void split(node_type* __x, node_type* __y)
    {
        this->make_root(__x);
        this->access(__y);
        this->splay(__y);
    }

    //int xr[300005],val[300005];
    void cut(node_type* __x, node_type* __y)
    {
        if (this->find(__x) != this->find(__y)) return;
        this->split(__x, __y);
        if (__y->left() == __x && __x->right() == nullptr)
        {
            __y->left() = nullptr;
            __x->parent() = nullptr;
        }
    }

    void link(node_type* __x, node_type* __y)
    {
        if (this->find(__x) != this->find(__y))
        {
            this->make_root(__x);
            __x->parent() = __y;
        }
    }

    inline void modify(node_type* __x, const value_type& __y)
    {
        this->access(__x);
        this->splay(__x);
        __x->value() = __y;
        this->push_up(__x);
    }

    inline value_type xor_sum(node_type* __x, node_type* __y)
    {
        this->split(__x, __y);
        return __y->data();
    }

public:
    void cut(size_type __x, size_type __y);
    void link(size_type __x, size_type __y);
    void modify(size_type __x, const value_type& __y);
    value_type xor_sum(size_type __x, size_type __y);
};

}
