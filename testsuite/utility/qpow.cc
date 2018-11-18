#include <iostream>
#include <unordered_map>
#include <polaris/utility>

int main()
{
    uint n, i, a, b, k;
    std::unordered_map<uint, uint> c;
    std::cin >> n >> a >> k;

    for (i = 0; i < n; ++i)
    {
        std::cin >> b;
        std::cout << pol::exqpowmod(a, b, k, c) << '\n';
    }

    return 0;
}
