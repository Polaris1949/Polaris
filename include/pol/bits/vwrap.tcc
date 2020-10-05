#ifndef _POL_VWRAP_TCC
#define _POL_VWRAP_TCC 1

namespace pol
{

template<typename _Tp>
var_wrapper<_Tp>::
var_wrapper()
    : _M_data()
{
}

template<typename _Tp>
var_wrapper<_Tp>::
var_wrapper(const value_type& __x)
    : _M_data(__x)
{
}

template<typename _Tp>
var_wrapper<_Tp>::
~var_wrapper()
{
}

template<typename _Tp>
_Tp
var_wrapper<_Tp>::
data() const
{
    return _M_data;
}

template<typename _Tp>
_Tp&
var_wrapper<_Tp>::
data()
{
    return _M_data;
}

template<typename _Tp>
var_wrapper<_Tp>::
operator value_type() const
{
    return _M_data;
}

template<typename _Tp>
var_wrapper<_Tp>::
operator reference()
{
    return _M_data;
}

template<typename _T>
std::istream&
operator >> (std::istream& __in, var_wrapper<_T>& __x)
{
    return (__in >> __x._M_data);
}

template<typename _T>
std::ostream&
operator << (std::ostream& __out, const var_wrapper<_T>& __x)
{
    return (__out << __x._M_data);
}

}

#endif
