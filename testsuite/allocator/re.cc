#include <iostream>
#include <pol/allocator>

struct foo
{
    foo() { std::cout << "constructor\n"; }
    foo(int) { std::cout << "constructor (int)\n"; std::terminate(); }
    ~foo() { std::cout << "destructor\n"; }
};

int main()
{
    pol::allocator<foo> a;
    foo* p = a.construct();
    p = a.reconstruct(p, 0);
}
