#ifndef _POL_PROBPOOL_TCC
#define _POL_PROBPOOL_TCC 1

namespace pol
{

template<typename _Tp>
prn_pool<_Tp>::
prn_pool()
    : _M_gen(std::random_device()()), _M_data()
{ }

template<typename _Tp>
void
prn_pool<_Tp>::
insert(const value_type& __x)
{
    this->_M_data.push_back(__x);
}

template<typename _Tp>
_Tp
prn_pool<_Tp>::
take()
{
    std::uniform_int_distribution<size_t> __dis(0, this->_M_data.size() - 1);
    return this->_M_data[__dis(this->_M_gen)];
}

template<typename _Tp, typename _Up>
prq_pool<_Tp, _Up>::
prq_pool()
    : _M_gen(std::random_device()()), _M_data(), _M_sum()
{ }

template<typename _Tp, typename _Up>
void
prq_pool<_Tp, _Up>::
insert(const value_type& __x, prob_type __p)
{
    this->_M_data.push_back(prq_data(__x, this->_M_sum));
    this->_M_sum += __p;
}

template<typename _Tp, typename _Up>
_Tp
prq_pool<_Tp, _Up>::
take()
{
    std::uniform_int_distribution<prob_type> __dis(0, this->_M_sum - 1);
    prob_type __c = __dis(this->_M_gen);
    return (--std::upper_bound(this->_M_data.begin(), this->_M_data.end(), __c))->value;
}

template<typename _Tp, typename _Up>
prf_pool<_Tp, _Up>::
prf_pool()
    : _M_gen(std::random_device()()), _M_data(), _M_sum()
{ }

template<typename _Tp, typename _Up>
void
prf_pool<_Tp, _Up>::
insert(const value_type& __x, prob_type __p)
{
    if (this->_M_sum + __p > prob_type(1.0))
        throw std::runtime_error("prf_pool::insert");

    this->_M_data.push_back(prf_data(__x, this->_M_sum));
    this->_M_sum += __p;
}

template<typename _Tp, typename _Up>
inline bool
prf_pool<_Tp, _Up>::
full() const
{ return this->_M_sum == prob_type(1.0); }

template<typename _Tp, typename _Up>
inline
prf_pool<_Tp, _Up>::
operator bool() const
{ return this->full(); }

template<typename _Tp, typename _Up>
void
prf_pool<_Tp, _Up>::
check() const
{
    if (!this->full())
        throw std::runtime_error("prf_pool::check");
}

template<typename _Tp, typename _Up>
void
prf_pool<_Tp, _Up>::
complete(const value_type& __x)
{
    if (this->full()) return;
    this->_M_data.push_back(prf_data(__x, this->_M_sum));
    this->_M_sum = 1.0;
}

template<typename _Tp, typename _Up>
_Tp
prf_pool<_Tp, _Up>::
take()
{
    prob_type __c = std::generate_canonical<prob_type, 10>(this->_M_gen);
    return (--std::upper_bound(this->_M_data.begin(), this->_M_data.end(), __c))->value;
}

}

#endif /* _POL_PROBPOOL_TCC */
