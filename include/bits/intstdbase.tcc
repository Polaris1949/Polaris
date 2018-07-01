#ifndef _POL_INTSTDBASE_TCC
#define _POL_INTSTDBASE_TCC 1

#include <cmath>

namespace polaris
{

_Int_allocator
_Int_stdbase::
_S_default_alloc{};

_Int_stdbase::
_Int_stdbase()
{
	_M_initialize();
}

_Int_stdbase::
_Int_stdbase(int __arg)
{
	_M_initialize();
	_M_set_si(__arg);
}

_Int_stdbase::
_Int_stdbase(unsigned int __arg)
{
	_M_initialize();
	_M_set_ui(__arg);
}

_Int_stdbase::
_Int_stdbase(long int __arg)
{
	_M_initialize();
	_M_set_si(__arg);
}

_Int_stdbase::
_Int_stdbase(unsigned long int __arg)
{
	_M_initialize();
	_M_set_ui(__arg);
}

_Int_stdbase::
_Int_stdbase(long long int __arg)
{
	_M_initialize();
	_M_set_si(__arg);
}

_Int_stdbase::
_Int_stdbase(unsigned long long int __arg)
{
	_M_initialize();
	_M_set_ui(__arg);
}

_Int_stdbase::
_Int_stdbase(float __arg)
{
	_M_initialize();
	_M_set_fp(__arg);
}

_Int_stdbase::
_Int_stdbase(double __arg)
{
	_M_initialize();
	_M_set_fp(__arg);
}

_Int_stdbase::
_Int_stdbase(long double __arg)
{
	_M_initialize();
	_M_set_fp(__arg);
}

_Int_stdbase::
_Int_stdbase(const char* __arg)
{
	_M_initialize();
	// TODO...
}

_Int_stdbase::
_Int_stdbase(const char* __arg, _Radix __radix)
{
	_M_initialize();
	// TODO...
}

_Int_stdbase::
_Int_stdbase(const std::string& __arg)
{
	_M_initialize();
	// TODO...
}

_Int_stdbase::
_Int_stdbase(const std::string& __arg, _Radix __radix)
{
	_M_initialize();
	// TODO...
}

_Int_stdbase::
_Int_stdbase(const _Int_stdbase& __arg)
{
	_M_initialize(__arg._M_length);
	_M_assign(__arg);
}

_Int_stdbase::
~_Int_stdbase()
{
	_M_get_allocator()->deallocate(_M_dataplus);
}

bool
_Int_stdbase::
_M_boolean() const
{
	return _M_length;
}

_Int_pointer
_Int_stdbase::
_M_begin() const
{
	return _M_dataplus;
}

_Int_pointer
_Int_stdbase::
_M_end() const
{
	return _M_dataplus + _M_length;
}

_Int_data
_Int_stdbase::
_M_front() const
{
	return *_M_begin();
}

_Int_data
_Int_stdbase::
_M_back() const
{
	return *(_M_end() - 1);
}

void
_Int_stdbase::
_M_initialize(size_t __n)
{
	if (__n)
	{
		_M_dataplus = (_Int_pointer)_M_get_allocator()->allocate(__n);
		
		if (!_M_dataplus)
		{
			throw std::bad_alloc();
		}
	}
	else
	{
		_M_dataplus = 0;
	}
	
	_M_capacity = __n;
	_M_length = 0;
}

void
_Int_stdbase::
_M_realloc(size_t __n)
{
	_M_dataplus = (_Int_pointer)_M_get_allocator()
		->reallocate(_M_dataplus, __n);
	
	if (!_M_dataplus)
	{
		throw std::bad_alloc();
	}
	
	_M_capacity = __n;
}

void
_Int_stdbase::
_M_shrink()
{
	_M_realloc(_M_length);
}

void
_Int_stdbase::
_M_reserve(size_t __n)
{
	if (_M_capacity < __n)
	{
		_M_realloc(__n);
		_M_length = __n;
	}
}

void
_Int_stdbase::
_M_reserve(size_t __n, _Int_data __arg)
{
	if (_M_capacity < __n)
	{
		_M_realloc(__n);
		
		_Int_pointer __ptr = _M_dataplus + _M_length;
		_M_length = __n;
		const _Int_pointer __sto = _M_dataplus + _M_length;
		
		while (__ptr < __sto)
		{
			*__ptr = __arg;
			++__ptr;
		}
	}
}

void
_Int_stdbase::
_M_request(size_t __n)
{
	if (this->_M_capacity < __n)
	{
		size_t __tmp = this->_M_capacity;
		while (__tmp < __n) __tmp <<= 1;
		this->_M_realloc(__tmp);
	}
	
	this->_M_length = __n;
}

template<typename _FP>
size_t
_Int_stdbase::
_S_extract_fp(_Int_data* __v, _FP __fp)
{
	size_t __exp;
	unsigned __sc;
	_Int_data __manh, __manl;
	
	assert_debug(__fp >= _FP(), "_S_extract_fp(): "
		"negative floating-point number");
	
	if (__fp == _FP())
	{
		for (size_t __i = 0; __i < _Int_fp_size<_FP>; ++__i)
		{
			__v[__i] = _Int_data();
		}
		
		return 0;
	}
	
	__exp = 0;
	
	if (__fp >= _FP(1))
	{
		assert_always(__fp * _FP(0.5) != __fp);
		
		while (__fp >= _FP(32768))
		{
			__fp *= (_FP(1) / _FP(65536));
			__exp += 16;
		}
		
		while (__fp >= _FP(1))
		{
			__fp *= _FP(0.5);
			++__exp;
		}
	}
	else if (__fp < _FP(0.5))
	{
		while (__fp < (_FP(1) / _FP(65536)))
		{
			__fp *= _FP(65536);
			__exp -= 16;
		}
		
		while (__fp < _FP(0.5))
		{
			__fp *= _FP(2);
			--__exp;
		}
	}
	
	__fp *= (_FP(4) * (_Int_data(1) << (_Int_data_bit - 2)));
	
	__manh = __fp;
	__manl = (__fp - __manh) * (4.0 * (_Int_data(1) << (_Int_data_bit - 2)));
	
	__sc = unsigned(__exp + 64 * _Int_data_bit) % _Int_data_bit;
	
	__exp = (__exp + 64 * _Int_data_bit) / _Int_data_bit
		- 64 * _Int_data_bit / _Int_data_bit + 1;
	
	if (__sc)
	{
		__v[2] = __manh >> (_Int_data_bit - __sc);
		__v[1] = (__manh << __sc) | (__manl >> (_Int_data_bit - __sc));
		__v[0] = __manl << __sc;
	}
	else
	{
		__v[2] = __manh;
		__v[1] = __manl;
		__v[0] = 0;
		--__exp;
	}
	
	return __exp;
}

void
_Int_stdbase::
_M_basic_increment()
{
	// TODO...
	_M_basic_plus(1);
}

void
_Int_stdbase::
_M_basic_decrement()
{
	// TODO...
	_M_basic_minus(1);
}

void
_Int_stdbase::
_M_basic_swap(_Int_stdbase& __arg)
{
	std::swap(this->_M_dataplus, __arg._M_dataplus);
	std::swap(this->_M_capacity, __arg._M_capacity);
	std::swap(this->_M_length, __arg._M_length);
	std::swap(this->_M_sign, __arg._M_sign);
}

void
_Int_stdbase::
_M_basic_plus(const _Int_stdbase& __arg)
{
	_Int_pointer __lhs = this->_M_begin();
	_Int_pointer __lst = this->_M_end();
	_Int_pointer __rhs = __arg._M_begin();
	_Int_pointer __rst = __arg._M_end();
	_Int_exdata __tmp = 0;
	
	while (__lhs < __lst && __rhs < __rst)
	{
		__tmp += _Int_exdata(*__lhs) + _Int_exdata(*__rhs);
		*__lhs = __tmp & _Int_exdata(~_Int_data(0));
		__tmp >>= _Int_data_bit;
		++__lhs; ++__rhs;
	}
	
	while (__lhs < __lst)
	{
		if (__tmp)
		{
			__tmp += _Int_exdata(*__lhs);
			*__lhs = __tmp & _Int_exdata(~_Int_data(0));
		}
		else return;
	}
	
	while (__rhs < __rst)
	{
		this->_M_request(__arg._M_length + 1);
		__lst = this->_M_end();
		
		while (__lhs < __lst && __rhs < __rst)
		{
			__tmp += _Int_exdata(*__rhs);
			*__lhs = __tmp & _Int_exdata(~_Int_data(0));
			__tmp >>= _Int_data_bit;
			++__lhs; ++__rhs;
		}
		
		if (__tmp)
		{
			*__lhs = __tmp;
		}
		else
		{
			--this->_M_length;
			return;
		}
	}
	
	if (__tmp)
	{
		this->_M_request(this->_M_length + 1);
		*__lhs = __tmp;
	}
}

// Requires: *this >= __arg
void
_Int_stdbase::
_M_basic_minus(const _Int_stdbase& __arg)
{
	_Int_pointer __lhs = this->_M_begin();
	_Int_pointer __lst = this->_M_end();
	_Int_pointer __rhs = __arg._M_begin();
	_Int_pointer __rst = __arg._M_end();
	_Int_exdata __tmp = 0;
	
	while (__lhs < __lst && __rhs < __rst)
	{
		__tmp += _Int_exdata(*__lhs) - _Int_exdata(*__rhs);
		*__lhs = __tmp & _Int_exdata(~_Int_data(0));
		__tmp >>= _Int_data_bit;
		++__lhs; ++__rhs;
	}
	
	if (__tmp)
	{
		if (__lhs < __lst)
		{
			*__lhs = __tmp;
		}
		
		assert_debug(__rhs == __rst, "_M_basic_minus(): "
				"requirement not satisfied");
	}
	
	if (!this->_M_back())
	{
		--_M_length;
	}
}

void
_Int_stdbase::
_M_basic_multiplies(const _Int_stdbase& __arg)
{
	
}

void
_Int_stdbase::
_M_basic_divides(const _Int_stdbase& __arg)
{
	
}

void
_Int_stdbase::
_M_basic_modulus(const _Int_stdbase& __arg)
{
	
}

_Int_allocator*
_Int_stdbase::
_S_get_default_allocator()
{
	return &_S_default_alloc;
}

_Int_allocator*
_Int_stdbase::
_M_get_allocator() const
{
	return &_S_default_alloc;
}

_Int_stdbase*
_Int_stdbase::
_M_create() const
{
	return new _Int_stdbase();
}

_Int_stdbase*
_Int_stdbase::
_M_clone() const
{
	return new _Int_stdbase(*this);
}

_Int_stdbase&
_Int_stdbase::
_M_normalize()
{
	return *this;
}

void
_Int_stdbase::
_M_swap(_Int_stdbase& __arg)
{
	if (_M_get_allocator() != __arg._M_get_allocator())
	{
		_Int_stdbase __temp(__arg);
		__arg._M_assign(*this);
		_M_basic_swap(__temp);
	}
	else
	{
		_M_basic_swap(__arg);
		__arg._M_normalize();
	}
}

_Int_data
_Int_stdbase::
_M_get_element(size_t __pos) const
{
	if (__pos >= _M_length) return 0;
	return _M_dataplus[__pos];
}

void
_Int_stdbase::
_M_set_element(size_t __pos, _Int_data __x)
{
	if (__pos >= _M_length)
	{
		if (__x != 0)
		{
			_M_request(__pos + 1);
			_M_dataplus[__pos] = __x;
		}
		
		return;
	}
	
	if (__pos == _M_length - 1 && __x == 0)
	{
		_M_shrink();
		return;
	}
	
	_M_dataplus[__pos] = __x;
}

void
_Int_stdbase::
_M_negate()
{
	if (_M_length) _M_sign = !_M_sign;
}

void
_Int_stdbase::
_M_abs()
{
	if (!_M_sign) _M_negate();
}

void
_Int_stdbase::
_M_increment()
{
	if (!_M_length)
	{
		_M_dataplus[_M_length++] = 1;
		return;
	}
	
	if (!_M_sign && _M_dataplus[_M_length - 1] == 1)
	{
		_M_length = 0;
		return;
	}
	
	if (_M_sign)
	{
		_M_basic_increment();
	}
	else
	{
		_M_basic_decrement();
	}
}

void
_Int_stdbase::
_M_decrement()
{
	if (!_M_length)
	{
		_M_dataplus[_M_length++] = 1;
		_M_sign = false;
		return;
	}
	
	if (_M_sign && _M_back() == 1)
	{
		_M_length = 0;
		return;
	}
	
	if (_M_sign)
	{
		_M_basic_decrement();
	}
	else
	{
		_M_basic_increment();
	}
}

void
_Int_stdbase::
_M_assign(const _Int_stdbase& __arg)
{
	_M_request(__arg._M_capacity);
	_M_length = __arg._M_length;
	_M_sign = __arg._M_sign;
	
	_Int_pointer __lhs = _M_begin();
	_Int_pointer __sto = _M_end();
	_Int_pointer __rhs = __arg._M_begin();
	
	while (__lhs < __sto)
	{
		*__lhs = *__rhs;
		++__lhs; ++__rhs;
	}
}

void
_Int_stdbase::
_M_plus(const _Int_stdbase& __arg)
{
	if (!_M_length)
	{
		_M_assign(__arg);
		return;
	}
	
	if (!__arg._M_length)
		return;
	
	if (_M_sign == __arg._M_sign)
	{
		_M_basic_plus(__arg);
	}
	else
	{
		int __cmp = _M_basic_compare(__arg);
		
		if (__cmp == 0)
		{
			_M_length = 0;
			_M_sign = false;
			return;
		}
		
		if (__cmp < 0)
		{
			_M_sign = __arg._M_sign;
			_Int_stdbase __tmp(*this);
			_M_assign(__arg);
			_M_basic_minus(__tmp);
		}
		else
		{
			_M_basic_minus(__arg);
		}
	}
}

void
_Int_stdbase::
_M_minus(const _Int_stdbase& __arg)
{
	_Int_stdbase __tmp(__arg);
	__tmp._M_negate();
	_M_plus(__tmp);
}

template<typename _FP>
void
_Int_stdbase::
_M_set_fp(_FP __fp)
{
	if (std::isinf(__fp) || std::isnan(__fp))
	{
		throw conversion_error()._M_msg("_M_set_fp(): "
			"invalid floating-point number");
	}
	
	bool __neg = __fp < 0;
	_Int_data __v[_Int_fp_size<_FP>];
	size_t __size;
	_Int_data* __ptr;
	
	if (__neg) __fp = -__fp;
	
	__size = _S_extract_fp(__v, __fp);
	
	if (_M_capacity < __size)
	{
		_M_realloc(__size);
	}
	
	__ptr = _M_dataplus;
	
	switch (__size)
	{
		default:
			for (size_t __i = 0; __i < __size - _Int_fp_size<_FP>; ++__i)
			{
				__ptr[__i] = _Int_data();
			}
			
			__ptr += __size - _Int_fp_size<_FP>;
			
		case 3:
			__ptr[2] = __v[2];
			__ptr[1] = __v[1];
			__ptr[0] = __v[0];
			break;
			
		case 2:
			__ptr[1] = __v[2];
			__ptr[0] = __v[1];
			break;
			
		case 1:
			__ptr[0] = __v[2];
			break;
			
		case 0:
			break;
	}
	
	_M_length = __size;
	
	if (__neg)
	{
		_M_negate();
	}
}

template<typename _SI>
void
_Int_stdbase::
_M_set_si(_SI __si)
{
	size_t __size = sizeof(_SI) / sizeof(_Int_data);
	bool __neg = __si < 0;
	_Int_data __v[__size];
	size_t __pos;
	size_t __i = 0;
	
	if (__neg) __si = -__si;
	
	for (__pos = 0; __pos < __size; ++__pos)
	{
		if (__v[__pos] = __si & ~_Int_data())
		{
			__i = __pos;
		}
		
		__si >>= _Int_data_bit;
	}
	
	__pos = ++__i;
	
	if (_M_capacity < __pos)
	{
		_M_realloc(__pos);
	}
	
	for (__i = 0; __i < __pos; ++__i)
	{
		_M_dataplus[__i] = __v[__i];
	}
	
	_M_length = __pos;
	
	if (__neg)
	{
		_M_negate();
	}
}

template<typename _UI>
void
_Int_stdbase::
_M_set_ui(_UI __ui)
{
	size_t __size = sizeof(_UI) / sizeof(_Int_data);
	_Int_data __v[__size];
	size_t __pos;
	size_t __i = 0;
	
	for (__pos = 0; __pos < __size; ++__pos)
	{
		if (__v[__pos] = __ui & ~_Int_data())
		{
			__i = __pos;
		}
		
		__ui >>= _Int_data_bit;
	}
	
	__pos = ++__i;
	
	if (_M_capacity < __pos)
	{
		_M_realloc(__pos);
	}
	
	for (size_t __i = 0; __i < __pos; ++__i)
	{
		_M_dataplus[__i] = __v[__i];
	}
	
	_M_length = __pos;
}

bool
_Int_stdbase::
_M_is_zero() const
{
	return !_M_length;
}

bool
_Int_stdbase::
_M_is_odd() const
{
	return !_M_length && *_M_dataplus;
}

size_t
_Int_stdbase::
_M_size() const
{
	return _M_length;
}

bool
_Int_stdbase::
_M_is_equal_to(const _Int_stdbase& __arg) const
{
	if (_M_sign != __arg._M_sign)
		return false;
	
	if (_M_length != __arg._M_length)
		return false;
	
	_Int_pointer __lhs = _M_dataplus;
	const _Int_pointer __sto = _M_dataplus + _M_length;
	_Int_pointer __rhs = __arg._M_dataplus;
	
	while (__lhs < __sto)
	{
		if (*__lhs == *__rhs)
		{
			++__lhs;
			++__rhs;
		}
		else
		{
			return false;
		}
	}
	
	return true;
}

bool
_Int_stdbase::
_M_is_not_equal_to(const _Int_stdbase& __arg) const
{
	if (_M_sign != __arg._M_sign)
		return true;
	
	if (_M_length != __arg._M_length)
		return true;
	
	_Int_pointer __lhs = _M_dataplus;
	const _Int_pointer __sto = _M_dataplus + _M_length;
	_Int_pointer __rhs = __arg._M_dataplus;
	
	while (__lhs < __sto)
	{
		if (*__lhs == *__rhs)
		{
			++__lhs;
			++__rhs;
		}
		else
		{
			return true;
		}
	}
	
	return false;
}

bool
_Int_stdbase::
_M_is_less_than(const _Int_stdbase& __arg) const
{
	if (_M_sign != __arg._M_sign)
		return _M_sign < __arg._M_sign;
	
	if (_M_length != __arg._M_length)
		return _M_length < __arg._M_length;
	
	_Int_pointer __lhs = _M_dataplus;
	const _Int_pointer __sto = _M_dataplus + _M_length;
	_Int_pointer __rhs = __arg._M_dataplus;
	
	while (__lhs < __sto)
	{
		if (*__lhs == *__rhs)
		{
			++__lhs;
			++__rhs;
		}
		else
		{
			return *__lhs < *__rhs;
		}
	}
	
	return false;
}

bool
_Int_stdbase::
_M_is_greater_than(const _Int_stdbase& __arg) const
{
	if (_M_sign != __arg._M_sign)
		return _M_sign > __arg._M_sign;
	
	if (_M_length != __arg._M_length)
		return _M_length > __arg._M_length;
	
	_Int_pointer __lhs = _M_dataplus;
	const _Int_pointer __sto = _M_dataplus + _M_length;
	_Int_pointer __rhs = __arg._M_dataplus;
	
	while (__lhs < __sto)
	{
		if (*__lhs == *__rhs)
		{
			++__lhs;
			++__rhs;
		}
		else
		{
			return *__lhs > *__rhs;
		}
	}
	
	return false;
}

bool
_Int_stdbase::
_M_is_less_than_equal_to(const _Int_stdbase& __arg) const
{
	if (_M_sign != __arg._M_sign)
		return _M_sign < __arg._M_sign;
	
	if (_M_length != __arg._M_length)
		return _M_length < __arg._M_length;
	
	_Int_pointer __lhs = _M_dataplus;
	const _Int_pointer __sto = _M_dataplus + _M_length;
	_Int_pointer __rhs = __arg._M_dataplus;
	
	while (__lhs < __sto)
	{
		if (*__lhs == *__rhs)
		{
			++__lhs;
			++__rhs;
		}
		else
		{
			return *__lhs < *__rhs;
		}
	}
	
	return true;
}

bool
_Int_stdbase::
_M_is_greater_than_equal_to(const _Int_stdbase& __arg) const
{
	if (_M_sign != __arg._M_sign)
		return _M_sign > __arg._M_sign;
	
	if (_M_length != __arg._M_length)
		return _M_length > __arg._M_length;
	
	_Int_pointer __lhs = _M_dataplus;
	const _Int_pointer __sto = _M_dataplus + _M_length;
	_Int_pointer __rhs = __arg._M_dataplus;
	
	while (__lhs < __sto)
	{
		if (*__lhs == *__rhs)
		{
			++__lhs;
			++__rhs;
		}
		else
		{
			return *__lhs > *__rhs;
		}
	}
	
	return true;
}

int
_Int_stdbase::
_M_basic_compare(const _Int_stdbase& __arg) const
{
	if (_M_length != __arg._M_length)
		return (_M_length < __arg._M_length ? -1 : 1);
	
	_Int_pointer __lhs = _M_dataplus;
	const _Int_pointer __sto = _M_dataplus + _M_length;
	_Int_pointer __rhs = __arg._M_dataplus;
	
	while (__lhs < __sto)
	{
		if (*__lhs == *__rhs)
		{
			++__lhs;
			++__rhs;
		}
		else
		{
			return (*__lhs < *__rhs ? -1 : 1);
		}
	}
	
	return 0;
}

int
_Int_stdbase::
_M_compare(const _Int_stdbase& __arg) const
{
	if (_M_sign != __arg._M_sign)
		return (_M_sign < __arg._M_sign ? -1 : 1);
	
	return _M_basic_compare(__arg);
}

}

#endif
