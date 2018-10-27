#ifndef _POL_ALLOC_TCC
#define _POL_ALLOC_TCC 1

namespace polaris
{

template<typename _Tp>
_Tp*
allocator<_Tp>::
allocate(size_type __n)
{
    return ::operator new (std::nothrow) _Tp[__n];
}

template<typename _Tp>
void
allocator<_Tp>::
deallocate(pointer __p)
{
    return ::operator delete[] __p;
}

}

#endif /* _POL_ALLOC_TCC */
