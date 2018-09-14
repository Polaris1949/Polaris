#ifndef _POL_INTFWD_TCC
#define _POL_INTFWD_TCC 1

namespace polaris
{

namespace __int_detail
{

constexpr size_t data_byte = sizeof(data_type);
constexpr size_t data_bit = char_bit * data_byte;
constexpr data_type data_min =
	std::numeric_limits<data_type>::min();
constexpr data_type data_max =
	std::numeric_limits<data_type>::max();

template<typename _FloatingPoint, bool _Cond =
	std::is_floating_point<_FloatingPoint>::value>
struct fp_size_data
{
	static_assert(_Cond, "need a floating-point type");
};

template<typename _FloatingPoint>
struct fp_size_data<_FloatingPoint, true>
{
	typedef _FloatingPoint type;
	static constexpr size_t value =
		(std::numeric_limits<_FloatingPoint>::digits + data_bit - 2)
		/ data_bit + 1;
};

}

constexpr size_t _Int_data_byte = __int_detail::data_byte;
constexpr size_t _Int_data_bit = __int_detail::data_bit;
constexpr size_t _Int_data_min = __int_detail::data_min;
constexpr size_t _Int_data_max = __int_detail::data_max;

template<typename _FP>
constexpr size_t _Int_fp_size = __int_detail::fp_size_data<_FP>::value;

}

#endif
