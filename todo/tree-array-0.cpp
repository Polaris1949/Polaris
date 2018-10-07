// TODO
// template<typename _Tp, typename _Func, typename _Mode>
template<typename _Tp>
class tree_array
{
public:
    using value_type = _Tp;
    using container_type = std::vector<_Tp>;
    using size_type = std::size_t;

private:
    container_type _M_tree;
    // container_type _M_array;
    // int tree[500005], arr[500000];

public:
    // void init();

    inline void resize(size_type __s)
    { this->_M_tree.resize(__s); }

    value_type inquire(size_type __x)
    {
        value_type __res{};
        for (size_type __i{}; __i < __x; __i += _S_lowbit(__i))
            __res += this->_M_array[__i];
    }

    /*
    inline int num(int x)
    {
        int tmp=0;
        for(register int i=x;i;i-=lowbit(i)) tmp+=arr[i];
        return tmp;
    }
    */

    // TODO: Different modification operations
    void modify(size_type __x, const value_type& __k)
    {
        for (size_type __i{__x}; __i < this->size(); __i += _S_lowbit(__i))
            this->_M_tree[__i] += __k;
    }

    /*
    inline void add(int x,int k)
    {
        int tmp=k-num(x-1);
        for(register int i=x;i<=n;i+=lowbit(i)) tree[i]+=k,arr[i]+=tmp;
    }
    */

    void modify(size_type __x, size_type __y, const value_type& __k)
    {
        for (size_type __i{__x}; __i < this->size(); __i += _S_lowbit(__i))
            this->_M_array[__i] += __k;
        for (size_type __i{__y}; __i < this->size(); __i += _S_lowbit(__i))
            this->_M_array[__i] -= __k;
    }

    /*
    inline void add_range(int x,int y,int k)
    {
        for(register int i=x;i<=n;i+=lowbit(i)) arr[i]+=k;
        for(register int i=y+1;i<=n;i+=lowbit(i)) arr[i]-=k;
    }
    */

    inline value_type inquire(size_type __x, size_type __y)
    {
        return this->_M_prefix(__y) - this->_M_prefix(__x);
    }

private:
    inline static size_type _S_lowbit(size_type __x)
    { return (__x + 1) & (~__x); }

    value_type _M_prefix(size_type __x)
    {
        value_type __res{};
        for (size_type __i{}; __i < __x; __i += _S_lowbit(__i))
            __res += this->_M_tree[__i];
        return __res;
    }
};
