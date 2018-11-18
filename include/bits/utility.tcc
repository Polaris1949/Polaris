#ifndef _POL_UTILITY_TCC
#define _POL_UTILITY_TCC 1

#include <cassert>
#include <climits>
#include <cmath>

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
inline constexpr size_t byteof()
{
    return sizeof(_Tp);
}

template<typename _Tp>
inline constexpr size_t byteof(const _Tp& __x)
{
    return sizeof(__x);
}

template<typename _Tp>
inline constexpr size_t bitof()
{
    return sizeof(_Tp) * CHAR_BIT;
}

template<typename _Tp>
inline constexpr size_t bitof(const _Tp& __x)
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
_Tp powmod(_Tp __x, _Tp __y, _Tp __mod)
{
    return _Tp{std::pow(__x, __y)} % __mod;
}

template<typename _Tp>
_Tp qpow(_Tp __x, _Tp __y)
{
    pol::expect(__y >= 0, "exponent should be an non-negative integer");

    _Tp __res{1};
    _Tp __tmp{__x};

    while (__y)
    {
        if (__y & 1) __res *= __tmp;
        __tmp *= __tmp;
        __y >>= 1;
    }

    return __res;
}

template<typename _Tp>
_Tp qpowmod(_Tp __x, _Tp __y, _Tp __mod)
{
    pol::expect(__y >= 0, "exponent should be a non-negative integer");

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

template<typename _Tp, typename _Cont>
_Tp& exqpowmod(_Tp __x, _Tp __y, _Tp __mod, _Cont& __c)
{
    pol::expect(__y >= 0, "exponent should be a non-negative integer");
    if (__x == 0 && __y != 0) return __c[__y] = 0;
    return __exqpowmod_impl(__x % __mod, __y, __mod, __c) %= __mod;
}

template<typename _Tp, typename _Cont>
_Tp& __exqpowmod_impl(_Tp __x, _Tp __y, _Tp __mod, _Cont& __c)
{
    _Tp& __res{__c[__y]};
    if (__res != 0) return __res;
    if (__y == 0) return __res = 1;
    _Tp __tmp{__exqpowmod_impl(__x, __y >> 1, __mod, __c) % __mod};
    __res = __tmp * __tmp % __mod;
    if (__y & 1) __res = __res * __x % __mod;
    return __res;
}

}

#endif
