#ifndef _POL_ALLOC_TCC
#define _POL_ALLOC_TCC 1

#include <new>

namespace polaris
{

template<typename _Tp>
_Tp*
allocator<_Tp>::
allocate(size_type __n) const
{
    return ::operator new (sizeof(_Tp) * __n);
}

template<typename _Tp>
void
allocator<_Tp>::
deallocate(pointer __p) const
{
    ::operator delete (__p);
}

template<typename _Tp>
_Tp*
allocator<_Tp>::
reallocate(pointer __p, size_type __n) const
{
    this->deallocate(__p);
    return this->allocate(__n);
}

template<typename _Tp>
template<typename... _Args>
_Tp*
allocator<_Tp>::
construct(_Args&&... __args) const
{
    return new _Tp{__args...};
}

template<typename _Tp>
void
allocator<_Tp>::
destroy(pointer __p) const
{
    delete __p;
}

template<typename _Tp>
template<typename... _Args>
_Tp*
allocator<_Tp>::
reconstruct(pointer __p, _Args&&... __args) const
{
    this->destroy(__p);
    return this->construct(__args...);
}

void*
allocator<void>::
allocate(size_type __n) const
{
    return ::operator new (sizeof(char) * __n);
}

void
allocator<void>::
deallocate(pointer __p) const
{
    ::operator delete (__p);
}

void*
allocator<void>::
reallocate(pointer __p, size_type __n) const
{
    this->deallocate(__p);
    return this->allocate(__n);
}

}

#endif /* _POL_ALLOC_TCC */
