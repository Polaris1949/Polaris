#ifndef _POL_INTFWD_H
#define _POL_INTFWD_H 1

#include <stdexcept>
#include <limits>
#include <type_traits>

namespace polaris
{

namespace __int_detail
{

#if POL_POOR_MEMORY
using data_type = uint8_t;
using exdata_type = uint16_t;
#else
using data_type = uint32_t;
using exdata_type = uint64_t;
#endif

using radix_type = size_t;

template<typename, bool>
struct fp_size_data;

}

typedef __int_detail::data_type _Int_data;
typedef _Int_data* _Int_pointer;
typedef __int_detail::exdata_type _Int_exdata;
typedef __int_detail::radix_type _Int_radix;

template<size_t __x, size_t __y>
struct __mp_div_floor
{
    constexpr static bool is_exact = (__x % __y) == 0;
    constexpr static size_t value = __x / __y;
};

template<size_t __x, size_t __y>
struct __mp_div_ceil
{
    constexpr static bool is_exact = (__x % __y) == 0;
    constexpr static size_t value = __x / __y + !is_exact;
};

template<typename _Tp>
struct integer_size
{
    constexpr static size_t value = __mp_div_ceil<sizeof(_Tp), \
        sizeof(_Int_data)>::value;
};

template<typename _Tp>
constexpr size_t integer_size_v = integer_size<_Tp>::value;

struct _Int_exception;

struct _Int_allocator;

struct _Int_reference;

struct _Int_base;

// @integer_allocator
class integer_allocator;

// @integer
class integer;

// @unsigned_integer
class unsigned_integer;

/*
// @modular_integer
template<int _Tag, class _ModT = integer>
    class modular_integer;

// @allocated_integer
template<int _Tag>
    class allocated_integer;

// @allocated_unsigned_integer
template<int _Tag>
    class allocated_unsigned_integer;

// @allocated_modular_integer
template<int _Tag, class _ModT = allocated_integer<_Tag> >
    class allocated_modular_integer;
*/

}

#endif
