#include <polaris/bit_observer>

pol::basic_bit_observer x;
pol::bit_observer<int> y{123456};

int main()
{
    std::cin >> x;
    std::cout << x << '\n';
    std::cout << y.at_observer(0) << '\n';
    return 0;
}
