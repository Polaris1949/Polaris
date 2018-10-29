#include <polaris/functional> // for pol::plus_eq, pol::max_f
#include <polaris/type_traits> // for pol::false_v
#include <vector>
#include <iostream>

namespace polaris
{

class tree_array_base
{
public:
    using size_type = std::size_t;

protected:
    static size_type _S_lowbit(size_type __x);
};

inline std::size_t
tree_array_base::
_S_lowbit(size_type __x)
{ return (__x + 1) & (~__x); }

struct tree_array_mode
{
    // modify point & inquire range
    struct mpir
    {
        template<typename _Tp>
        using default_calc = plus_eq<_Tp>;
    };

    // modify range & inquire point
    struct mrip
    {
        template<typename _Tp>
        using default_calc = plus_eq<_Tp>;
    };

    // modify range & inquire range
    struct mrir
    {
        template<typename _Tp>
        using default_calc = plus_eq<_Tp>;
    };

    // TODO: modify point & inquire min/max value in range
    struct mpim
    {
        template<typename _Tp>
        using default_calc = max_f<_Tp>;
    };
};

// TODO: template<_Tp, _Mode, _Cont, _Func>
// template<typename _Tp, typename _Mode, typename _Cont,
//     typename _Func = typename _Mode::default_calc<_Tp>>
template<typename _Tp, typename _Mode>
class tree_array
{
public:
    static_assert(false_v<_Tp>, "no such mode");
};

// TODO: 80%
template<typename _Tp>
class tree_array<_Tp, tree_array_mode::mpir>
    : public tree_array_base
{
public:
    using value_type = _Tp;
    using container_type = std::vector<_Tp>;
    using size_type = std::size_t;

private:
    container_type _M_tree;

public:
    tree_array() = default;

    template<typename _Seq>
    tree_array(const _Seq& __data);

    template<typename _Seq>
    void init(const _Seq& __data);

    bool empty() const;
    void clear();

    size_type size() const;
    void resize(size_type __s);

    const value_type& at(size_type __pos) const;
    const value_type& operator[] (size_type __pos) const;

    // TODO: Different modification operations
    void modify(size_type __x, const value_type& __k);

    value_type inquire(size_type __x, size_type __y);

private:
    value_type _M_prefix(size_type __x);
};

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
inline bool
tree_array<_Tp, tree_array_mode::mpir>::
empty() const
{ return this->_M_tree.empty(); }

template<typename _Tp>
inline void
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

// TODO
template<typename _Tp>
class tree_array<_Tp, tree_array_mode::mrip>
    : public tree_array_base
{
public:
    using value_type = _Tp;
    using container_type = std::vector<_Tp>;
    using size_type = std::size_t;

private:
    container_type _M_delta;

public:
    inline void resize(size_type __s)
    { this->_M_delta.resize(__s); }

    // TODO: Different modification operations
    void modify(size_type __x, size_type __y, const value_type& __k)
    {
        for (size_type __i{__x}; __i < this->size(); __i += _S_lowbit(__i))
            this->_M_delta[__i] += __k;
        for (size_type __i{__y}; __i < this->size(); __i += _S_lowbit(__i))
            this->_M_delta[__i] -= __k;
    }

    value_type inquire(size_type __x)
    {
        value_type __res{};
        for (size_type __i{}; __i < __x; __i += _S_lowbit(__i))
            __res += this->_M_delta[__i];
    }
};

// TODO
template<typename _Tp>
class tree_array<_Tp, tree_array_mode::mrir>
    : public tree_array_base
{
public:
    using value_type = _Tp;
    using container_type = std::vector<_Tp>;
    using size_type = std::size_t;

private:
    container_type _M_tree;

public:
    // TODO: Best implementation?
    static_assert(false_v<_Tp>, "unimplemented");
};

}

pol::tree_array<int, pol::tree_array_mode::mpir> a;

int main()
{
    int i, n, m, o, x, y;
    std::cin >> n >> m;

    {
        std::vector<int> v;
        v.resize(n);

        for (i=0; i<n; ++i)
            std::cin >> v[i];

        a.init(v);
    }

    for (i=0; i<m; ++i)
    {
        std::cin >> o >> x >> y;
        if (o==1) a.modify(--x, y);
        else std::cout << a.inquire(--x, y) << '\n';
    }

    return 0;
}
