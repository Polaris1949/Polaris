namespace polaris
{

template<typename _Tp>
_Tp qpow(_Tp __x, _Tp __y, _Tp __mod)
{
	_Tp __res{1};
	_Tp __tmp{__x % __mod};

	while (__y)
	{
		if (__y & 1) __res = __res * __tmp % __mod;
		__tmp = __tmp * __tmp % __mod;
		__y >>= 1;
	}

	return __res;
}

}

namespace pol = polaris;

#include <set>
#include <vector>
#include <algorithm>

namespace polaris
{

template<typename _Tp>
class chtholly_tree_node
{
public:
    using size_type = std::size_t;
    using value_type = _Tp;

private:
    size_type _M_left;
    size_type _M_right;
    mutable value_type _M_data;

public:
    chtholly_tree_node() = default;
    chtholly_tree_node(size_type __l, size_type __r);
    chtholly_tree_node(size_type __l, size_type __r, const value_type& __v);

    size_type left() const;
    size_type right() const;
    value_type& data() const;
    size_type length() const;

    bool operator < (const chtholly_tree_node& __o) const;
};

template<typename _Tp>
class chtholly_tree
{
public:
    using size_type = std::size_t;
    using value_type = _Tp;
    using node_type = chtholly_tree_node<value_type>;
    using container_type = std::set<node_type>;
    using iterator = typename container_type::iterator;

private:
    container_type _M_sto;

    iterator
    _M_split(size_type __pos);

public:
    chtholly_tree() = default;

    template<typename _Seq>
    chtholly_tree(const _Seq& __data);

    template<typename _Seq>
    void
    init(const _Seq& __data);

    void
    plus(size_type __l, size_type __r, const value_type& __v);

    void
    assign(size_type __l, size_type __r, const value_type& __v);

    value_type
    rank(size_type __l, size_type __r, size_type __k);

    value_type
    pow_sum(size_type __l, size_type __r, value_type __exp, value_type __mod);
};

}

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

    throw std::out_of_range{std::string{"chtholly_tree::rank(): __k "
        "(which is "} + std::to_string(__k) + ") >= range [__l, __r) length "
        "(which is " + std::to_string(__r - __l) + ")"};
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

#include <iostream>

using llong = long long;

pol::chtholly_tree<llong> ct;
int n, m;
llong seed, mod;

int rnd()
{
	int res = seed;
	seed = (seed * 7 + 13) % 1000000007;
	return res;
}

int main()
{
    std::cin >> n >> m >> seed >> mod;

    {
        std::vector<llong> data;

        for (int i = 0; i < n; ++i)
            data.push_back(rnd() % mod + 1);

        ct.init(data);
    }

	while (m--)
	{
		int op{rnd() % 4 + 1};
		int l{rnd() % n + 1};
		int r{rnd() % n + 1};
		int x{}, y{};

		if (l > r) std::swap(l, r);
		if (op == 3) x = (rnd() % (r - l + 1)) + 1;
		else x = (rnd() % mod) + 1;
		if (op == 4) y = (rnd() % mod) + 1;
        --l;

		switch (op)
		{
		case 1:
            ct.plus(l, r, x);
			break;

		case 2:
            ct.assign(l, r, x);
			break;

		case 3:
            std::cout << ct.rank(l, r, --x) << '\n';
			break;

		case 4:
            std::cout << ct.pow_sum(l, r, x, y) << '\n';
			break;
		}
	}

    return 0;
}
