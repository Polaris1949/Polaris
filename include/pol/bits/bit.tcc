#ifndef _POL_BIT_TCC
#define _POL_BIT_TCC 1

namespace polaris
{

template<typename _Tp>
basic_bit<_Tp>::
basic_bit()
    : _M_ptr{nullptr}
{}

template<typename _Tp>
basic_bit<_Tp>::
basic_bit(const self_type& __o)
    : _M_ptr{new storage_type{*__o._M_ptr}}, _M_lev{__o._M_lev}
{}

template<typename _Tp>
basic_bit<_Tp>::
basic_bit(self_type&& __o)
    : _M_ptr{std::move(__o._M_ptr)}, _M_lev{std::move(__o._M_lev)}
{ __o._M_ptr = nullptr; }

template<typename _Tp>
basic_bit<_Tp>::
basic_bit(bool __data)
//    : _M_ptr{global_bit_resource<_Tp>()->allocate(_M_lev)}
    : basic_bit{global_bit_resource<_Tp>()->allocate_v()}
{}
/*
template<typename _Tp>
basic_bit<_Tp>::
basic_bit(storage_type* __ptr, level_type __lev)
    : _M_ptr{__ptr}, _M_lev{__lev}
{}
*/
template<typename _Tp>
basic_bit<_Tp>::
basic_bit(bit_view_type&& __v)
    : _M_ptr{__v.storage()}, _M_lev{__v.byte() * char_bit + __v.bit()}
{}

template<typename _Tp>
basic_bit<_Tp>::
~basic_bit() noexcept
{ global_bit_resource<>()->deallocate(this); }

template<typename _Tp>
basic_bit<_Tp>&
basic_bit<_Tp>::
operator = (bool __data)
{
    this->_M_ptr->set(this->_M_lev, __data);
}

template<typename _Tp>
basic_bit<_Tp>&
basic_bit<_Tp>::
operator = (const self_type& __o)
{
    this->_M_ptr = new storage_type{*__o._M_ptr};
    this->_M_lev = __o._M_lev;
}

template<typename _Tp>
basic_bit<_Tp>&
basic_bit<_Tp>::
operator = (self_type&& __o)
{
    this->_M_ptr = std::move(__o._M_ptr);
    this->_M_lev = std::move(__o._M_lev);
    __o._M_ptr = nullptr;
}

template<typename _Tp>
basic_bit_view<_Tp>::
basic_bit_view()
    : _M_storage{}, _M_byte{}, _M_bit{}
{}

template<typename _Tp>
basic_bit_view<_Tp>::
basic_bit_view(storage_type* __sto, size_type __byte, size_type __bit)
    : _M_storage{__sto}, _M_byte{__byte}, _M_bit{__bit}
{}

template<typename _Tp>
basic_bit_storage<_Tp>*
basic_bit_view<_Tp>::
storage() const
{ return this->_M_storage; }

template<typename _Tp>
std::size_t
basic_bit_view<_Tp>::
byte() const
{ return this->_M_byte; }

template<typename _Tp>
std::size_t
basic_bit_view<_Tp>::
bit() const
{ return this->_M_bit; }

template<typename _Tp>
std::size_t
basic_bit_view<_Tp>::
level() const
{ return this->_M_byte * char_bit + this->_M_bit; }

}

#endif /* _POL_BIT_TCC */
