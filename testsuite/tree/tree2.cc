#include <iostream>
#define private public
#define protected public
#include <pol/tree>
#include <pol/log>

using base = pol::tree_node_base;
using node = pol::tree_node<std::string>;
using iter = pol::tree_base_iterator;
using tree = pol::tree<std::string>;

int main() try
{
    tree t("a0(b1(e4,f5),c2,d3(g6))");
    auto i = t.begin();
    while (i != t.end())
    {
        std::cout << *i << '\n';
        ++i;
    }
    do
    {
        --i;
        std::cout << *i << '\n';
    }
    while (i != t.begin());
    pol::log::note("TEST");
    return 0;
}
catch (std::exception& e)
{
    std::cerr << e.what() << '\n';
    std::terminate();
}