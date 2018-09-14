#ifndef _POL_BIT_TCC
#define _POL_BIT_TCC 1

namespace polaris
{

template<typename _STp>
basic_bit<_STp>::
basic_bit()
    : _M_ptr{nullptr}
{}

template<typename _STp>
basic_bit<_STp>::
basic_bit(const self_type& __o)
    : _M_ptr{new storage_type{*__o._M_data}}, _M_lev{__o._M_lev}
{}

template<typename _STp>
basic_bit<_STp>::
basic_bit(self_type&& __o)
    : _M_ptr{std::move(__o._M_data)}, _M_lev{std::move(__o._M_lev)}
{ __o._M_data = nullptr; }

template<typename _STp>
basic_bit<_STp>::
basic_bit(bool __data)
    : _M_ptr{global_bit_resource<_STp>()->allocate(_M_lev)}
{}

template<typename _STp>
basic_bit<_STp>::
basic_bit(storage_type* __ptr, level_type __lev)
    : _M_ptr{__ptr}, _M_lev{__lev}
{}

template<typename _STp>
basic_bit<_STp>&
basic_bit<_STp>::
operator = (bool __data)
{
    this->_M_ptr->set(this->_M_lev, __data);
}

}

#endif /* _POL_BIT_TCC */
