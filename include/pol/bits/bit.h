#ifndef _POL_BIT_H
#define _POL_BIT_H 1

namespace polaris
{

template<typename _Tp>
class basic_bit
{
public:
    using storage_type = basic_bit_storage<_Tp>;
    using level_type = typename storage_type::level_type;
    using self_type = basic_bit<_Tp>;
    using resource_type = bit_resource<_Tp>;
    using bit_view_type = basic_bit_view<_Tp>;

private:
    storage_type* _M_ptr;
    //resource_type* _M_res;
    level_type _M_lev;

public:
    basic_bit();
    basic_bit(const self_type& __o);
    basic_bit(self_type&& __o);
    explicit basic_bit(bool __data);
    explicit basic_bit(storage_type* __ptr);

    ~basic_bit() noexcept;

    self_type& operator = (bool __data);
    self_type& operator = (const self_type& __o);
    self_type& operator = (self_type&& __o);

    explicit operator bool() const;

private:
    friend class bit_resource<_Tp>;

    //basic_bit(storage_type* __ptr, level_type __lev);
    explicit basic_bit(bit_view_type&& __v);
};

using bit = basic_bit<unsigned int>;

template<typename _Tp>
class basic_bit_view
{
public:
    using storage_type = basic_bit_storage<_Tp>;
    using size_type = std::size_t;

private:
    storage_type* _M_storage;
    size_type _M_byte;
    size_type _M_bit;

public:
    basic_bit_view();
    basic_bit_view(storage_type* __sto, size_type __byte, size_type __bit);

    storage_type* storage() const;
    size_type byte() const;
    size_type bit() const;
    size_type level() const;
};

}

#endif
