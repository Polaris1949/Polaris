#include <pol/allocator>

namespace pol
{

void*
allocator<void>::
allocate(size_type __n)
{ return ::operator new (sizeof(char) * __n); }

void
allocator<void>::
deallocate(pointer __p) noexcept
{ ::operator delete (__p); }

void*
allocator<void>::
reallocate(pointer __p, size_type __n)
{
    this->deallocate(__p);
    return this->allocate(__n);
}

}
