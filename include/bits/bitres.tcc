#ifndef _POL_BITRES_TCC
#define _POL_BITRES_TCC 1

namespace polaris
{

template<typename _STp>
bit_usage<_STp>::
bit_usage(storage_type* __data)
    : _M_data{__data}, _M_count{}
{}

template<typename _STp>
bool
bit_usage<_STp>::
set(level_type __n)
{
    if (_M_count & (count_type{true} << __n))
        return false;

    _M_count |= (count_type{true} << __n);
    return true;
}

template<typename _STp>
bool
bit_usage<_STp>::
reset(level_type __n)
{
    if (!(_M_count & (count_type{true} << __n)))
        return false;

    _M_count &= ~(count_type{true} << __n);
    return true;
}

template<typename _STp>
bool
bit_usage<_STp>::
full() const
{
    return this->_M_count == ~((unsigned char){0});
}

template<typename _STp>
bool
bit_usage<_STp>::
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

template<typename _STp>
basic_bit_storage<_STp>*
bit_usage<_STp>::
storage() const
{
    return this->_M_data.get();
}

template<typename _STp>
basic_bit<_STp>*
bit_resource<_STp>::
allocate()
{
    for (std::shared_ptr<usage_type>& __e : this->_M_chunk)
        if (!__e->full())
        {
            unsigned int __n;
            __e->get_any(__n);
            return new bit_type{__e->storage(), __n};
        }

    this->_M_chunk.push_back(std::shared_ptr<usage_type>{new usage_type{new storage_type}});
    unsigned __n;
    std::shared_ptr<usage_type>& __e{this->_M_chunk.back()};
    __e->get_any(__n);
    return new bit_type{__e->storage(), __n};
}

template<typename _STp>
basic_bit_storage<_STp>*
bit_resource<_STp>::
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

template<typename _STp = unsigned int>
bit_resource<_STp>*
global_bit_resource()
{
    static std::shared_ptr<bit_resource<_STp>> __res;
    return __res.get();
}

}

#endif /* _POL_BITRES_TCC */
