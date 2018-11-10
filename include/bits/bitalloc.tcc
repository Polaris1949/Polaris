#ifndef _POL_BITALLOC_TCC
#define _POL_BITALLOC_TCC 1

namespace polaris
{

template<typename _Tp>
bit_ptr
bit_allocator<_Tp>::
allocate()
{
    return global_bit_resource().allocate();
}

template<typename _Tp>
void
bit_allocator<_Tp>::
deallocate(bit_ptr __p)
{
    global_bit_resource().deallocate(__p);
}

template<typename _Tp>
bit_ptr
bit_allocator<_Tp>::
reallocate(bit_ptr __p)
{
    this->deallocate(__p);
    return this->allocate();
}

}

#endif
