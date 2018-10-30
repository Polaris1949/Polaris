#include <iostream>
#include <vector>
#include <polaris/tree_array>

pol::tree_array<int, pol::tree_array_mode::mrip> a;

int main()
{
    int i, n, m, o, x, y, k;
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
        std::cin >> o;

        if (o==1)
        {
            std::cin >> x >> y >> k;
            a.modify(--x, y, k);
        }
        else
        {
            std::cin >> x;
            std::cout << a.inquire(--x) << '\n';
        }
    }

    return 0;
}
