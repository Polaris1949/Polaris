#include <iostream>
#include <polaris/utility>

int main()
{
    int x{};
    std::cout << pol::inc(x) << ' ' << pol::inc_copy(x) << '\n';
    std::cout << pol::dec(x) << ' ' << pol::dec_copy(x) << '\n';
}
