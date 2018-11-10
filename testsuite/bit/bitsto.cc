#include <iostream>
#include <polaris/bit>

using ubyte = unsigned char;
pol::bit_storage a;

int main()
{
    ubyte x{a.obtain()};
    a.set(x, true);
    std::cout << a.get(x) << '\n';
    a.release(x);
    return 0;
}
