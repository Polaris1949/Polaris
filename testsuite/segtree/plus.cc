#include <vector>
#include <iostream>
#include <algorithm>
#include <pol/segment_tree>

using llong = long long;

struct fsum_t
{
    llong operator() (llong x, llong y) const
    { return x+y; }
};

struct fmod_t
{
    using node_type = pol::segment_tree_node<llong, llong>;

    void operator() (node_type* root, llong x) const
    {
        root->data() += root->segment()*x;
        root->mark() += x;
    }
};

llong n, m;
std::vector<llong> v;
pol::segment_tree<llong, llong, fsum_t> stree;

int main()
{
    llong i, x, y, k, f;
    std::cin >> n >> m;
    v.resize(n);

    for (i=0; i<n; ++i)
        std::cin >> v[i];

    stree.construct(0, n, v);

    for (i=0; i<m; ++i)
    {
        std::cin >> f;

        if (f==1)
        {
            std::cin >> x >> y >> k;
            stree.modify(--x, y, k, fmod_t(), fmod_t());
        }
        else
        {
            std::cin >> x >> y;
            std::cout << stree.search(--x, y, fmod_t()) << '\n';
        }
    }

    return 0;
}
