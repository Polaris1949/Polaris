#ifndef _POL_INTEGER_TCC
#define _POL_INTEGER_TCC 1

#include <cstring>
#include <limits>
#include <type_traits>
#include <cmath>

namespace polaris
{
/*
template<typename _T>
integer::size_type
integer::
_M_nlength(_T __n) // _T must be an integer type.
{
	if (__n == _T())
	{
		return 0;
	}
	else
	{
		size_type __pos = 0;
		
		if (__n > _T())
		{
			for (size_type __i = 0; __i < sizeof(_T); ++__i)
			{
				if (reinterpret_cast<unsigned char*>(&__n)[__i]
					!= static_cast<unsigned char>(0u))
				{
					__pos = __i;
				}
			}
		}
		else
		{
			for (size_type __i = 0; __i < sizeof(_T); ++__i)
			{
				if (reinterpret_cast<unsigned char*>(&__n)[__i]
					!= static_cast<unsigned char>(~0u))
				{
					__pos = __i;
				}
			}
		}
		
		return ++__pos;
	}
}

template<typename _T>
void
integer::
_M_construct(_T __n, bool __int)//__int: is_integer
{
	if (__int)
	{
		size_type __len = _M_nlength(__n);
		
		if (_S_sign_bit(reinterpret_cast<const char*>(&__n)[__len - 1]))
		{
			++__len;
		}
		
		_M_dataplus = static_cast<data_type*>(_M_do_get_allocator()
			->allocate(__len));
		std::memcpy(_M_dataplus, &__n, __len);
		_M_length = __len;
	}
	else
	{
		unsigned long long __temp = __n; // ??? TODO...
		
		if (std::isinf(__n))
		{
			throw conversion_error();
		}
		
		size_type __len = _M_nlength(__temp);
		_M_dataplus = static_cast<data_type*>(_M_do_get_allocator()
			->allocate(__len));
		std::memcpy(_M_dataplus, &__temp, __len);
		_M_length = __len;
	}
}

template<typename _T>
bool
integer::
_S_sign_bit(_T __n)
{
	return __n & (_T(1) << (std::numeric_limits<_T>::digits
		- std::is_unsigned<_T>::value));
}

_Int_data_type*
integer::
_M_data() const
{
	return _M_dataplus;
}

void
integer::
_M_basic_swap(const integer& __arg)
{
	// TODO...
}
*/
/**
 *  @brief  Default constructor creates an integer that equals to zero.
 */
integer::
integer()
	: _Base()
{
	//__detail::__integer::init(this);
	// Move to _Int_base.
}

/**
 *  @brief  Construct integer with value of @a __arg.
 *  @param __arg  Source integer number.
 */
integer::
integer(int __arg)
	: _Base(__arg)
{
}

/**
 *  @brief  Construct integer with value of @a __arg.
 *  @param __arg  Source integer number.
 */
integer::
integer(unsigned int __arg)
	: _Base(__arg)
{
}

/**
 *  @brief  Construct integer with value of @a __arg.
 *  @param __arg  Source integer number.
 */
integer::
integer(long int __arg)
	: _Base(__arg)
{
}

/**
 *  @brief  Construct integer with value of @a __arg.
 *  @param __arg  Source integer number.
 */
integer::
integer(unsigned long int __arg)
	: _Base(__arg)
{
}

/**
 *  @brief  Construct integer with value of @a __arg.
 *  @param __arg  Source integer number.
 */
integer::
integer(long long int __arg)
	: _Base(__arg)
{
}

/**
 *  @brief  Construct integer with value of @a __arg.
 *  @param __arg  Source integer number.
 */
integer::
integer(unsigned long long int __arg)
	: _Base(__arg)
{
}

/**
 *  @brief  Construct integer with value of @a __arg.
 *  @param __arg  Source floating-point number.
 *  @throw  conversion_error  If @a __arg is an invalid number.
 */
integer::
integer(float __arg)
	: _Base(__arg)
{
}

/**
 *  @brief  Construct integer with value of @a __arg.
 *  @param __arg  Source floating-point number.
 *  @throw  conversion_error  If @a __arg is an invalid number.
 */
integer::
integer(double __arg)
	: _Base(__arg)
{
}

/**
 *  @brief  Construct integer with value of @a __arg.
 *  @param __arg  Source floating-point number.
 *  @throw  conversion_error  If @a __arg is an invalid number.
 */
integer::
integer(long double __arg)
	: _Base(__arg)
{
}

/**
 *  @brief  Construct integer with value of @a __arg.
 *  @param __arg  Source string.
 *  @throw  invalid_argument_error  If @a __arg is an invalid string.
 */
integer::
integer(const char* __arg)
	: _Base(__arg)
{
}

/**
 *  @brief  Construct integer with value of @a __arg by using base radix with
 *          value of @a __radix.
 *  @param __arg  Source string.
 *  @param __radix  Base radix.
 *  @throw  invalid_argument_error  If value of @a __radix is invalid or @a
 *          __arg is an invalid string.
 */
integer::
integer(const char* __arg, radix_type __radix)
	: _Base(__arg, __radix)
{
}

/**
 *  @brief  Construct integer with value of @a __arg.
 *  @param __arg  Source string.
 *  @throw  invalid_argument_error  If @a __arg is an invalid string.
 */
integer::
integer(const std::string& __arg)
	: _Base(__arg)
{
}

/**
 *  @brief  Construct integer with value of @a __arg by using base radix with
 *          value of @a __radix.
 *  @param __arg  Source string.
 *  @param __radix  Base radix.
 *  @throw  invalid_argument_error  If value of @a __radix is invalid or @a
 *          __arg is an invalid string.
 */
integer::
integer(const std::string& __arg, radix_type __radix)
	: _Base(__arg, __radix)
{
}

/**
 *  @brief  Construct integer with copy of value of @a __arg.
 *  @param __arg  Source integer.
 */
integer::
integer(const integer& __arg) // TODO: exception/failure
	: _Base(_Base(__arg))
{
	/*
	_M_do_get_allocator()->deallocate(_M_dataplus);
	_M_dataplus = (data_type*)_M_do_get_allocator()
		->allocate(__arg._M_length);
	_M_length = __arg._M_length;
	std::memcpy(_M_dataplus, __arg._M_dataplus, _M_length);
	*/
}

/**
 *  @brief  Destroy the integer instance.
 */
// TODO: Move to _Int_base
integer::
~integer()
{
	do_get_allocator()->deallocate(_M_dataplus);
}

/**
 *  @return  false if %integer is zero, true otherwise.
 */
integer::
operator boolean() const
{
	return _M_boolean();
}

/**
 *  @return  Default allocator.
 */
integer_allocator*
integer::
get_default_allocator()
{
	return _S_get_default_allocator();
}

/**
 *  @return  Allocator of this integer.
 */
integer_allocator*
integer::
get_allocator() const
{
	return _M_get_allocator();
}

integer*
integer::
create() const
{
	return (integer*)do_create();
}

integer*
integer::
clone() const
{
	return (integer*)do_clone();
}

integer&
integer::
normalize()
{
	return (integer&)do_normalize();
}

integer&
integer::
swap(integer& __arg)
{
	return do_swap(__arg);
}

integer_allocator*
integer::
do_get_allocator() const
{
	return _M_get_allocator();
}

integer*
integer::
do_create() const
{
	return (integer*)_M_create();
}

integer*
integer::
do_clone() const
{
	return (integer*)_M_clone();
}

integer&
integer::
do_normalize()
{
	return *this;
}

integer&
integer::
do_swap(integer& __arg)
{
	if (do_get_allocator() != __arg.do_get_allocator())
	{
		integer __temp(__arg);
		__arg._M_assign(*this);
		_M_basic_swap(__temp);
	}
	else
	{
		_M_basic_swap(__arg);
		__arg.do_normalize();
	}
	
	return *this;
}

int
integer::
sign() const
{
	// TODO: More quick way? ...
	if (_M_length)
	{
		if (_M_sign) return 1;
		else return -1;
	}
	else return 0;
	//return *this == integer() ? 0 : (*this > integer() ? 1 : -1);
}

bool
integer::
is_zero() const
{
	// TODO: More quick way? ...
	return _M_is_zero();
}

bool
integer::
is_odd() const
{
	return get_bit(0);
}

std::size_t
integer::
highest_bit() const
{
	if (is_zero())
		throw invalid_argument_error()._M_msg("integer::highest_bit(): ");
	// TODO: find index of the last bit that is true...
	return 0;
}

std::size_t
integer::
lowest_bit() const
{
	if (is_zero())
		throw invalid_argument_error()._M_msg("integer::lowest_bit(): ");
	// TODO: find index of the first bit that is true...
	return 0;
}

bool
integer::
get_bit(size_type __pos) const
{
	if (__pos >= size()) return false;
	// TODO...
	return false;
}

integer&
integer::
set_bit(size_type __pos, bool __x)
{
	// TODO...
	return *this;
}

integer
integer::
get_sub(size_type __pos, size_type __n) const
{
	// TODO...
	return integer();
}

std::size_t
integer::
size() const
{
	return _M_length;
}

_Int_reference
integer::
operator[] (size_type __pos)
{
	return reference(this, __pos);
}

const _Int_reference
integer::
operator[] (size_type __pos) const
{
	return reference(const_cast<_Int_base*>((const _Int_base*)this), __pos);
}

integer&
integer::
negate()
{
	return do_negate();
}

integer&
integer::
abs()
{
	return do_abs();
}

integer&
integer::
operator++ ()
{
	return increment();
}

integer&
integer::
operator-- ()
{
	return decrement();
}

integer&
integer::
operator = (const integer& __x)
{
	return assign(__x);
}

integer&
integer::
operator += (const integer& __x)
{
	return add(__x);
}

integer&
integer::
operator -= (const integer& __x)
{
	return subtract(__x);
}

integer&
integer::
operator *= (const integer& __x)
{
	return multiply(__x);
}

integer&
integer::
operator /= (const integer& __x)
{
	if (__x == integer())
		throw division_by_zero()._M_msg("integer::operator /= () (): ");
	return divide(__x);
}

integer&
integer::
operator %= (const integer& __x)
{
	if (__x == integer())
		throw division_by_zero()._M_msg("integer::operator /= () (): ");
	return remainder(__x);
}

integer&
integer::
operator <<= (size_type __n)
{
	return shift_left(__n);
}

integer&
integer::
operator >>= (size_type __n)
{
	return shift_right(__n);
}

integer&
integer::
operator &= (const integer& __x)
{
	return bitwise_and(__x);
}

integer&
integer::
operator |= (const integer& __x)
{
	return bitwise_or(__x);
}

integer&
integer::
operator ^= (const integer& __x)
{
	return bitwise_xor(__x);
}

_Int_data
integer::
get_element(size_type __pos) const
{
	if (__pos >= size()) return 0;
	// TODO...
	return 0;
}

integer&
integer::
set_element(size_type __pos, data_type __x)
{
	// TODO...
	return *this;
}

integer&
integer::
do_negate()
{
	// TODO...
	return *this;
}

integer&
integer::
do_abs()
{
	// TODO...
	return *this;
}

integer&
integer::
increment()
{
	// TODO...
	return *this;
}

integer&
integer::
decrement()
{
	// TODO...
	return *this;
}

integer&
integer::
assign(const integer& __x)
{
	// TODO...
	return *this;
}

integer&
integer::
add(const integer& __x)
{
	// TODO...
	return *this;
}

integer&
integer::
subtract(const integer& __x)
{
	// TODO...
	return *this;
}

integer&
integer::
multiply(const integer& __x)
{
	// TODO...
	return *this;
}

integer&
integer::
divide(const integer& __x)
{
	// TODO...
	return *this;
}

integer&
integer::
remainder(const integer& __x)
{
	// TODO...
	return *this;
}

integer&
integer::
shift_left(size_type __n)
{
	// TODO...
	return *this;
}

integer&
integer::
shift_right(size_type __n)
{
	// TODO...
	return *this;
}

integer&
integer::
bitwise_and(const integer& __x)
{
	// TODO...
	return *this;
}

integer&
integer::
bitwise_or(const integer& __x)
{
	// TODO...
	return *this;
}

integer&
integer::
bitwise_xor(const integer& __x)
{
	// TODO...
	return *this;
}

integer
operator++ (integer& __x, int)
{
	integer __temp(__x);
	++__x;
	return __temp;
}

integer
operator-- (integer& __x, int)
{
	integer __temp(__x);
	--__x;
	return __temp;
}

integer
operator+ (const integer& __x)
{
	return __x;
}

integer
operator- (const integer& __x)
{
	return integer(__x).negate();
}

integer
operator + (const integer& __x, const integer& __y)
{
	return integer(__x) += __y;
}

integer
operator - (const integer& __x, const integer& __y)
{
	return integer(__x) -= __y;
}

integer
operator * (const integer& __x, const integer& __y)
{
	return integer(__x) *= __y;
}

integer
operator / (const integer& __x, const integer& __y)
{
	return integer(__x) /= __y;
}

integer
operator % (const integer& __x, const integer& __y)
{
	return integer(__x) %= __y;
}

integer
operator << (const integer& __x, integer::size_type __n)
{
	return integer(__x) <<= __n;
}

integer
operator >> (const integer& __x, integer::size_type __n)
{
	return integer(__x) >>= __n;
}

integer
operator & (const integer& __x, const integer& __y)
{
	return integer(__x) &= __y;
}

integer
operator | (const integer& __x, const integer& __y)
{
	return integer(__x) |= __y;
}

integer
operator ^ (const integer& __x, const integer& __y)
{
	return integer(__x) ^= __y;
}

bool
operator == (const integer& __lhs, const integer& __rhs)
{
	// TODO...
	return false;
}

bool
operator != (const integer& __lhs, const integer& __rhs)
{
	return !(__lhs == __rhs);
}

bool
operator < (const integer& __lhs, const integer& __rhs)
{
	// TODO...
	return false;
}

bool
operator <= (const integer& __lhs, const integer& __rhs)
{
	return __lhs < __rhs || __lhs == __rhs;
}

bool
operator > (const integer& __lhs, const integer& __rhs)
{
	return !(__lhs <= __rhs);
}

bool
operator >= (const integer& __lhs, const integer& __rhs)
{
	return !(__lhs < __rhs);
}

}

#endif
