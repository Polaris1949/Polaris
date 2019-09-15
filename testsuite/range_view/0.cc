#include <iostream>
#include <pol/range_view>

int main()
{
    int a[20];
    for (int i = 0; i < 20; ++i)
        a[i] = i * 2 + 1;
    pol::range_view<int> r{a + 10, a + 20};
    std::cout << r[-1] << '\n';
}
