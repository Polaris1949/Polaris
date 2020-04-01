#include <pol/memory>
#include <pol/format>
#include <iostream>

using pol::mbyte;

void print(void* p, size_t n)
{
    mbyte* beg = (mbyte*)p;
    mbyte* end = beg + n;
    size_t line = 0;
    size_t col = 0;
    std::cout << "         ";
    while (col<16)
    {
        std::cout << fmt::format("?{:01x}", col) << ' ';
        ++col;
    }
    std::cout << '\n';
    col = 0;
    while (beg<end)
    {
        if (col==0) std::cout << fmt::format("{:07x}?", line) << ' ';
        std::cout << fmt::format("{:02x}", *beg) << ' ';
        ++col; ++beg;
        if ((col&0xf)==0)
        {
            col = 0; ++line;
            std::cout << '\n';
        }
    }
    if (col&0xf) std::cout << '\n';
}

constexpr size_t sz = 1024 * 1024;

int main() try
{
    pol::local_buffer<sz> x;
    print(&x, sz);
}
catch (...) {std::terminate();}