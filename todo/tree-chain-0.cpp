#include <polaris/version>
#include <polaris/tree>

namespace polaris
{

template<typename _Tp>
class tree_chain_node
    : public tree_node<_Tp>
{
public:
    using value_type = _Tp;
    using size_type = std::size_t;

private:
    _Tp _M_mark;

public:
    tree_chain_node(const value_type& __x);

    value_type& mark();
    const value_type& mark() const;
};

template<typename _Tp>
class tree_chain
{
public:
    using value_type = _Tp;
    using size_type = std::size_t;
    using node_type = tree_chain_node<_Tp>;

private:
    node_type* _M_root;

public:
    tree_chain() = default;

    template<typename _Seq>
    void init(const _Seq& __data);

    void construct(size_type __b, size_type __e);
    void push_down(node_type* __p, size_type __len);
    value_type inquire(size_type __b, size_type __e);
    void modify(size_type __b, size_type __e, const value_type& __k);
    value_type inquire_child(size_type __b, size_type __e);
    void modify_child(size_type __b, size_type __e, const value_type& __k);
};

}
