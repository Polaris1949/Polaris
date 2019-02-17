#ifndef _POL_BITRES_H
#define _POL_BITRES_H 1

#include <list>
#include <memory>

namespace polaris
{

template<typename _Tp>
class bit_usage
{
public:
    using storage_type = basic_bit_storage<_Tp>;
    using bit_view_type = basic_bit_view<_Tp>;
    using level_type = unsigned char;
    using count_type = unsigned char;
    using size_type = std::size_t;

private:
    storage_type* _M_data;
    unsigned char _M_count;

public:
    bit_usage() = default;
    bit_usage(storage_type* __data);

    bool set(level_type __n);
    bool reset(level_type __n);
    bool get(level_type __n) const;

    bool full() const;
    bool get_any(level_type& __n);
    bit_view_type get_any_v();

    storage_type* storage() const;
};

template<typename _Tp>
class bit_resource
{
public:
    using storage_type = basic_bit_storage<_Tp>;
    using bit_type = basic_bit<_Tp>;
    using bit_view_type = basic_bit_view<_Tp>;
    using usage_type = bit_usage<_Tp>;
    using container_type = std::list<usage_type>;
    using iterator = typename container_type::iterator;
    using level_type = unsigned char;
    using size_type = std::size_t;

private:
    container_type _M_chunk;
    iterator _M_cur;

public:
    bit_ptr allocate(size_type __n);
    void deallocate(bit_ptr __p, size_type __n);

/*
    bit_view_type allocate_v();
    [[deprecated]] bit_type* allocate();
    [[deprecated]] storage_type* allocate(level_type& __n);

    void deallocate(bit_type* __ptr);
    void deallocate_v(bit_view_type __v);
*/
};

template<typename _Tp = unsigned int>
bit_resource<_Tp>* global_bit_resource();

}

#endif /* _POL_BITRES_H */
