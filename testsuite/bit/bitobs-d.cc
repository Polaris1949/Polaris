#include <polaris/bit_observer>

pol::bit_observer<double> x;

int main()
{
    std::cin >> x.data();
    std::cout << x << '\n';
}
