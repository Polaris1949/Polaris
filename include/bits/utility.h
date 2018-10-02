#ifndef _POL_UTILITY_H
#define _POL_UTILITY_H 1

#pragma GCC system_header

#include "exception.h"

namespace polaris
{

template<typename _Tp, typename =
	decltype(std::declval<_Tp>() == std::declval<_Tp>())>
bool fully_equal_to(_Tp&& __x, _Tp&& __y);

template<typename _Tp, typename _Up>
bool fully_equal_to(_Tp&& __x, _Up&& __y);

template<typename _Tp>
[[deprecated]] inline _Tp&
inc(_Tp& __x);

template<typename _Tp>
[[deprecated]] inline _Tp&
dec(_Tp& __x);

template<typename _Tp>
[[deprecated]] inline _Tp
inc_copy(const _Tp& __x);

template<typename _Tp>
[[deprecated]] inline _Tp
dec_copy(const _Tp& __x);

template<typename _Tp>
inline _Tp&
flip(_Tp& __x);

template<typename _T>
inline const _T&
return_if(bool __c, const _T& __t, const _T& __f);

#if _POLLIB_OLD
template<typename _T, typename _E>
inline const _T&
return_if(bool __c, const exception_wrapper<_E>& __t, const _T& __f);

template<typename _T, typename _E>
inline const _T&
return_if(bool __c, const _T& __t, const exception_wrapper<_E>& __f);
#endif

template<typename _Tp, typename _Pred>
inline const _Tp&
return_if_pred(const _Tp& __x, const _Tp& __y, const _Pred& __p);

template<typename _Seq>
inline typename _Seq::value_type
random_choice(const _Seq& __s);

inline bool
prob_choice(unsigned __x);

template<typename _Tp>
inline constexpr size_t byteof();

template<typename _Tp>
inline constexpr size_t byteof(const _Tp& __x);

template<typename _Tp>
inline constexpr size_t bitof();

template<typename _Tp>
inline constexpr size_t bitof(const _Tp& __x);

template<typename _Tp>
constexpr const _Tp&
min_of(const _Tp& __x);

template<typename _Tp, typename... _Args>
constexpr const _Tp&
min_of(const _Tp& __x, const _Args&... __args);

template<typename _Tp>
constexpr const _Tp&
max_of(const _Tp& __x);

template<typename _Tp, typename... _Args>
constexpr const _Tp&
max_of(const _Tp& __x, const _Args&... __args);

template<typename _Tp>
constexpr _Tp
sum(const _Tp& __x);

template<typename _Tp, typename... _Args>
constexpr auto
sum(const _Tp& __x, const _Args&... __args);

template<typename... _Args>
constexpr auto
average(const _Args&... __args);

template<typename _Tp>
_Tp qpow(_Tp __x, _Tp __y, _Tp __mod);

}

#endif
