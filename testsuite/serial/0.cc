#include <iostream>
#include <pol/serial>

struct alpha
{
    int a;
    int b;
};

struct beta
{
    beta() = delete;
    beta(int x):i(x) {}
    int i;
};

int main()
{
    alpha x;
    x.a = 1; x.b = 2;
    for (char& e : pol::serialize(x))
    {
        std::cout << (int)e << '\n';
    }
    std::cout << '\n';
    beta b1(8);
    auto b2 = pol::deserialize<beta>(pol::serialize(b1));
    std::cout << b2.i << '\n';
    char* p = pol::serialize_raw(x);
    std::cout << (int)*p << '\n';
    delete[] p;
    x = pol::deserialize_raw<alpha>("a\0\0\0b\0\0\0");
    std::cout << x.a << ' ' << x.b << '\n';
}