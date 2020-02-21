#include <pol/allocator>
#include <iostream>
#include "db.h"

int main()
{
    pol::nt_allocator<char> a;
    char* p = a.allocate(19260817_KB);
    if (p)
        std::cerr << "success\n";
    else
        std::cerr << "failure\n";
    a.deallocate(p);
}
