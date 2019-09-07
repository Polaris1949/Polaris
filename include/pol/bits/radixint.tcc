#ifndef _POL_RADIXINT_TCC
#define _POL_RADIXINT_TCC 1

#include <stdexcept>
#include <iostream>

namespace polaris
{

template<typename _T>
std::deque<unsigned_char>
radix_integer::
to_container(_T __n, byte_type __r)
{
	if (__r < 2)
		throw std::invalid_argument("radix_integer::"
			"to_container(): invalid radix '__r'");

	container_type __ret;

	if (__n == 0)
	{
		__ret.push_back(static_cast<byte_type>(0));
		return __ret;
	}

	while (__n > 0)
	{
		__ret.push_back(__n % __r);
		__n /= __r;
	}

	return __ret;
}

template<typename _T>
size_t
radix_integer::
integer_length(_T __n)
{
	if (__n == 0)
		return static_cast<size_type>(1);

	size_t __len{};

	while (__n > 0)
	{
		__len++;
		__n /= 10;
	}

	return __len;
}

radix_integer::
radix_integer()
	: _M_radix(static_cast<byte_type>(100)), _M_data({0})
{
}

template<typename _T>
radix_integer::
radix_integer(_T __n, byte_type __r)
	: _M_radix(return_if(__r < 2, make_ew(std::invalid_argument
		("radix_integer::radix_integer(): invalid radix '__r'")), __r)),
		_M_data(to_container<_T>(__n, __r))
{
}

radix_integer::
radix_integer(const container_type& __x, byte_type __r)
	: _M_radix(return_if(__r < 2, make_ew(std::invalid_argument
		("radix_integer::radix_integer(): invalid radix '__r'")), __r)),
		_M_data(return_if(__x.empty(), make_ew
		(std::invalid_argument("radix_integer::radix_integer(): "
		"empty container '__x'")), __x))
{
}

radix_integer::
radix_integer(const radix_integer& __x)
	: _M_radix(__x._M_radix), _M_data(__x._M_data)
{
}

radix_integer::
radix_integer(radix_integer&& __x)
	: _M_radix(static_cast<byte_type>(100)),
		_M_data({0})
{
	this->swap(__x);
}

radix_integer::
~radix_integer() __noexcept__
{
}

void
radix_integer::
swap(radix_integer& __x)
{
	std::swap(this->_M_radix, __x._M_radix);
	std::swap(this->_M_data, __x._M_data);
}

const std::deque<unsigned_char>&
radix_integer::
data() const
{
	return this->_M_data;
}

radix_integer
radix_integer::
operator + (const radix_integer& __x) const
{
	if (this->_M_radix != __x._M_radix)
		exception_thrower(std::invalid_argument
			("radix_integer::operator + (): different radixes"));

	radix_integer __ret(0, this->_M_radix);

	size_type lsize = this->_M_data.size(),
		rsize = __x._M_data.size();
	bool comp = lsize < rsize;
	size_type &minsize = comp ? lsize : rsize,
		&maxsize = comp ? rsize : lsize;
	unsigned short temp;

	__ret._M_data.resize(maxsize + 1);

	for (size_type i = 0; i < minsize; i++)
	{
		temp = static_cast<unsigned short>(this->_M_data[i])
			+ static_cast<unsigned short>(__x._M_data[i]);
		__ret._M_data[i] += temp % __ret._M_radix;
		__ret._M_data[i + 1] += temp / __ret._M_radix;
	}

	for (size_type i = minsize; i < maxsize; i++)
	{
		temp = comp ? static_cast<unsigned short>(__x._M_data[i])
			: static_cast<unsigned short>(this->_M_data[i]);
		__ret._M_data[i] += temp % __ret._M_radix;
		__ret._M_data[i + 1] += temp / __ret._M_radix;
	}

	while (__ret._M_data.back() == 0 && __ret._M_data.size() > 1)
		__ret._M_data.pop_back();

	return __ret;
}

std::istream&
operator >> (std::istream& __in, radix_integer& __x)
{
	char temp;
	unsigned short d = 0;
	bool f;
	__x._M_data.clear();

	while (true)
	{
		f = false;
		temp = __in.peek();

		if (isspace(temp)) break;

		while (isdigit(temp))
		{
			__in >> temp;
			d = d * 10 + temp - '0';
			if (d >= __x._M_radix) {f = true; break;}
			temp = __in.peek();
		}

		temp = d % 10;
		d /= 10;
		__x._M_data.push_front(d);

		if (!f) break;
		d = temp;
	}
}

std::ostream&
operator << (std::ostream& __out, const radix_integer& __x)
{
	size_t __size = __x._M_data.size(), __e = __size - 1,
		__rlen = radix_integer::integer_length(__x._M_radix - 1);

	for (size_t i = 0; i < __size; i++)
	{
		if (i)
			for (size_t j = 0; j < __rlen - radix_integer::
				integer_length(__x._M_data[__e - i]); j++)
				__out << '0';

		__out << short(__x._M_data[__e - i]);
	}

	return __out;
}

}

#endif
