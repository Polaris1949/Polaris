#ifndef _POL_UTILITY_H
#define _POL_UTILITY_H 1

namespace polaris
{

template<typename _Tp, typename =
    decltype(std::declval<_Tp>() == std::declval<_Tp>())>
bool fully_equal_to(_Tp&& __x, _Tp&& __y);

template<typename _Tp, typename _Up>
bool fully_equal_to(_Tp&& __x, _Up&& __y);

template<typename _Tp>
inline _Tp&
inc(_Tp& __x);

template<typename _Tp>
inline _Tp&
dec(_Tp& __x);

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

template<typename _Tp, typename _Pred>
inline const _Tp&
return_if_pred(const _Tp& __x, const _Tp& __y, const _Pred& __p);

template<typename _Seq>
inline typename _Seq::value_type
random_choice(const _Seq& __s);

inline bool
prob_choice(unsigned __x);

template<typename _Tp>
constexpr size_t byteof();

template<typename _Tp>
constexpr size_t byteof(const _Tp& __x);

template<typename _Tp>
constexpr size_t bitof();

template<typename _Tp>
constexpr size_t bitof(const _Tp& __x);

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
_Tp powmod(_Tp __x, _Tp __y, _Tp __mod);

template<typename _Tp>
_Tp qpow(_Tp __x, _Tp __y);

template<typename _Tp>
_Tp qpowmod(_Tp __x, _Tp __y, _Tp __mod);

template<typename _Tp, typename _Cont>
_Tp& exqpowmod(_Tp __x, _Tp __y, _Tp __mod, _Cont& __c);

template<typename _Tp, typename _Cont>
_Tp& __exqpowmod_impl(_Tp __x, _Tp __y, _Tp __mod, _Cont& __c);

}

#endif
