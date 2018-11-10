#ifndef _POL_BITALLOC_H
#define _POL_BITALLOC_H 1

namespace polaris
{

template<typename _Tp>
class bit_allocator
    : public allocator<_Tp>
{
public:
    using size_type = std::size_t;

public:
    bit_ptr allocate();
    void deallocate(bit_ptr __p);
    bit_ptr reallocate(bit_ptr __p);
};

template<typename _Tp>
class bitfield_allocator
    : public allocator<_Tp>
{
public:
    using size_type = std::size_t;

public:
    bitfield_ptr allocate(size_type __n);
    void deallocate(bitfield_ptr __p);
    bitfield_ptr reallocate(bitfield_ptr __p, size_type __n);
};

}

#endif /* _POL_BITALLOC_H */
