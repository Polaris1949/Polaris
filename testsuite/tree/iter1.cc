#include <iostream>
#define private public
#define protected public
#include <pol/tree>

using base = pol::tree_node_base;
using node = pol::tree_node<char>;
using iter = pol::tree_base_iterator;
using tree = pol::tree<char>;

int main()
{
    tree t;
    t.emplace('a');
    t.root()->emplace_back('b');
    t.root()->emplace_back('c');
    t.root()->emplace_back('d');
    t.root()->child(0)->emplace_back('e');
    t.root()->child(0)->emplace_back('f');
    t.root()->child(2)->emplace_back('g');
    auto i = t.begin();
    while (i != t.end())
    {
        std::cout << *i << '\n';
        ++i;
    }
    return 0;
}