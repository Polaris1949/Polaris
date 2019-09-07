#ifndef _POL_BYTERES_TCC
#define _POL_BYTERES_TCC 1

#include <memory_resource>

namespace pol
{

void*
byte_resource::
allocate(size_type __n)
{
    return std::pmr::get_default_resource()->allocate(__n);
}

void
byte_resource::
deallocate(pointer __p)
{
    std::pmr::get_default_resource()->deallocate(__p, npos);
}

void*
byte_resource::
reallocate(pointer __p, size_type __n)
{
    this->deallocate(__p);
    return this->allocate(__p, __n);
}

}

#endif
