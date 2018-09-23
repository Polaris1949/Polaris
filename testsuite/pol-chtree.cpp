#include <iostream>
#include <polaris/chtholly_tree>

using llong = long long;

pol::chtholly_tree<llong> ct;
int n, m;
llong seed, mod;

int rnd()
{
    int res = seed;
    seed = (seed * 7 + 13) % 1000000007;
    return res;
}

int main()
{
    std::cin >> n >> m >> seed >> mod;

    {
        std::vector<llong> data;

        for (int i = 0; i < n; ++i)
            data.push_back(rnd() % mod + 1);

        ct.init(data);
    }

    while (m--)
    {
        int op{rnd() % 4 + 1};
        int l{rnd() % n + 1};
        int r{rnd() % n + 1};
        int x{}, y{};

        if (l > r) std::swap(l, r);
        if (op == 3) x = (rnd() % (r - l + 1)) + 1;
        else x = (rnd() % mod) + 1;
        if (op == 4) y = (rnd() % mod) + 1;
        --l;

        switch (op)
        {
        case 1:
            ct.plus(l, r, x);
            break;

        case 2:
            ct.assign(l, r, x);
            break;

        case 3:
            std::cout << ct.rank(l, r, --x) << '\n';
            break;

        case 4:
            std::cout << ct.pow_sum(l, r, x, y) << '\n';
            break;
        }
    }

    return 0;
}
