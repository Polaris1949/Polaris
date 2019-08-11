#include <map>
#include <iostream>

using iter_t = std::map<int, int>::iterator;

uintptr_t itou(iter_t i)
{
    return *reinterpret_cast<uintptr_t*>(std::addressof(i));
}

iter_t utoi(uintptr_t u)
{
    return *reinterpret_cast<iter_t*>(std::addressof(u));
}

int main()
{
    std::cout << sizeof(iter_t) << '\n';
    std::cout << sizeof(uintptr_t) << '\n';
    itou(iter_t{});
    utoi(uintptr_t{});
}
