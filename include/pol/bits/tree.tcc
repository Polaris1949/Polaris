#ifndef _POL_TREE_TCC
#define _POL_TREE_TCC 1

#include <pol/utility>

namespace pol
{

tree_node_base::
tree_node_base()
    : _M_parent(nullptr), _M_child()
{ }

tree_node_base*
tree_node_base::
parent() const
{ return this->_M_parent; }

tree_node_base*
tree_node_base::
child(size_type __n) const
{
#if POL_DEBUG
    if (__n >= this->_M_child.size())
        throw std::out_of_range("tree_node_base::child");
#endif

    using _Iter = std::list<base_type*>::const_iterator;
    _Iter __i = this->_M_child.begin();
    size_type __j = 0;

    while (__i != this->_M_child.end())
    {
        if (__n == __j) return *__i;
        ++__i; ++__j;
    }

    return nullptr;
}

bool
tree_node_base::
empty() const
{
    return this->_M_child.empty();
}

tree_node_base*
tree_node_base::
front() const
{
    return this->_M_child.front();
}

tree_node_base*
tree_node_base::
back() const
{
    return this->_M_child.back();
}

void
tree_node_base::
push_back(base_type* __c)
{
    if (__c->parent() != nullptr)
        throw std::invalid_argument("pol::tree_node_base::push_back");
    this->_M_child.push_back(__c);
    __c->_M_parent = this;
}

tree_node_base*
tree_node_base::
next_child(base_type* __p) const
{
    using _Iter = child_const_iterator;
    _Iter __i = this->cbegin();
    while (__i != this->cend())
    {
        if (*__i == __p)
        {
            ++__i;
            if (__i == this->cend())
                return nullptr;
            return *__i;
        }
        ++__i;
    }
    return nullptr;
}

tree_node_base*
tree_node_base::
prev_child(base_type* __p) const
{
    using _Iter = child_const_iterator;
    _Iter __i = this->cend();
    while (__i != this->cbegin())
    {
        --__i;
        if (*__i == __p)
        {
            if (__i == this->cbegin())
                return nullptr;
            --__i;
            return *__i;
        }
    }
    return nullptr;
}

std::list<tree_node_base*>::iterator
tree_node_base::
begin()
{
    return this->_M_child.begin();
}

std::list<tree_node_base*>::iterator
tree_node_base::
end()
{
    return this->_M_child.end();
}

std::list<tree_node_base*>::const_iterator
tree_node_base::
cbegin() const
{
    return this->_M_child.cbegin();
}

std::list<tree_node_base*>::const_iterator
tree_node_base::
cend() const
{
    return this->_M_child.cend();
}

tree_base_iterator::
tree_base_iterator()
    : _M_root(nullptr), _M_st()
{ }

tree_base_iterator::
tree_base_iterator(base_type* __root, bool __t)
    : _M_root(__root), _M_st()
{
    if (!__t) this->_M_st.push(__root);
}

tree_base_iterator&
tree_base_iterator::
operator++ ()
{
    if (this->_M_st.empty())
    {
        this->_M_st.push(this->_M_root);
        return *this;
    }
    base_type* __ch = this->_M_st.top();
    if (!__ch->empty())
    {
        this->_M_st.push(__ch->front());
        return *this;
    }
    // need a better data structure?
    this->_M_st.pop();
    base_type* __pa = this->_M_st.top();
    while (__ch == __pa->back())
    {
        this->_M_st.pop();
        if (this->_M_st.empty()) return *this;
        __ch = __pa;
        __pa = this->_M_st.top();
    }
    // not effective
    __ch = __pa->next_child(__ch);
    this->_M_st.push(__ch);
    return *this;
}

tree_base_iterator&
tree_base_iterator::
operator-- ()
{
    if (this->_M_st.empty())
    {
        base_type* __np = this->_M_root;
        this->_M_st.push(__np);
        while (!__np->empty())
        {
            __np = __np->back();
            this->_M_st.push(__np);
        }
        return *this;
    }
    base_type* __ch = this->_M_st.top();
    this->_M_st.pop();
    if (this->_M_st.empty()) return *this;
    base_type* __pa = this->_M_st.top();
    if (__ch != __pa->front())
    {
        __ch = __pa->prev_child(__ch);
        this->_M_st.push(__ch);
        while (!__ch->empty())
        {
            __pa = __ch;
            __ch = __ch->back();
            this->_M_st.push(__ch);
        }
    }
    return *this;
}

inline bool
operator == (const tree_base_iterator& __lhs, const tree_base_iterator& __rhs)
{
    return __lhs._M_root == __rhs._M_root && __lhs._M_st == __rhs._M_st;
}

inline bool
operator != (const tree_base_iterator& __lhs, const tree_base_iterator& __rhs)
{
    return !(__lhs == __rhs);
}

template<typename _Tp>
tree_iterator<_Tp>::
tree_iterator(node_type* __root, bool __t)
    : tree_base_iterator((base_type*)__root, __t)
{ }

template<typename _Tp>
tree_node<_Tp>::
tree_node(const value_type& __x)
    : tree_node_base(), _M_data(__x)
{ }

template<typename _Tp>
void
tree_node<_Tp>::
data(const value_type& __x)
{
    this->_M_data = __x;
}

template<typename _Tp>
_Tp
tree_node<_Tp>::
data() const
{
    return this->_M_data;
}

template<typename _Tp>
tree_node<_Tp>*
tree_node<_Tp>::
front() const
{
    return (node_type*)this->tree_node_base::front();
}

template<typename _Tp>
tree_node<_Tp>*
tree_node<_Tp>::
back() const
{
    return (node_type*)this->tree_node_base::back();
}

template<typename _Tp>
void
tree_node<_Tp>::
push_back(node_type* __p)
{
    this->tree_node_base::push_back((base_type*)__p);
}

template<typename _Tp>
void
tree_node<_Tp>::
emplace_back()
{
    this->tree_node_base::push_back((base_type*)(new node_type));
}

template<typename _Tp>
void
tree_node<_Tp>::
emplace_back(const value_type& __x)
{
    this->tree_node_base::push_back((base_type*)(new node_type(__x)));
}

template<typename _Tp>
void
tree_node<_Tp>::
_M_construct(std::string_view __s)
{
    size_type __beg = 0;
    size_type __end = 0;
    size_type __siz = __s.size();
    std::string_view __name;
    while (__end < __siz)
    {
        switch (__s[__end])
        {
        case ',':
        {
            if (__name.empty())
            {
                __name = __s.substr(__beg, __end - __beg);
                this->emplace_back(from_string<_Tp>(__name));
            }
            __name = std::string_view();
            __beg = ++__end;
            break;
        }
        case '(':
        {
            std::stack<size_type> __st;
            __st.push(__end + 1);
            __name = __s.substr(__beg, __end - __beg);
            this->emplace_back(from_string<_Tp>(__name));
            ++__end;
            while (!__st.empty() && __end < __siz)
            {
                if (__s[__end] == '(')
                {
                    __st.push(__end + 1);
                }
                if (__s[__end] == ')')
                {
                    __beg = __st.top();
                    __st.pop();
                    if (__st.empty())
                    {
                        std::string_view __sub = __s.substr(__beg, __end - __beg);
                        // std::cerr << this->back()->_M_data << ".sub = " << __sub << '\n';
                        this->back()->_M_construct(__sub);
                        ++__end;
                        break;
                    }
                }
                ++__end;
            }
            break;
        }
        case ')':
            throw std::invalid_argument("tree_node<_Tp>::_M_construct");
        default:
            ++__end;
        }
    }
    if (__beg < __end && __name.empty())
    {
        __name = __s.substr(__beg, __end - __beg);
        this->emplace_back(from_string<_Tp>(__name));
    }
}

template<typename _Tp>
void
tree_node<_Tp>::
_M_destroy() noexcept
{
    using _Iter = std::list<base_type*>::iterator;
    _Iter __i = this->begin();
    while (__i != this->end())
    {
        node_type* __p = (node_type*)*__i;
        __p->_M_destroy();
        delete __p;
        ++__i;
    }
}

template<typename _Tp>
tree_iterator<_Tp>&
tree_iterator<_Tp>::
operator++ ()
{
    this->base_iterator::operator++ ();
    return *this;
}

template<typename _Tp>
tree_iterator<_Tp>&
tree_iterator<_Tp>::
operator-- ()
{
    this->base_iterator::operator-- ();
    return *this;
}

template<typename _Tp>
_Tp
tree_iterator<_Tp>::
operator* () const
{
    return ((node_type*)this->_M_st.top())->data();
}

template<typename _Tp>
tree_node_base*
tree_iterator<_Tp>::
base_ptr() const
{
    return this->_M_st.top();
}

template<typename _Tp>
tree_node<_Tp>*
tree_iterator<_Tp>::
node_ptr() const
{
    return (node_type*)this->_M_st.top();
}

template<typename _Tp>
tree_node<_Tp>*
tree_node<_Tp>::
parent() const
{
    return (node_type*)(this->tree_node_base::parent());
}

template<typename _Tp>
tree_node<_Tp>*
tree_node<_Tp>::
child(size_type __n) const
{
    return (node_type*)(this->tree_node_base::child(__n));
}

template<typename _Tp>
tree_node<_Tp>*
tree_node<_Tp>::
operator[] (size_type __n) const
{
    return this->child(__n);
}

template<typename _Tp>
tree<_Tp>::
tree()
    : _M_root(nullptr)
{ }

template<typename _Tp>
tree<_Tp>::
tree(std::string_view __s)
    : _M_root(nullptr)
{
    if (!__s.empty())
    {
        size_type __n = 0;
        while (__s[__n] && __s[__n] != '(') ++__n;
        if (__s[__n] != '(' || __s.back() != ')')
            throw std::invalid_argument("tree::tree");
        std::string_view __name = __s.substr(0, __n);
        this->_M_root = new node_type(from_string<_Tp>(__name));
        std::string_view __sub = __s.substr(__n + 1, __s.size() - 2 - __n);
        // std::cerr << this->_M_root->data() << ".sub = " << __sub << '\n';
        this->_M_root->_M_construct(__sub);
    }
}

template<typename _Tp>
tree<_Tp>::
~tree() noexcept
{
    this->clear();
}

template<typename _Tp>
void
tree<_Tp>::
emplace()
{
    this->_M_root = new node_type;
}

template<typename _Tp>
void
tree<_Tp>::
emplace(const value_type& __x)
{
    this->_M_root = new node_type(__x);
}

template<typename _Tp>
void
tree<_Tp>::
clear() noexcept
{
    this->_M_root->_M_destroy();
    delete this->_M_root;
}

template<typename _Tp>
tree_node<_Tp>*
tree<_Tp>::
root() const
{
    return this->_M_root;
}

template<typename _Tp>
tree_iterator<_Tp>
tree<_Tp>::
begin()
{
    return tree_iterator(this->_M_root, false);
}

template<typename _Tp>
tree_iterator<_Tp>
tree<_Tp>::
end()
{
    return tree_iterator(this->_M_root, true);
}

}

#endif /* _POL_TREE_TCC */
