#include <pol/allocator>

int main() try
{
    pol::allocator<void> a;
    void* p = a.allocate(16);
    a.deallocate(p);
    p = nullptr;
    p = a.reallocate(p, 32);
    a.deallocate(p);
}
catch (...)
{ std::terminate(); }
