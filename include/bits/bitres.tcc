#ifndef _POL_BITRES_TCC
#define _POL_BITRES_TCC 1

namespace polaris
{

template<typename _Tp>
bit_usage<_Tp>::
bit_usage(storage_type* __data)
    : _M_data{__data}, _M_count{}
{}

template<typename _Tp>
bool
bit_usage<_Tp>::
set(level_type __n)
{
    if (_M_count & (count_type{true} << __n))
        return false;

    _M_count |= (count_type{true} << __n);
    return true;
}

template<typename _Tp>
bool
bit_usage<_Tp>::
reset(level_type __n)
{
    if (!(_M_count & (count_type{true} << __n)))
        return false;

    _M_count &= ~(count_type{true} << __n);
    return true;
}

template<typename _Tp>
bool
bit_usage<_Tp>::
get(level_type __n) const
{
    return _M_count & (count_type{1} << __n);
}

template<typename _Tp>
bool
bit_usage<_Tp>::
full() const
{
    return this->_M_count == static_cast<unsigned char>(-1);
}

template<typename _Tp>
bool
bit_usage<_Tp>::
get_any(level_type& __n)
{
    if (this->full()) return false;
    unsigned char __tmp{this->_M_count};
    __n = 0;
    while (true)
    {
        if (!(__tmp & 1))
        {
            this->set(__n);
            break;
        }
        ++__n; __tmp >>= 1;
    }
    return true;
}

template<typename _Tp>
basic_bit_view<_Tp>
bit_usage<_Tp>::
get_any_v()
{
    bit_view_type __res;
    if (this->full()) return __res;
    size_type __i{};
    for (; __i < bitof<_Tp>(); ++__i)
        if (!this->get(__i))
        {
            this->set(__i);
            break;
        }
    return bit_view_type{this->storage(), __i / char_bit, __i % char_bit};
}

template<typename _Tp>
basic_bit_storage<_Tp>*
bit_usage<_Tp>::
storage() const
{
    return this->_M_data.get();
}

template<typename _Tp>
basic_bit_view<_Tp>
bit_resource<_Tp>::
allocate_v()
{
    for (usage_type& __e : this->_M_chunk)
        if (!__e.full())
            return __e.get_any_v();
    this->_M_chunk.push_back(usage_type{new storage_type});
    return this->_M_chunk.back().get_any_v();
}

template<typename _Tp>
void
bit_resource<_Tp>::
deallocate_v(bit_view_type __v)
{
    for (usage_type& __e : this->_M_chunk)
        if (__e.storage() == __v.storage())
            __e.reset(__v.byte() * char_bit + __v.bit());
}

template<typename _Tp>
void
bit_resource<_Tp>::
deallocate(bit_type* __ptr)
{
    if (!__ptr->_M_ptr) return;
    for (usage_type& __e : this->_M_chunk)
        if (__ptr->_M_ptr == __e.storage())
            __e.reset(__ptr->_M_lev);
}

template<typename _Tp>
basic_bit<_Tp>*
bit_resource<_Tp>::
allocate()
{
    for (usage_type& __e : this->_M_chunk)
        if (!__e.full())
        {
            unsigned int __n;
            __e.get_any(__n);
            return new bit_type{__e.storage(), __n};
        }

    this->_M_chunk.push_back(usage_type{new storage_type});
    unsigned __n;
    usage_type& __e{this->_M_chunk.back()};
    __e.get_any(__n);
    return new bit_type{__e.storage(), __n};
}

template<typename _Tp>
basic_bit_storage<_Tp>*
bit_resource<_Tp>::
allocate(level_type& __n)
{
    for (std::shared_ptr<usage_type>& __e : this->_M_chunk)
        if (!__e->full())
        {
            __e->get_any(__n);
            return __e->storage();
        }

    this->_M_chunk.push_back(std::shared_ptr<usage_type>{new usage_type{new storage_type}});
    std::shared_ptr<usage_type>& __e{this->_M_chunk.back()};
    __e->get_any(__n);
    return __e->storage();
}

template<typename _Tp = unsigned int>
bit_resource<_Tp>*
global_bit_resource()
{
    using _Res_t = bit_resource<_Tp>;
    static std::shared_ptr<_Res_t> __res{new _Res_t};
    return __res.get();
}

}

#endif /* _POL_BITRES_TCC */
