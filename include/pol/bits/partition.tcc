#ifndef _POL_PARTITION_TCC
#define _POL_PARTITION_TCC 1

namespace polaris
{

template<typename _Tp, typename _Func>
partition<_Tp, _Func>::
partition()
    : _M_data{}, _M_calc{}, _M_mark{}, _M_bsize{}, _M_func{}
{}

template<typename _Tp, typename _Func>
partition<_Tp, _Func>::
~partition() noexcept
{}

template<typename _Tp, typename _Func>
size_t
partition<_Tp, _Func>::
size() const
{
    return this->_M_data.size();
}

template<typename _Tp, typename _Func>
size_t
partition<_Tp, _Func>::
bucket_size() const
{
    return this->_M_bsize;
}

template<typename _Tp, typename _Func>
size_t
partition<_Tp, _Func>::
bucket_count() const
{
    return this->_M_data.size() / this->_M_bsize;
}

template<typename _Tp, typename _Func>
std::vector<_Tp>&
partition<_Tp, _Func>::
data()
{
    return this->_M_data;
}

template<typename _Tp, typename _Func>
void
partition<_Tp, _Func>::
bucket_resize(size_type __size)
{
    this->_M_bsize = __size;
    this->_M_calc.resize(this->_M_data.size() / this->bucket_count());
    this->_M_mark.resize(this->_M_data.size() / this->bucket_count());
    // TODO...
}

template<typename _Tp, typename _Func>
size_t
partition<_Tp, _Func>::
bucket_index(size_type __pos) const
{
    return __pos / this->_M_bsize;
}

template<typename _Tp, typename _Func>
size_t
partition<_Tp, _Func>::
bucket_begin(size_type __pos) const
{
    return bucket_index(__pos) * this->_M_bsize;
}

template<typename _Tp, typename _Func>
size_t
partition<_Tp, _Func>::
bucket_end(size_type __pos) const
{
    return bucket_index(__pos) * this->_M_bsize + this->_M_bsize;
}

template<typename _Tp, typename _Func>
bool
partition<_Tp, _Func>::
is_bucket_range(size_type __begin, size_type __end) const
{
    return this->bucket_index(__begin) == this->bucket_index(--__end);
}

template<typename _Tp, typename _Func>
_Tp
partition<_Tp, _Func>::
find(size_type __pos) const
{
    return this->_M_func(this->_M_data[__pos], this->_M_mark \
        [this->bucket_index(__pos)]);
}

template<typename _Tp, typename _Func>
_Tp
partition<_Tp, _Func>::
find(size_type __begin, size_type __end) const
{
    _Tp __ans{};

    if (is_bucket_range(__begin, __end))
    {
        for (size_type __i = __begin; __i < __end; ++__i)
            __ans = this->_M_func(__ans, this->find(__i));
    }
    else
    {
        for (size_type __i = __begin; __i < this->bucket_end(__begin); ++__i)
            __ans = this->_M_func(__ans, this->find(__i));
        for (size_type __b = this->bucket_index(this->bucket_end(__begin)); \
                __b < this->bucket_index(this->bucket_begin(__end)); ++__b)
            __ans = this->_M_func(__ans, this->_M_calc[__b]);
        for (size_type __i = this->bucket_begin(__end); __i < __end; ++__i)
            __ans = this->_M_func(__ans, this->find(__i));
    }

    return __ans;
}

template<typename _Tp, typename _Func>
void
partition<_Tp, _Func>::
modify(size_type __pos, value_type __x)
{
    this->_M_data[__pos] = this->_M_func(this->_M_data[__pos], __x);
    this->_M_calc[this->bucket_index(__pos)] = this->_M_func \
        (this->_M_calc[this->bucket_index(__pos)], __x);
}

template<typename _Tp, typename _Func>
void
partition<_Tp, _Func>::
modify(size_type __begin, size_type __end, value_type __x)
{
    if (this->is_bucket_range(__begin, __end))
    {
        for (size_type __i = __begin; __i < __end; ++__i)
            this->modify(__i, __x);
    }
    else
    {
        for (size_type __i = __begin; __i < this->bucket_end(__begin); ++__i)
            this->modify(__i, __x);
        for (size_type __b = this->bucket_index(this->bucket_end(__begin)); \
                __b < this->bucket_index(this->bucket_begin(__end)); ++__b)
            this->_M_mark[this->bucket_index(__b)] = this->_M_func \
                (this->_M_mark[this->bucket_index(__b)], __x);
        for (size_type __i = this->bucket_begin(__end); __i < __end; ++__i)
            this->modify(__i, __x);
    }
}

}

#endif
