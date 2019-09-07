#ifndef _POL_PROB_TCC
#define _POL_PROB_TCC 1

#include <algorithm>
#include <iostream>

namespace polaris
{

template<typename _Tp>
card_pool<_Tp>::
card_pool()
    : card_pool(value_type{})
{}

template<typename _Tp>
card_pool<_Tp>::
card_pool(const value_type& __d)
    : _M_gen{std::random_device{}()}, _M_def{__d}
{
    this->_M_prob.push_back(0);
    this->_M_value.push_back(__d);
}

template<typename _Tp>
bool
card_pool<_Tp>::
insert(const value_type& __x, double __p)
{
    double __r = this->_M_prob.back() + __p;

    if (__r >= 1.0)
        return false;

    value_type __d = this->_M_value.back();
    this->_M_value.back() = __x;
    this->_M_prob.push_back(__r);
    this->_M_value.push_back(__d);
    return true;
}

template<typename _Tp>
void
card_pool<_Tp>::
set_default(const value_type& __x)
{
    this->_M_value.back() = __x;
}

template<typename _Tp>
const _Tp&
card_pool<_Tp>::
take()
{
    double __c = std::generate_canonical<double, 10>(this->_M_gen);
    //std::cerr << "! " << __c << '\n';
    size_t __n = std::distance(this->_M_prob.begin(), --std::upper_bound(
        this->_M_prob.begin(), this->_M_prob.end(), __c));
    if (__n >= this->_M_value.size()) return this->_M_value.back();
    return this->_M_value[__n];
}

}

#endif
