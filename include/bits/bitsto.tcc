#ifndef _POL_BITSTO_TCC
#define _POL_BITSTO_TCC 1

namespace polaris
{

template<typename _Tp>
basic_bit_storage<_Tp>::
basic_bit_storage(const storage_type& __data)
    : _M_data{__data}
{}

template<typename _Tp>
basic_bit_storage<_Tp>::
basic_bit_storage(storage_type&& __data)
    : _M_data{std::move(__data)}
{}

template<typename _Tp>
bool
basic_bit_storage<_Tp>::
empty() const
{
    return this->_M_count == 0u;
}

template<typename _Tp>
bool
basic_bit_storage<_Tp>::
full() const
{
    return this->_M_count == storage_type{-1};
}

template<typename _Tp>
void
basic_bit_storage<_Tp>::
clear()
{
    for (level_type __i{}; __i < bitof<storage_type>(); ++__i)
        this->unlock(__i);
}

template<typename _Tp>
_Tp*
basic_bit_storage<_Tp>::
data() const
{
    return std::addressof(this->_M_data);
}

template<typename _Tp>
bool
basic_bit_storage<_Tp>::
set(level_type __n, bool __x)
{
    if (__n >= bitof<storage_type>())
        return false;

    if (__x) this->_M_data |= (storage_type{true} << __n);
    else this->_M_data &= ~(storage_type{true} << __n);
    return true;
}

template<typename _Tp>
bool
basic_bit_storage<_Tp>::
get(level_type __n) const
{
    return this->_M_data & (storage_type{true} << __n);
}

template<typename _Tp>
bool
basic_bit_storage<_Tp>::
is_locked(level_type __n) const
{
    return this->_M_count & (storage_type{true} << __n);
}

template<typename _Tp>
bool
basic_bit_storage<_Tp>::
lock(level_type __n)
{
    if (this->is_locked(__n))
        return false;
    this->_M_count |= (storage_type{true} << __n);
    return true;
}

template<typename _Tp>
bool
basic_bit_storage<_Tp>::
unlock(level_type __n)
{
    if (!this->is_locked(__n))
        return false;
    this->_M_count &= ~(storage_type{true} << __n);
    return true;
}

template<typename _Tp>
unsigned char
basic_bit_storage<_Tp>::
obtain()
{
    for (level_type __i{}; __i < bitof<storage_type>(); ++__i)
        if (this->lock(__i)) return __i;
    throw std::runtime_error{"basic_bit_storage::obtain(): "
        "no available resource"};
}

template<typename _Tp>
void
basic_bit_storage<_Tp>::
release(level_type __n)
{
    if (this->unlock(__n)) return;
    throw std::runtime_error{"basic_bit_storage::release(): "
        "no such active resource"};
}

}

#endif /* _POL_BITSTO_TCC */
