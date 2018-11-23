#include <iostream>
#include <polaris/allocator>

pol::allocator<int> a;

int main()
{
    int* p = a.allocate(1);
    a.deallocate(p);
}
