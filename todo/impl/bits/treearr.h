#ifndef _POL_TREEARR_H
#define _POL_TREEARR_H 1

namespace polaris
{

// TODO: More general base?
class tree_array_base
{
public:
    using size_type = std::size_t;

protected:
    static size_type _S_lowbit(size_type __x);
};

// TODO: More
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

// TODO: 80%
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
    void modify(size_type __x, size_type __y, const value_type& __k);

    value_type inquire(size_type __x);
};

// TODO: 0%
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

// TODO: 0%
template<typename _Tp>
class tree_array<_Tp, tree_array_mode::mpim>
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

#endif /* _POL_TREEARR_H */
