#include <iostream>
#include <stdexcept>
#include <pol/allocator>
#include "db.h"

pol::allocator<foo> a;

int main()
{
    foo* p = nullptr;
    try
    {
        a.destroy(a.construct());
        p = a.construct();
        std::cerr << "ok for #1\n";
        a.destroy(p);
        p = nullptr;
        p = a.reallocate(p, 19260817_MB);
        a.deallocate(p);
        std::cerr << "ok for #2\n";
    }
    catch (...)
    {
        std::terminate();
    }
}
