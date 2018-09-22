#include <polaris/bits/graph/edge>

int main()
{
    pol::edge<> a{1, 2};
    pol::edge<> b{0, 1};
    std::cout << (a < b) << '\n';
    std::cout << pol::edge<int>{b, 3} << '\n';
}
