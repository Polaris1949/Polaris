#ifndef _POL_UTILITY_H_
#define _POL_UTILITY_H_ 1

#pragma GCC system_header

#include "exception.h"

namespace polaris
{

template<typename _Tp>
inline _Tp
inc_copy(const _Tp& __x);

template<typename _Tp>
inline _Tp
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

}

#endif
