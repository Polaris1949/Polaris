#include <pol/segment_tree>
#include <iostream>
#include <vector>

using llong = long long;

struct delta
{
    llong plus, mul;

    delta()
        : plus(0), mul(1)
    { }

    bool operator == (const delta& x) const
    { return this->plus == x.plus && this->mul == x.mul; }
};

int n, m, p;

struct data_func_t
{
    llong operator() (llong x, llong y) const
    { return (x + y) % p; }
};

using node_t = pol::segment_tree_node<llong, delta>;

struct search_func_t
{
    void operator() (node_t* root, delta x) const
    {
        root->mark().mul = (root->mark().mul * x.mul) % p;
        root->mark().plus = (root->mark().plus * x.mul) % p;
        root->data() = (root->data() * x.mul) % p;
        root->mark().plus = (root->mark().plus + x.plus) % p;
        root->data() = (root->data() + root->segment() * x.plus) % p;
    }
};

struct mod_func_plus_t
{
    void operator() (node_t* root, llong x) const
    {
        root->mark().plus = (root->mark().plus + x) % p;
        root->data() = (root->data() + x * root->segment()) % p;
    }
};

struct mod_func_mul_t
{
    void operator() (node_t* root, llong x) const
    {
        root->data() = (root->data() * x) % p;
        root->mark().plus = (root->mark().plus * x) % p;
        root->mark().mul = (root->mark().mul * x) % p;
    }
};

std::vector<llong> v;
pol::segment_tree<llong, delta, data_func_t> stree;

int main()
{
    int i, f;
    llong x, y, k;
    std::cin >> n >> m >> p;
    v.resize(n);

    for (i=0; i<n; i++)
        std::cin >> v[i];

    stree.construct(0, n, v);

    for (i=0; i<m; i++)
    {
        std::cin >> f;

        if (f==1)
        {
            std::cin >> x >> y >> k;
            stree.modify(--x, y, k, mod_func_mul_t(), search_func_t());
        }
        else if (f==2)
        {
            std::cin >> x >> y >> k;
            stree.modify(--x, y, k, mod_func_plus_t(), search_func_t());
        }
        else
        {
            std::cin >> x >> y;
            std::cout << stree.search(--x, y, search_func_t()) << '\n';
        }
    }

    return 0;
}
