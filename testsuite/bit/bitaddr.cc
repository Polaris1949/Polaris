#include <iostream>
#include <polaris/memory>

int main()
{
    pol::uchar n;
    pol::bit_address x{&n, 0};
    std::cout << x << '\n';
    std::cout << sizeof(pol::bit_address) << '\n';
    std::cout << alignof(pol::bit_address) << '\n';
}
