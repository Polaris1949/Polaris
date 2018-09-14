#ifndef _POL_INTALLOC_TCC
#define _POL_INTALLOC_TCC 1

#include <cstdlib>

namespace polaris
{

integer_allocator::
integer_allocator()
{
}

integer_allocator::
~integer_allocator() noexcept
{
}

_Int_allocator::
_Int_allocator() noexcept
{
}

_Int_allocator::
~_Int_allocator() noexcept
{
}

void*
_Int_allocator::
allocate(size_type __n)
{
	return std::malloc(__n);
}

void*
_Int_allocator::
reallocate(pointer __p, size_type __n)
{
	return std::realloc(__p, __n);
}

void
_Int_allocator::
deallocate(pointer __p)
{
	std::free(__p);
}

}

#endif
