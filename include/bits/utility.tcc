#ifndef _POL_UTILITY_TCC
#define _POL_UTILITY_TCC 1

#pragma GCC system_header

#include <cassert>
#include <climits>
#include "utility.h"
#include "exception.tcc"

namespace polaris
{

template<typename _Tp, typename =
	decltype(std::declval<_Tp>() == std::declval<_Tp>())>
bool fully_equal_to(_Tp&& __x, _Tp&& __y)
{
	return __x == __y;
}

template<typename _Tp, typename _Up>
bool fully_equal_to(_Tp&& __x, _Up&& __y)
{
	return false;
}

template<typename _Tp>
inline _Tp&
inc(_Tp& __x)
{
	return ++__x;
}

template<typename _Tp>
inline _Tp&
dec(_Tp& __x)
{
	return --__x;
}

template<typename _Tp>
inline _Tp
inc_copy(const _Tp& __x)
{
	_Tp __y{__x};
	return ++__y;
}

template<typename _Tp>
inline _Tp
dec_copy(const _Tp& __x)
{
	_Tp __y{__x};
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

template<typename _Tp>
constexpr const _Tp&
min_of(const _Tp& __x)
{
	return __x;
}

template<typename _Tp, typename... _Args>
constexpr const _Tp&
min_of(const _Tp& __x, const _Args&... __args)
{
	return std::min(__x, min_of(__args...));
}

template<typename _Tp>
constexpr const _Tp&
max_of(const _Tp& __x)
{
	return __x;
}

template<typename _Tp, typename... _Args>
constexpr const _Tp&
max_of(const _Tp& __x, const _Args&... __args)
{
	return std::max(__x, max_of(__args...));
}

template<typename _Tp>
constexpr _Tp
sum(const _Tp& __x)
{
	return __x;
}

template<typename _Tp, typename... _Args>
constexpr auto
sum(const _Tp& __x, const _Args&... __args)
{
	return __x + sum(__args...);
}

template<typename... _Args>
constexpr auto
average(const _Args&... __args)
{
	return sum(__args...) / sizeof...(__args);
}

template<typename _Tp>
_Tp qpow(_Tp __x, _Tp __y, _Tp __mod)
{
	_Tp __res{1};
	_Tp __tmp{__x % __mod};

	while (__y)
	{
		if (__y & 1) __res = __res * __tmp % __mod;
		__tmp = __tmp * __tmp % __mod;
		__y >>= 1;
	}

	return __res;
}

}

#endif
