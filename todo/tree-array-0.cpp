#include <polaris/type_traits>
#include <vector>

namespace polaris
{

class tree_array_base
{
public:
    using size_type = std::size_t;

protected:
    inline static size_type _S_lowbit(size_type __x)
    { return (__x + 1) & (~__x); }
};

// TODO
// template<typename _Tp, typename _Func, typename _Mode>
template<typename _Tp, typename _Mode>
class tree_array
{
public:
    static_assert(false_v<_Tp>, "no such mode");
};

struct tree_array_mode
{
    struct mpip {}; // modify point & inquire point (deprecated)
    struct mpir {}; // modify point & inquire range
    struct mrip {}; // modify range & inquire point
    struct mrir {}; // modify range & inquire range
};

// TODO
template<typename _Tp>
class tree_array<_Tp, tree_array_mode::mpip>
{
public:
    using value_type = _Tp;
    using container_type = std::vector<_Tp>;
    using size_type = std::size_t;

private:
    container_type _M_tree;

public:
    static_assert(false_v<_Tp>, "deprecated");
};

// TODO
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
    inline void resize(size_type __s)
    { this->_M_tree.resize(__s); }

    // TODO: Different modification operations
    void modify(size_type __x, const value_type& __k)
    {
        for (size_type __i{__x}; __i < this->size(); __i += _S_lowbit(__i))
            this->_M_tree[__i] += __k;
    }

    inline value_type inquire(size_type __x, size_type __y)
    { return this->_M_prefix(__y) - this->_M_prefix(__x); }

private:
    value_type _M_prefix(size_type __x)
    {
        value_type __res{};
        for (size_type __i{}; __i < __x; __i += _S_lowbit(__i))
            __res += this->_M_tree[__i];
        return __res;
    }
};

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
{
public:
    using value_type = _Tp;
    using container_type = std::vector<_Tp>;
    using size_type = std::size_t;

private:
    container_type _M_tree;

public:
    static_assert(false_v<_Tp>, "unimplemented");
};

}
