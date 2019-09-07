#include <iostream>
#include <pol/contract>

struct foo
{
    constexpr foo(int x)
        : data_{x}
    {
        pol::expect(x, "invalid argument", "x should not be 0");
    }

    int data_;
};

int main()
{
    constexpr foo a{0};
}
