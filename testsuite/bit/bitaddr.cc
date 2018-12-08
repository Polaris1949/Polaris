#include <iostream>
#include <polaris/memory>

int main()
{
    pol::uchar n;
    pol::bit_address x{&n, (size_t)0u};
    std::cout << x << '\n';
    std::cin >> x;
    std::cout << x << '\n';
    static_assert(sizeof(pol::bit_address) == sizeof(size_t) * 2);
}
