#include "vwrap.h"

namespace polaris
{

template<typename _Tp>
value_wrapper<_Tp>::
value_wrapper()
	: _M_data()
{
}

template<typename _Tp>
value_wrapper<_Tp>::
value_wrapper(const value_type& __x)
	: _M_data(__x)
{
}

template<typename _Tp>
value_wrapper<_Tp>::
~value_wrapper()
{
}

template<typename _Tp>
_Tp
value_wrapper<_Tp>::
data() const
{
	return _M_data;
}

template<typename _Tp>
_Tp&
value_wrapper<_Tp>::
data()
{
	return _M_data;
}

template<typename _Tp>
value_wrapper<_Tp>::
operator value_type() const
{
	return _M_data;
}

template<typename _Tp>
value_wrapper<_Tp>::
operator reference()
{
	return _M_data;
}

template<typename _T>
std::istream&
operator >> (std::istream& __in, value_wrapper<_T>& __x)
{
	return (__in >> __x._M_data);
}

template<typename _T>
std::ostream&
operator << (std::ostream& __out, const value_wrapper<_T>& __x)
{
	return (__out << __x._M_data);
}

}
