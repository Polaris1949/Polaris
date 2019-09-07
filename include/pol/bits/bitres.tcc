#ifndef _POL_BITRES_TCC
#define _POL_BITRES_TCC 1

namespace pol
{

bitmem_ptr::
bitmem_ptr(nullptr_t) noexcept
    : _M_ptr{nullptr}, _M_size{0}
{ }

bitmem_ptr::
bitmem_ptr(pointer __p, size_type __n) noexcept
    : _M_ptr{__p}, _M_size{__n}
{ }

bitmem_ptr::
operator bool() const noexcept
{ return this->_M_ptr; }

bit_ptr
bitmem_ptr::
ptr() const noexcept
{ return this->_M_ptr; }

size_t
bitmem_ptr::
size() const noexcept
{ return this->_M_size; }

template<typename _Tp>
bit_resource<_Tp>::_Chunk::
_Chunk(size_type __n)
    : _M_data{new storage_type[__n]}, _M_size{__n}
{ }

template<typename _Tp>
bit_resource<_Tp>::_Chunk::
~_Chunk() noexcept
{ if (this->_M_data) delete[] this->_M_data; }

template<typename _Tp>
size_t
bit_resource<_Tp>::_Chunk::
size() const noexcept
{ return this->_M_size; }

template<typename _Tp>
basic_bit_storage<_Tp>*
bit_resource<_Tp>::_Chunk::
begin() noexcept
{ return this->_M_data; }

template<typename _Tp>
basic_bit_storage<_Tp>*
bit_resource<_Tp>::_Chunk::
end() noexcept
{ return this->_M_data + this->_M_size; }

template<typename _Tp>
bitmem_ptr
bit_resource<_Tp>::_Chunk::
allocate(size_type __n)
{
    // buggy optimization
    /*
    if (this->_M_size >= __n)
    {
        for (size_t __i{}; __i < this->_M_size; ++__i)
        {
            bitmem_ptr __p{this->_M_data[__i].allocate(__n)};
            if (__p) return __p;
        }
        return nullptr;
    }
    */

    iterator __iter{this->begin()};
    size_t __count;
    bit_ptr __p;
    //bool __again;

    while (__iter != this->end())
    {
        __count = 0;
        //__again = false;

        // left
        {
            size_t __cntl;
            while (__iter != this->end()
                && !(__cntl = __iter->free_countl()))
                ++__iter;
            if (__iter == this->end()) return nullptr;
            size_t __req = std::min(__cntl, __n);
            __iter->lockl(__req);
            __p = {&__iter->data(), __fsize - __req};
            __count += __req;
            if (__count >= __n)
                return {__p, __n};
        }

        // middle + end
        while (__iter != this->end())
        {
            size_t __cntr = __iter->free_countr();
            size_t __req = std::min(__fsize, __n - __count);
            if (__cntr < __req)
            {
                //__again = true;
                // try again
                break;
            }
            __iter->lockr(__req);
            __count += __req;
            if (__count >= __n)
                return {__p, __n};
            ++__iter;
        }

        // if (__again) continue;
    }

    return nullptr;
}

template<typename _Tp>
bitmem_ptr
bit_resource<_Tp>::
allocate(size_type __n)
{
    size_t __bs{std::ceil2(__n) >> 3}; // block size (assume 8-bit byte)
    size_t __as; // actual size
    size_t __es{sizeof(_Tp)}; // expected size
    iterator __iter{this->_M_chunk.begin()};
    while (__iter != this->_M_chunk.end())
    {
        __as = __iter->size();
        if (__as != __es && __es >= __bs)
        {
            __iter = this->_M_chunk.insert(__iter, std::move(_Chuck{__es}));
            return __iter->allocate(__n); // ok, new chunk
        }
        if (__as >= __bs)
        {
            bitmem_ptr __p{__iter->allocate(__n)};
            if (__p) return __p;
        }
        ++__iter;
        __es <<= 1;
    }
    this->_M_chunk.push_back(std::move(_Chunk{__es}));
    return this->_M_chunk.back().allocate(__n); // ok, new chunk
}

template<typename _Tp>
void
bit_resource<_Tp>::
deallocate(bitmem_ptr __p) noexcept
{
    iterator __iter{this->_M_chunk.begin()};
    while (__iter != this->_M_chunk.end())
    {
        if (__)
    }
}

template<typename _Tp = unsigned int>
bit_resource<_Tp>*
default_bit_resource()
{
    static bit_resource<_Tp> __res{};
    return &__res;
}

}

#endif /* _POL_BITRES_TCC */
