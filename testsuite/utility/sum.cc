#include <iostream>
#include <polaris/utility>

int main()
{
    std::cout << pol::sum(0, 1, 2) << '\n';
    std::cout << pol::average(3, 4, 5) << '\n';
    std::cout << pol::average<float>(6, 7, 8, 9) << '\n';
}
