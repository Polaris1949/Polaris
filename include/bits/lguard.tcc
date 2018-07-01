#ifndef _POL_BITS_LGUARD_TCC
#define _POL_BITS_LGUARD_TCC

#include <polaris/bits/lguard.h>

namespace polaris
{

template<typename _Tp>
literal_guard<_Tp>::
literal_guard() noexcept
	: _M_storage()
{
}

template<typename _Tp>
literal_guard<_Tp>::
literal_guard(value_type __arg) noexcept
	: _M_storage(__arg)
{
}

template<typename _Tp>
literal_guard<_Tp>&
literal_guard<_Tp>::
operator = (value_type __arg) noexcept
{
	return (_M_storage = __arg, *this);
}

template<typename _Tp>
literal_guard<_Tp>::
operator value_type&() noexcept
{
	return _M_storage;
}

template<typename _Tp>
literal_guard<_Tp>::
operator value_type() const noexcept
{
	return _M_storage;
}

template<typename _T>
literal_guard<_T>
make_lguard(_T __arg)
{
	return literal_guard<_T>(__arg);
}

#if __cplusplus >= 201103L

inline literal_guard<unsigned long long>
operator"" _lg(unsigned long long __arg)
{
	return literal_guard<unsigned long long>(__arg);
}

#endif

}

#endif
