#include <polaris/version>

namespace polaris
{

template<typename _Tp>
class tree_chain_node
    : public binary_tree_node<_Tp>
{
public:
    using value_type = _Tp;
    using size_type = std::size_t;

private:
    _Tp _M_mark;

public:
    tree_chain_node(const value_type& __x);
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
};

}
