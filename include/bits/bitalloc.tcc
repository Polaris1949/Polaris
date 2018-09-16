#ifndef _POL_BITALLOC_TCC
#define _POL_BITALLOC_TCC 1

namespace polaris
{

template<typename _Tp>
basic_bit<_Tp>*
bit_allocator<_Tp>::
allocate()
{
    basic_bit_view<_Tp> __tmp{global_bit_resource<>()->allocate_v()};
    //return new bit_type{global_bit_resource<>()->allocate()};
}

}

#endif
