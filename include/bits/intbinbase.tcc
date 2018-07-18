#ifndef _POL_INTBINBASE_TCC
#define _POL_INTBINBASE_TCC 1

namespace polaris
{

template<typename _Tp, typename _Req = require<std::is_integral<_Tp>>>
void
basic_binary_integer::
_M_initialize(_Tp __x)
{
	_Int_data __tmp;
	_Int_data* __begin;

	if (sizeof(_Tp) % sizeof(_Int_data))
	{
		__tmp = __x;
		__begin = &__tmp;
	}
	else
		__begin = reinterpret_cast<_Int_data*>(&__x);

	_Int_data* __end = __begin + integer_size_v<_Tp>;
	std::copy(__begin, __end, this->_M_impl._M_start);
}

basic_binary_integer::
basic_binary_integer(char __x)
	: _Int_genbase(integer_size_v<char>)
{
	_M_initialize(__x);
}

basic_binary_integer::
basic_binary_integer(unsigned char __x)
	: _Int_genbase(integer_size_v<unsigned char>)
{
	_M_initialize(__x);
}

basic_binary_integer::
basic_binary_integer(int __x)
	: _Int_genbase(integer_size_v<int>)
{
	_M_initialize(__x);
}

basic_binary_integer::
basic_binary_integer(unsigned int __x)
	: _Int_genbase(integer_size_v<unsigned int>)
{
	_M_initialize(__x);
}

basic_binary_integer::
basic_binary_integer(long long __x)
	: _Int_genbase(integer_size_v<long long>)
{
	_M_initialize(__x);
}

basic_binary_integer::
basic_binary_integer(unsigned long long __x)
	: _Int_genbase(integer_size_v<unsigned long long>)
{
	_M_initialize(__x);
}

basic_binary_integer::
basic_binary_integer(size_type_tag_t, size_type __n)
	: _Int_genbase(__n)
{
}

basic_binary_integer&
basic_binary_integer::
_M_basic_plus(const basic_binary_integer& __x)
{
	_Int_exdata __t{};
	size_t __i{};

	for (; __i < __x.size(); ++__i)
	{
		__t += _Int_exdata(this->_M_get_element(__i))
			+  _Int_exdata(__x._M_get_element(__i));
		this->_M_set_element(__i, _Int_data(__t));
		__t >>= sizeof(_Int_data) * 8;
	}

	for (; __i < this->size(); ++__i)
	{
		__t += _Int_exdata(this->_M_get_element(__i))
			+  _Int_exdata(__x._M_get_element(__i));
		this->_M_set_element(__i, _Int_data(__t));
		__t >>= sizeof(_Int_data) * 8;
	}

	if (__t) this->_M_set_element(__i, this->_M_get_element(__i) + __t);
	return *this;
}

basic_binary_integer&
basic_binary_integer::
_M_basic_minus(const basic_binary_integer& __x)
{
	_Int_exdata __t{};
	size_t __i{};

	for (; __i < __x.size(); ++__i)
	{
		__t += _Int_exdata(this->_M_get_element(__i))
			-  _Int_exdata(__x._M_get_element(__i));
		this->_M_set_element(__i, _Int_data(__t));
		__t >>= sizeof(_Int_data) * 8;
	}

	for (; __i < this->size(); ++__i)
	{
		__t += _Int_exdata(this->_M_get_element(__i))
			-  _Int_exdata(__x._M_get_element(__i));
		this->_M_set_element(__i, _Int_data(__t));
		__t >>= sizeof(_Int_data) * 8;
	}

	if (__t) this->_M_set_element(__i, this->_M_get_element(__i) + __t);
	return *this;
}

size_t
basic_binary_integer::
size() const
{
	return this->_Int_genbase::size();
}

size_t
basic_binary_integer::
capacity() const
{
	return this->_Int_genbase::capacity();
}

_Int_data*
basic_binary_integer::
data() const
{
	return this->_M_impl._M_start;
}

basic_binary_integer&
basic_binary_integer::
flip()
{
	_Int_data* __ptr = this->_M_impl._M_start;

	while (__ptr < this->_M_impl._M_finish)
		polaris::flip(*__ptr++);

	return *this;
}

basic_binary_integer&
basic_binary_integer::
operator &= (const basic_binary_integer& __x)
{
	_Int_data* __lptr = this->_M_impl._M_start;
	_Int_data* __rptr = __x._M_impl._M_start;

	while (__rptr < __x._M_impl._M_finish)
		*__lptr++ &= *__rptr++;

	while (__lptr < this->_M_impl._M_finish)
		*__lptr++ = 0;

	return *this;
}

basic_binary_integer&
basic_binary_integer::
operator |= (const basic_binary_integer& __x)
{
	_Int_data* __lptr = this->_M_impl._M_start;
	_Int_data* __rptr = __x._M_impl._M_start;

	while (__rptr < __x._M_impl._M_finish)
		*__lptr++ |= *__rptr++;

	while (__lptr < this->_M_impl._M_finish)
		*__lptr++ = 0;

	return *this;
}

basic_binary_integer&
basic_binary_integer::
operator ^= (const basic_binary_integer& __x)
{
	_Int_data* __lptr = this->_M_impl._M_start;
	_Int_data* __rptr = __x._M_impl._M_start;

	while (__rptr < __x._M_impl._M_finish)
		*__lptr++ ^= *__rptr++;

	while (__lptr < this->_M_impl._M_finish)
		*__lptr++ = 0;

	return *this;
}

basic_binary_integer
basic_binary_integer::
operator & (const basic_binary_integer& __x) const
{
	return basic_binary_integer(*this) &= __x;
}

basic_binary_integer
basic_binary_integer::
operator | (const basic_binary_integer& __x) const
{
	return basic_binary_integer(*this) |= __x;
}

basic_binary_integer
basic_binary_integer::
operator ^ (const basic_binary_integer& __x) const
{
	return basic_binary_integer(*this) ^= __x;
}

basic_binary_integer
basic_binary_integer::
operator ~ () const
{
	return basic_binary_integer(*this).flip();
}

basic_binary_integer
basic_binary_integer::
operator + (const basic_binary_integer& __x) const
{
	basic_binary_integer __ret{size_type_tag, this->size()};
	_Int_data* __optr = __ret._M_impl._M_start;
	_Int_data* __lptr = this->_M_impl._M_start;
	_Int_data* __rptr = __x._M_impl._M_start;

	while (__lptr < this->_M_impl._M_finish \
		&& __rptr < __x._M_impl._M_finish)
	{
		*__optr++ += *__lptr++ + *__rptr++;
	}

	while (__lptr < this->_M_impl._M_finish)
	{
		*__optr++ += *__lptr++;
	}
}

basic_binary_integer&
basic_binary_integer::
operator += (const basic_binary_integer& __x)
{
	//return *this = *this + __x;
	return this->_M_basic_plus(__x);
}

basic_binary_integer&
basic_binary_integer::
operator -= (const basic_binary_integer& __x)
{
	return this->_M_basic_minus(__x);
}

}

#endif
