#include <iostream>
#include <vector>
#include <pol/range_map>

int main()
{
    pol::rm_1idx<std::vector<int>> a;
    std::vector<int>& v=a.container();
    v.push_back(1);
    v.push_back(2);
    std::cout << a[2] << '\n';
}
