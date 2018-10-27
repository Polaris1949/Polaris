#ifndef _POL_ALLOC_H
#define _POL_ALLOC_H 1

namespace polaris
{

template<typename _Tp = void>
class allocator;

template<typename _Tp>
class allocator
{
public:
    using value_type = _Tp;
    using pointer = _Tp*;
    using size_type = size_t;

    pointer allocate(size_type __n) const;
    void deallocate(pointer __p) const;
    pointer reallocate(pointer __p, size_type __n) const;

    template<typename... _Args>
    pointer construct(_Args&&... __args) const;

    void destroy(pointer __p) const;

    template<typename... _Args>
    pointer reconstruct(pointer __p, _Args&&... __args) const;
};

template<>
class allocator<void>
{
public:
    using pointer = void*;
    using size_type = size_t;

    pointer allocate(size_type __n) const;
    void deallocate(pointer __p) const;
    pointer reallocate(pointer __p, size_type __n) const;
};

}

#endif /* _POL_ALLOC_H */
