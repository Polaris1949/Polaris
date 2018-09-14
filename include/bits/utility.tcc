#ifndef _POL_UTILITY_TCC_
#define _POL_UTILITY_TCC_ 1

#pragma GCC system_header

#include <cassert>
#include <climits>
#include "utility.h"
#include "exception.tcc"

namespace polaris
{

template<typename _Tp>
inline _Tp
inc_copy(const _Tp& __x)
{
	_Tp __y(__x);
	return ++__y;
}

template<typename _Tp>
inline _Tp
dec_copy(const _Tp& __x)
{
	_Tp __y(__x);
	return --__y;
}

template<typename _Tp>
inline _Tp&
flip(_Tp& __x)
{
	return __x = ~__x;
}

template<typename _T>
const _T&
return_if(bool __c, const _T& __t, const _T& __f)
{
	return (__c ? __t : __f);
}

#if _POLLIB_OLD
template<typename _T, typename _E>
const _T&
return_if(bool __c, const exception_wrapper<_E>& __t, const _T& __f)
{
	if (__c) __t();
	else return __f;
}

template<typename _T, typename _E>
const _T&
return_if(bool __c, const _T& __t, const exception_wrapper<_E>& __f)
{
	if (__c) return __t;
	else __f();
}
#endif

template<typename _Tp, typename _Pred>
const _Tp&
return_if_pred(const _Tp& __x, const _Tp& __y, const _Pred& __p)
{
	return __p(__x, __y) ? __x : __y;
}

template<typename _Seq>
inline typename _Seq::value_type
random_choice(const _Seq& __s)
{
	return __s[rand() % __s.size()];
}

inline bool
prob_choice(unsigned __x)
{
	struct _Helper
	{
		typedef unsigned value_type;

		size_t size() const
		{
			return 100;
		}

		size_t operator[] (unsigned __n) const
		{
			return __n;
		}
	};

	_Helper __gen;
	return random_choice(__gen) < __x;
}

template<typename _Tp>
constexpr size_t byteof()
{
	return sizeof(_Tp);
}

template<typename _Tp>
constexpr size_t byteof(const _Tp& __x)
{
	return sizeof(__x);
}

template<typename _Tp>
constexpr size_t bitof()
{
	return sizeof(_Tp) * CHAR_BIT;
}

template<typename _Tp>
constexpr size_t bitof(const _Tp& __x)
{
	return sizeof(__x) * CHAR_BIT;
}

}

#endif
