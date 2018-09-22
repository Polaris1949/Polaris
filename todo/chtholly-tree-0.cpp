#include <polaris/version>
#include <set>

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
    value_type _M_data;

public:
    chtholly_tree_node() = default;
    chtholly_tree_node(size_type __l, size_type __r);
    chtholly_tree_node(size_type __l, size_type __r, const value_type& __v);

    size_type left() const;
    size_type right() const;
    value_type& data();
    const value_type& data() const;

    bool operator < (const chtholly_tree_node& __o) const;
};

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
data()
{ return this->_M_data; }

template<typename _Tp>
inline const _Tp&
chtholly_tree_node<_Tp>::
data() const
{ return this->_M_data; }

template<typename _Tp>
inline bool
chtholly_tree_node<_Tp>::
operator < (const chtholly_tree_node& __o) const
{ return this->left() < __o.left(); }

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

    iterator split(size_type __pos)
    {
        iterator __it{this->_M_sto.lower_bound(node_type{__pos, -1})};
        if (__it != _M_sto.end() && it->left() == __pos)
            return __it;
        --__it;
        size_type __l = __it->left();
        size_type __r = __it->right();
        value_type __v = __it->data();
        this->_M_sto.erase(__it);
        this->_M_sto.insert(node_type{__l, __pos-1, __v});
        return this->_M_sto.insert(node_type{__pos, __r, __v}).first;
    }

public:
    template<typename _Seq>
    void init(const _Seq& __data)
    {
        size_type __n{__data.size()};
        for (size_type __i{}; __i < __n; ++__i)
            this->_M_sto.insert(node_type{__i, __i, __data[i]});
        this->_M_sto.insert(node_type{__n + 1, __n + 1});
    }

    template<typename _Func>
    void add_range(size_type __l, size_type __r, value_type __v)
    {
        set<node>::iterator itl = split(l),itr = split(r+1);
        for (; itl != itr; ++itl)
            itl->v += val;
    }

    void assign_range(int l, int r, long long val) {
        set<node>::iterator itl = split(l),itr = split(r+1);
        _M_sto.erase(itl, itr);
        _M_sto.insert(node(l, r, val));
    }
    long long range_rank(int l, int r, int k) {
        vector<pair<long long, int> > vp;
        set<node>::iterator itl = split(l),itr = split(r+1);
        vp.clear();
        for (; itl != itr; ++itl)
            vp.push_back(pair<long long,int>(itl->v, itl->r - itl->l + 1));
        sort(vp.begin(), vp.end());
        for (vector<pair<long long,int> >::iterator it=vp.begin(); it!=vp.end(); ++it) {
            k -= it->second;
            if (k <= 0)
                return it->first;
        }
    }
    long long pow_sum_range(int l, int r, int ex, int mod) {
        set<node>::iterator itl = split(l),itr = split(r+1);
        long long res = 0;
        for (; itl != itr; ++itl)
            res = (res + (long long)(itl->r - itl->l + 1) * qpow(itl->v, (long long)(ex), (long long)(mod))) % mod;
        return res;
    }
};

}
