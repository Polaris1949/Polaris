#ifndef _POL_BITALLOC_H
#define _POL_BITALLOC_H 1

namespace polaris
{

template<typename _Tp>
class bit_allocator
{
public:
    using size_type = std::size_t;
    using bit_type = basic_bit<_Tp>;

public:
    bit_type* allocate();
    //bitfield_view* allocate(size_type __n);

    void deallocate(bit_type* __p);
    //void deallocate(bitfield_view* __p);

    bit_type* reallocate();
    //bitfield_view* reallocate(size_type __n);
};

}

#endif
