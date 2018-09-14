#ifndef _POL_BIT_H
#define _POL_BIT_H 1

namespace polaris
{

template<typename _STp>
class basic_bit
{
public:
    using storage_type = basic_bit_storage<_STp>;
    using level_type = typename storage_type::level_type;
    using self_type = basic_bit<_STp>;
    using resource_type = bit_resource<_STp>;

private:
    storage_type* _M_ptr;
    resource_type* _M_res;
    level_type _M_lev;

public:
    basic_bit();
    basic_bit(const self_type& __o);
    basic_bit(self_type&& __o);
    explicit basic_bit(bool __data);
    explicit basic_bit(storage_type* __ptr);

    self_type& operator = (bool __data);
    self_type& operator = (const self_type& __o);
    self_type& operator = (self_type&& __o);

    explicit operator bool() const;

private:
    friend class bit_resource<_STp>;

    basic_bit(storage_type* __ptr, level_type __lev);
};

using bit = basic_bit<unsigned int>;

}

#endif
