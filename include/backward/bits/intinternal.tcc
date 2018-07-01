#ifndef _POL_INTINTERNAL_TCC
#define _POL_INTINTERNAL_TCC 1

#include <cassert>
#include <limits>
#include <type_traits>
#include <cmath>
#include <iostream>

namespace polaris
{

template<typename _FloatingPoint, bool _Cond =
	std::is_floating_point<_FloatingPoint>::value>
struct _Int_data_size_fp_cfg
{
	static_assert(_Cond, "need a floating-point type");
	typedef void type;
	static constexpr size_t value = 0;
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
	_Int_data_type* __desttmp = __dest;
	size_t __ntmp = __n;
#if __STDEXT_DEBUG
	assert(__n > 0);
#endif
	do
	{
		*__desttmp++ = __f;
	}
    while (--__ntmp);
}

void __zero(_Int_data_type* __dest, size_t __n)
{
#if __STDEXT_DEBUG
	assert(__n >= 0);
#endif
	if (__n != 0)
	__fill(__dest, __n, _Int_data_type(0));
}

// Bugs fixed!!
// TODO: Move into intdetail.tcc
int
__extract_double (_Int_data_type* rp, double d)
{
  long exp;
  unsigned sc;

  unsigned /*long*/ int manh, manl;

  /* BUGS

     1. Should handle Inf and NaN in IEEE specific code.
     2. Handle Inf and NaN also in default code, to avoid hangs.
     3. Generalize to handle all GMP_LIMB_BITS >= 32.
     4. This lits is incomplete and misspelled.
   */

#if __STDEXT_DEBUG
  assert(d >= 0.0);
#endif

  if (d == 0.0)
    {
      __zero(rp, _Int_data_size_fp<double>);
      return 0;
    }

    /* Unknown (or known to be non-IEEE) double format.  */
    exp = 0;
    if (d >= 1.0)
      {
	assert(d * 0.5 != d);

	while (d >= 32768.0)
	  {
	    d *= (1.0 / 65536.0);
	    exp += 16;
	  }
	while (d >= 1.0)
	  {
	    d *= 0.5;
	    exp += 1;
	  }
      }
    else if (d < 0.5)
      {
	while (d < (1.0 / 65536.0))
	  {
	    d *=  65536.0;
	    exp -= 16;
	  }
	while (d < 0.5)
	  {
	    d *= 2.0;
	    exp -= 1;
	  }
      }

    d *= (4.0 * ((unsigned /*long*/ int) 1 << (_Int_data_bits - 2)));

    manh = d;
    manl = (d - manh) * (4.0 * ((unsigned /*long*/ int) 1 << (_Int_data_bits - 2)));

  sc = (unsigned) (exp + 64 * _Int_data_bits) % _Int_data_bits;

  /* We add something here to get rounding right.  */
  exp = (exp + 64 * _Int_data_bits) / _Int_data_bits - 64 * _Int_data_bits / _Int_data_bits + 1;

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

void
set_d (_Int_base* r, double d)
{
  bool negative;
  _Int_data_type tp[_Int_data_size_fp<double>];
  _Int_data_type* rp;
  size_t rn;
  
  if (std::isinf(d) || std::isnan(d))
  {
  	throw conversion_error();
  }
  
  negative = d < 0;
  d = std::abs(d);

  rn = __extract_double (tp, d);

  if (r->_M_capacity < rn)
    r->_M_realloc(rn);

  /*if (rn <= 0)
    rn = 0;*/

  rp = r->_M_dataplus;

  switch (rn)
    {
    default:
      __zero(rp, rn - _Int_data_size_fp<double>);
      rp += rn - _Int_data_size_fp<double>;
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

void
set_si (_Int_base* dest, signed long int val)
{
  size_t size;
  _Int_data_type vl;

  //vl = (_Int_data_type)std::abs(static_cast<unsigned long int>(val));
  vl = (_Int_data_type)static_cast<unsigned long int>(val);

  dest->_M_dataplus[0] = vl;
  size = vl != 0;

  dest->_M_length= val >= 0 ? size : -size;
}

void
set_ui (_Int_base* dest, unsigned long int val)
{
  size_t size;
  size = sizeof(val)/sizeof(_Int_data_type);

	if ((val>>(sizeof(val)*__CHAR_BIT__-1))&&dest->_M_capacity<=size)
	{
		dest->_M_realloc(++size);
		dest->_M_dataplus[1]=0;
	}

  dest->_M_dataplus[0] = val;
  dest->_M_length = size;
}

}

#endif
