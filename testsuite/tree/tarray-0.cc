#include <iostream>
#include <polaris/tree_array>

pol::tree_array<int, pol::tree_array_mode::mpir> a;

int main()
{
    int i, n, m, o, x, y;
    std::cin >> n >> m;

    {
        std::vector<int> v;
        v.resize(n);

        for (i=0; i<n; ++i)
            std::cin >> v[i];

        a.init(v);
    }

    for (i=0; i<m; ++i)
    {
        std::cin >> o >> x >> y;
        if (o==1) a.modify(--x, y);
        else std::cout << a.inquire(--x, y) << '\n';
    }

    return 0;
}
