#include <algorithm>
#include <vector>
#include <stack>
#include <iostream>
// #include <polaris/binary_tree>

namespace polaris
{

template<typename _Tp>
class binary_tree_node
{
public:
	typedef _Tp                    value_type;
	typedef binary_tree_node<_Tp>  node_type;
	typedef std::size_t            size_type;

protected:
	node_type* _M_parent;
	node_type* _M_left;
	node_type* _M_right;
	value_type _M_data;

public:
	binary_tree_node();

	binary_tree_node(const value_type& __x);

	~binary_tree_node() noexcept;

	node_type&
	construct(const value_type& __x);

	node_type&
	destroy();

	node_type*&
	parent();

	const node_type*&
	parent() const;

	node_type*&
	child(bool __x);

	const node_type*&
	child(bool __x) const;

	node_type*&
	left();

	const node_type*&
	left() const;

	node_type*&
	right();

	const node_type*&
	right() const;

	value_type&
	data();

	const value_type&
	data() const;

	bool
	is_branch() const;

	bool
	is_leaf() const;

	size_type
	degree() const;

	size_type
	depth() const;

private:
	void
	_M_construct(const value_type& __x);

	void
	_M_destroy();
};

template<typename _Tp>
binary_tree_node<_Tp>::
binary_tree_node()
	: _M_parent{nullptr}, _M_left{nullptr}, _M_right{nullptr}, _M_data{}
{}

template<typename _Tp>
binary_tree_node<_Tp>::
binary_tree_node(const value_type& __x)
	: _M_parent{nullptr}, _M_left{nullptr}, _M_right{nullptr}, _M_data{__x}
{}

template<typename _Tp>
binary_tree_node<_Tp>::
~binary_tree_node() noexcept
{}

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
parent()
{ return this->_M_parent; }

template<typename _Tp>
inline const binary_tree_node<_Tp>*&
binary_tree_node<_Tp>::
parent() const
{ return this->_M_parent; }

template<typename _Tp>
inline binary_tree_node<_Tp>*&
binary_tree_node<_Tp>::
child(bool __x)
{ return __x ? this->right() : this->left(); }

template<typename _Tp>
inline const binary_tree_node<_Tp>*&
binary_tree_node<_Tp>::
child(bool __x) const
{ return __x ? this->right() : this->left(); }

template<typename _Tp>
inline binary_tree_node<_Tp>*&
binary_tree_node<_Tp>::
left()
{ return this->_M_left; }

template<typename _Tp>
inline const binary_tree_node<_Tp>*&
binary_tree_node<_Tp>::
left() const
{ return this->_M_left; }

template<typename _Tp>
inline binary_tree_node<_Tp>*&
binary_tree_node<_Tp>::
right()
{ return this->_M_right; }

template<typename _Tp>
inline const binary_tree_node<_Tp>*&
binary_tree_node<_Tp>::
right() const
{ return this->_M_right; }

template<typename _Tp>
inline _Tp&
binary_tree_node<_Tp>::
data()
{ return this->_M_data; }

template<typename _Tp>
inline const _Tp&
binary_tree_node<_Tp>::
data() const
{ return this->_M_data; }

template<typename _Tp>
inline bool
binary_tree_node<_Tp>::
is_branch() const
{ return this->degree() > 0; }

template<typename _Tp>
inline bool
binary_tree_node<_Tp>::
is_leaf() const
{ return this->degree() == 0; }

template<typename _Tp>
inline std::size_t
binary_tree_node<_Tp>::
degree() const
{
	return size_type{this->_M_left != nullptr}
		+ size_type{this->_M_right != nullptr};
}

template<typename _Tp>
void
binary_tree_node<_Tp>::
_M_construct(const value_type& __x)
{
	new (&this->data()) value_type{__x};
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

	this->data().~value_type();
}

template<typename _Tp>
class link_cut_tree_node
    : public binary_tree_node<_Tp>
{
public:
    using base_type = binary_tree_node<_Tp>;
    using value_type = _Tp;
    using node_type = link_cut_tree_node<_Tp>;

protected:
    value_type _M_value;
    bool _M_mark;

public:
    link_cut_tree_node() = default;

    link_cut_tree_node(const value_type& __x)
        : base_type{__x}, _M_value{__x}, _M_mark{false}
    {}

    ~link_cut_tree_node() noexcept { }

    value_type& value()
    { return this->_M_value; }

    const value_type& value() const
    { return this->_M_value; }

    bool& mark()
    { return this->_M_mark; }

    const bool& mark() const
    { return this->_M_mark; }

    void reverse()
    {
        std::swap(this->left(), this->right());
        this->mark() ^= true;
    }
};

template<typename _Tp>
class link_cut_tree
{
public:
    using value_type = _Tp;
    using node_base = binary_tree_node<_Tp>;
    using node_type = link_cut_tree_node<_Tp>;
    using tree_type = link_cut_tree<_Tp>;
    using size_type = std::size_t;

private:
    std::vector<node_type*> _M_node;

