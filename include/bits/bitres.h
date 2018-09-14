#ifndef _POL_BITRES_H
#define _POL_BITRES_H 1

#include <list>
#include <memory>

namespace polaris
{

template<typename _STp>
class bit_usage
{
public:
    using storage_type = basic_bit_storage<_STp>;
    using level_type = unsigned char;
    using count_type = unsigned char;

private:
    std::shared_ptr<storage_type> _M_data;
    unsigned char _M_count;

public:
    bit_usage() = default;
    bit_usage(storage_type* __data);

    bool set(level_type __n);
    bool reset(level_type __n);

    bool full() const;
    bool get_any(level_type& __n);

    storage_type* storage() const;
};

template<typename _STp>
class bit_resource
{
public:
    using storage_type = basic_bit_storage<_STp>;
    using bit_type = basic_bit<_STp>;
    using usage_type = bit_usage<_STp>;
    using container_type = std::list<std::shared_ptr<usage_type>>;
    using iterator = typename container_type::iterator;
    using level_type = unsigned char;

private:
    container_type _M_chunk;
    iterator _M_cur;

public:
    bit_type* allocate();
    storage_type* allocate(level_type& __n);
    void deallocate(bit_type* __ptr);
};

template<typename _STp = unsigned int>
bit_resource<_STp>* global_bit_resource();

}

#endif /* _POL_BITRES_H */
