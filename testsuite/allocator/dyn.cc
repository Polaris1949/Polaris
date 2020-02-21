#include <pol/allocator>
#include <iostream>

int main()
{
    pol::allocator<int> a;
    std::cout << sizeof(a) << '\n';
    std::cout << sizeof((std::allocator<void>())) << '\n';
}
