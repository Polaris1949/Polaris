#ifndef _POL_INTDETIAL_TCC
#define _POL_INTDETIAL_TCC 1

#include <cstdarg>
#include <limits>
#include <cmath>
#include <cassert>

namespace polaris
{
namespace __detail
{
namespace __integer
{

template<typename _FloatingPoint, bool _Cond =
	std::is_floating_point<_FloatingPoint>::value>
struct _Int_data_size_fp_cfg
{
	static_assert(_Cond, "need a floating-point type");
};

template<typename _FloatingPoint>
struct _Int_data_size_fp_cfg<_FloatingPoint, true>
{
	typedef _FloatingPoint type;
	static constexpr size_t value =
		(std::numeric_limits<_FloatingPoint>::digits + _Int_data_bits - 2)
		/ _Int_data_bits + 1;
};

template<typename _FloatingPoint>
constexpr size_t _Int_data_size_fp =
	_Int_data_size_fp_cfg<_FloatingPoint>::value;

void __fill(_Int_data_type* __dest, size_t __n, _Int_data_type __f)
{
#if __STDEXT_DEBUG
	assert(__n > 0);
#endif
	do
	{
		*__dest++ = __f;
	}
    while (--__n);
}

void __zero(_Int_data_type* __dest, size_t __n)
{
#if __STDEXT_DEBUG
	assert(__n >= 0);
#endif
	if (__n != 0)
	__fill(__dest, __n, _Int_data_type(0));
}

// Use code from GMP.
template<typename _FloatingPoint, typename = typename
	std::enable_if<std::is_floating_point<_FloatingPoint>::value>::type>
size_t
__extract_fp(_Int_data_type* rp, _FloatingPoint d)
{
	typedef _FloatingPoint _FP;
	
	size_t exp;
	unsigned sc;
	_Int_data_type manh, manl;
	
	/* BUGS
	
	1. Should handle Inf and NaN in IEEE specific code.
	2. Handle Inf and NaN also in default code, to avoid hangs.
	3. Generalize to handle all GMP_LIMB_BITS >= 32.
	4. This lits is incomplete and misspelled.
	*/
	
#if __STDEXT_DEBUG
	assert(d >= (_FP)0.0);
#endif
	
	if (d == (_FP)0.0)
	{
		__zero(rp, _Int_data_size_fp<_FloatingPoint>);
		return 0;
	}
	
	/* Unknown (or known to be non-IEEE) double format.  */
	exp = 0;
	if (d >= (_FP)1.0)
	{
		assert(d * (_FP)0.5 != d);
		
		while (d >= (_FP)32768.0)
		{
			d *= ((_FP)1.0 / (_FP)65536.0);
			exp += 16;
		}
		while (d >= (_FP)1.0)
		{
			d *= (_FP)0.5;
			exp += 1;
		}
	}
	else if (d < (_FP)0.5)
	{
		while (d < ((_FP)1.0 / (_FP)65536.0))
		{
			d *=  (_FP)65536.0;
			exp -= 16;
		}
		while (d < (_FP)0.5)
		{
			d *= (_FP)2.0;
			exp -= 1;
		}
	}
	
	d *= ((_FP)4.0 * ((_Int_data_type) 1 << (_Int_data_bits - 2)));
	
	manh = d;
	manl = (d - manh) * (4.0 * ((_Int_data_type) 1 << (_Int_data_bits - 2)));
	
	sc = (unsigned) (exp + 64 * _Int_data_bits) % _Int_data_bits;
	
	/* We add something here to get rounding right.  */
	exp = (exp + 64 * _Int_data_bits) / _Int_data_bits
		- 64 * _Int_data_bits / _Int_data_bits + 1;
	
	if (sc != 0)
	{
		rp[2] = manh >> (_Int_data_bits - sc);
		rp[1] = (manh << sc) | (manl >> (_Int_data_bits - sc));
		rp[0] = manl << sc;
	}
	else
	{
		rp[2] = manh;
		rp[1] = manl;
		rp[0] = 0;
		exp--;
	}
	
	return exp;
}

inline void
init(_Int_base* __x)
{
	__x->_M_capacity = 1;
	__x->_M_dataplus = (_Int_data_type*)__x->do_get_allocator()->allocate(1);
	__x->_M_length = 0;
}

inline void
clear(_Int_base* __x)
{
	__x->do_get_allocator()->deallocate(__x->_M_dataplus);
}

// @set_fp
template<typename _FloatingPoint, typename = typename
	std::enable_if<std::is_floating_point<_FloatingPoint>::value>::type>
void
set_fp(_Int_base* r, _FloatingPoint d)
{
	typedef _FloatingPoint _FP;
	
	bool negative;
	_Int_data_type tp[_Int_data_size_fp<_FP>];
	_Int_data_type* rp;
	size_t rn;
	
	if (std::isinf(d) || std::isnan(d))
	{
		throw conversion_error();
	}

	negative = d < 0;
	d = std::abs(d);
	
	rn = __extract_fp (tp, d);
	
	if (r->_M_capacity < rn)
	r->_M_realloc(rn);
	
	rp = r->_M_dataplus;
	
	switch (rn)
	{
	default:
		__zero(rp, rn - _Int_data_size_fp<_FP>);
		rp += rn - _Int_data_size_fp<_FP>;
		/* fall through */
	case 3:
		rp[2] = tp[2], rp[1] = tp[1], rp[0] = tp[0];
		break;
	case 2:
		rp[1] = tp[2], rp[0] = tp[1];
		break;
	case 1:
		rp[0] = tp[2];
		break;
	case 0:
		break;
	}
	
	r->_M_length = rn;
	
	if (negative)
	{
		r->do_negate();
	}
}

template<typename _SignedInt, typename = typename
	std::enable_if<std::is_signed<_SignedInt>::value>::type>
void
set_sint(_Int_base* dest, _SignedInt val)
{
	size_t size;
	_Int_data_type vl;
	bool neg=val<0;
	if (neg) val=-val;
	size = sizeof(_SignedInt) / sizeof(_Int_data_type);
	
	if (size <= 1)
	{
		vl = static_cast<_Int_data_type>(val);
		dest->_M_dataplus[0] = vl;
		dest->_M_length = 1;
	}
	else
	{
		if (dest->_M_capacity < size)
		{
			dest->_M_realloc(size);
		}
		
		for (size_t i=0; i<size; ++i)
		{
			vl = static_cast<_Int_data_type>(val
				>>(sizeof(_Int_data_type)*__CHAR_BIT__*i));
			dest->_M_dataplus[i]=vl;
		}
		
		dest->_M_length=size;
	}
	
	if (neg)
	{
		dest->do_negate();
	}
}

template<typename _UnsignedInt, typename = typename
	std::enable_if<std::is_unsigned<_UnsignedInt>::value>::type>
void
set_uint(_Int_base* dest, _UnsignedInt val)
{
	size_t size;
	_Int_data_type vl;
	
	size = sizeof(_UnsignedInt) / sizeof(_Int_data_type);
	
	if (size <= 1)
	{
		vl = static_cast<_Int_data_type>(val);
		dest->_M_dataplus[0] = vl;
		dest->_M_length = 1;
	}
	else
	{
		if (dest->_M_capacity < size)
		{
			dest->_M_realloc(size);
		}
		
		for (size_t i=0; i<size; ++i)
		{
			vl = static_cast<_Int_data_type>(val
				>>(sizeof(_Int_data_type)*__CHAR_BIT__*i));
			dest->_M_dataplus[i]=vl;
		}
		
		dest->_M_length=size;
	}
}

}
}
}

#endif
