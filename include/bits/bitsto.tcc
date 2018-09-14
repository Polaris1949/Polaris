#ifndef _POL_BITSTO_TCC
#define _POL_BITSTO_TCC 1

namespace polaris
{

template<typename _STp>
basic_bit_storage<_STp>::
basic_bit_storage(const storage_type& __data)
    : _M_data{__data}
{}

template<typename _STp>
basic_bit_storage<_STp>::
basic_bit_storage(storage_type&& __data)
    : _M_data{std::move(__data)}
{}

template<typename _STp>
bool
basic_bit_storage<_STp>::
set(level_type __lev, bool __val)
{
    if (__lev >= bitof<storage_type>())
        return false;

    if (__val) this->_M_data |= (storage_type{true} << __lev);
    else this->_M_data &= ~(storage_type{true} << __lev);
    return true;
}

template<typename _STp>
bool
basic_bit_storage<_STp>::
get(level_type __lev) const
{
    return this->_M_data & (storage_type{true} << __lev);
}

}

#endif /* _POL_BITSTO_TCC */