    void push_up(node_type* __x)
    {
        value_type __ld{};
        value_type __rd{};

        if (__x->left()) __ld = __x->left()->data();
        if (__x->right()) __rd = __x->right()->data();

        __x->data() = __ld ^ __rd ^ __x->value();
    }

    void push_down(node_type* __x)
    {
        if (__x->mark())
        {
            __x->mark() = false;
            node_type* __l{static_cast<node_type*>(__x->left())};
            node_type* __r{static_cast<node_type*>(__x->right())};

            if (__l) __l->reverse();
            if (__r) __r->reverse();
        }
    }

    inline bool is_root(node_type* __x)
    {
        node_base* __p{__x->parent()};
        if (__p == nullptr) return true;
        return __p->left() != __x && __p->right() != __x;
    }

    void rotate(node_type* __x)
    {
        node_type* __y{static_cast<node_type*>(__x->parent())};
        node_type* __z{static_cast<node_type*>(__y->parent())};
        bool __l{__y->right() == __x};
        bool __r{__l ^ true};

        if (!this->is_root(__y))
        {
            if (__z->left() == __y) __z->left() = __x;
            else __z->right() = __x;
        }

        __x->parent() = __z;
        __y->parent() = __x;
        if (__x->child(__r)) __x->child(__r)->parent() = __y;
        __y->child(__l) = __x->child(__r);
        __x->child(__r) = __y;

        this->push_up(__y);
        this->push_up(__x);
    }

    void splay(node_type* __x)
    {
        std::stack<node_type*> __st;
        __st.push(__x);

        for (node_type* __i{__x}; !this->is_root(__i);
                __i = static_cast<node_type*>(__i->parent()))
        {
            __st.push(static_cast<node_type*>(__i->parent()));
        }

        while (!__st.empty())
        {
            this->push_down(__st.top());
            __st.pop();
        }

        while (!this->is_root(__x))
        {
            node_type* __y{static_cast<node_type*>(__x->parent())};
            node_type* __z{static_cast<node_type*>(__y->parent())};

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
        node_type* __t{nullptr};

        while (__x)
        {
            this->splay(__x);
            __x->right() = __t;
            this->push_up(__x);
            __t = __x;
            __x = static_cast<node_type*>(__x->parent());
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
        while (__x->left()) __x = static_cast<node_type*>(__x->left());
        return __x;
    }

    inline void split(node_type* __x, node_type* __y)
    {
        this->make_root(__x);
        this->access(__y);
        this->splay(__y);
    }

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

    inline void assign(node_type* __x, const value_type& __y)
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
    link_cut_tree() = default;

    template<typename _Seq>
    link_cut_tree(const _Seq& __data)
    { this->construct(__data); }

    ~link_cut_tree() noexcept
    { this->destroy(); }

    template<typename _Seq>
    tree_type& construct(const _Seq& __data)
    {
        for (const value_type& __elem : __data)
            this->_M_node.push_back(new node_type{__elem});

        return *this;
    }

    tree_type& destroy()
    {
        for (node_type*& __elem : this->_M_node)
            delete __elem;

        return *this;
    }

    inline void cut(size_type __x, size_type __y)
    {
        this->cut(this->_M_node[__x], this->_M_node[__y]);
    }

    inline void link(size_type __x, size_type __y)
    {
        this->link(this->_M_node[__x], this->_M_node[__y]);
    }

    inline void assign(size_type __x, const value_type& __y)
    {
        this->assign(this->_M_node[__x], __y);
    }

    inline value_type xor_sum(size_type __x, size_type __y)
    {
        return this->xor_sum(this->_M_node[__x], this->_M_node[__y]);
    }
};

}

namespace pol = polaris;

pol::link_cut_tree<int> lct;

int main()
{
    int n, m, o, x, y;
    std::cin >> n >> m;

    {
        std::vector<int> v;
        v.resize(n);
        for (int i=0; i<n; ++i)
            std::cin >> v[i];
        lct.construct(v);
    }

    for (int i=0; i<m; ++i)
    {
        std::cin >> o >> x >> y;

        switch (o)
        {
            case 0: std::cout << lct.xor_sum(--x, --y) << '\n'; break;
            case 1: lct.link(--x, --y); break;
            case 2: lct.cut(--x, --y); break;
            case 3: lct.assign(--x, y); break;
        }
    }

    return 0;
}
