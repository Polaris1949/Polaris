#ifndef _POL_TYPE_TCC
#define _POL_TYPE_TCC 1

namespace pol
{

template<typename _Tp>
basic_type<_Tp>::
basic_type()
	: _M_data()
{
}

template<typename _Tp>
basic_type<_Tp>::
basic_type(const _Tp& __x)
	: _M_data(__x)
{
}

template<typename _Tp>
basic_type<_Tp>::
basic_type(_Tp&& __x)
	: _M_data()
{
	this->swap(__x);
}

template<typename _Tp>
basic_type<_Tp>::
basic_type(const basic_type<_Tp>& __x)
	: _M_data(__x._M_data)
{
}

template<typename _Tp>
basic_type<_Tp>::
basic_type(basic_type<_Tp>&& __x)
	: _M_data()
{
	this->swap(__x);
}

template<typename _Tp>
basic_type<_Tp>::
~basic_type() noexcept
{
}

template<typename _Tp>
void
basic_type<_Tp>::
swap(_Tp& __x)
{
	std::swap(this->_M_data, __x);
}

template<typename _Tp>
void
basic_type<_Tp>::
swap(basic_type<_Tp>& __x)
{
	std::swap(this->_M_data, __x._M_data);
}

template<typename _Tp>
basic_type<_Tp>&
basic_type<_Tp>::
operator = (const basic_type<_Tp>& __x)
{
	this->_M_data = __x._M_data;
	return *this;
}

template<typename _Tp>
basic_type<_Tp>&
basic_type<_Tp>::
operator = (basic_type<_Tp>&& __x)
{
	this->_M_data = _Tp();
	this->swap(__x);
	return *this;
}

template<typename _Tp>
_Tp&
basic_type<_Tp>::
data()
{
	return this->_M_data;
}

template<typename _Tp>
_Tp
basic_type<_Tp>::
data() const
{
	return this->_M_data;
}

template<typename _Tp>
size_t
basic_type<_Tp>::
size() const
{
	return sizeof(this->_M_data);
}

template<typename _Tp>
basic_type<_Tp>::
operator _Tp&()
{
	return this->_M_data;
}

template<typename _Tp>
basic_type<_Tp>::
operator _Tp() const
{
	return this->_M_data;
}

template<typename _Tp>
integer_type<_Tp>::
integer_type()
	: basic_type<_Tp>()
{
}

template<typename _Tp>
integer_type<_Tp>::
integer_type(const _Tp& __x)
	: basic_type<_Tp>(__x)
{
}

template<typename _Tp>
integer_type<_Tp>::
integer_type(_Tp&& __x)
	: basic_type<_Tp>()
{
	this->swap(__x);
}

template<typename _Tp>
integer_type<_Tp>::
integer_type(const integer_type<_Tp>& __x)
	: basic_type<_Tp>(__x._M_data)
{
}

template<typename _Tp>
integer_type<_Tp>::
integer_type(integer_type<_Tp>&& __x)
	: basic_type<_Tp>()
{
	this->swap(__x);
}

template<typename _Tp>
integer_type<_Tp>::
~integer_type() noexcept
{
}

template<typename _Tp>
void
integer_type<_Tp>::
swap(value_type& __x)
{
	std::swap(this->_M_data, __x);
}

template<typename _Tp>
void
integer_type<_Tp>::
swap(integer_type<value_type>& __x)
{
	std::swap(this->_M_data, __x._M_data);
}

template<typename _Tp>
integer_type<_Tp>&
integer_type<_Tp>::
operator = (const integer_type<_Tp>& __x)
{
	this->_M_data = __x._M_data;
	return *this;
}

template<typename _Tp>
integer_type<_Tp>&
integer_type<_Tp>::
operator = (integer_type<_Tp>&& __x)
{
	this->_M_data = _Tp();
	this->swap(__x);
	return *this;
}

template<typename _Tp>
integer_type<_Tp>
integer_type<_Tp>::
operator + (const integer_type<_Tp>& __x) const
{
	return integer_type<_Tp>(this->_M_data + __x._M_data);
}

template<typename _Tp>
integer_type<_Tp>
integer_type<_Tp>::
operator - (const integer_type<_Tp>& __x) const
{
	return integer_type<_Tp>(this->_M_data - __x._M_data);
}

template<typename _Tp>
integer_type<_Tp>
integer_type<_Tp>::
operator * (const integer_type<_Tp>& __x) const
{
	return integer_type<_Tp>(this->_M_data * __x._M_data);
}

template<typename _Tp>
integer_type<_Tp>
integer_type<_Tp>::
operator / (const integer_type<_Tp>& __x) const
{
	return integer_type<_Tp>(this->_M_data / __x._M_data);
}

template<typename _Tp>
integer_type<_Tp>
integer_type<_Tp>::
operator % (const integer_type<_Tp>& __x) const
{
	return integer_type<_Tp>(this->_M_data % __x._M_data);
}

template<typename _Tp>
integer_type<_Tp>&
integer_type<_Tp>::
operator += (const integer_type<_Tp>& __x)
{
	this->_M_data += __x._M_data;
	return *this;
}

template<typename _Tp>
integer_type<_Tp>&
integer_type<_Tp>::
operator -= (const integer_type<_Tp>& __x)
{
	this->_M_data -= __x._M_data;
	return *this;
}

template<typename _Tp>
integer_type<_Tp>&
integer_type<_Tp>::
operator *= (const integer_type<_Tp>& __x)
{
	this->_M_data *= __x._M_data;
	return *this;
}

template<typename _Tp>
integer_type<_Tp>&
integer_type<_Tp>::
operator /= (const integer_type<_Tp>& __x)
{
	this->_M_data /= __x._M_data;
	return *this;
}

template<typename _Tp>
integer_type<_Tp>&
integer_type<_Tp>::
operator %= (const integer_type<_Tp>& __x)
{
	this->_M_data %= __x._M_data;
	return *this;
}

template<typename _Tp>
bool
integer_type<_Tp>::
operator == (const integer_type<_Tp>& __x) const
{
	return (this->_M_data == __x._M_data);
}

template<typename _Tp>
bool
integer_type<_Tp>::
operator != (const integer_type<_Tp>& __x) const
{
	return (this->_M_data != __x._M_data);
}

template<typename _Tp>
bool
integer_type<_Tp>::
operator < (const integer_type<_Tp>& __x) const
{
	return (this->_M_data < __x._M_data);
}

template<typename _Tp>
bool
integer_type<_Tp>::
operator <= (const integer_type<_Tp>& __x) const
{
	return (this->_M_data <= __x._M_data);
}

template<typename _Tp>
bool
integer_type<_Tp>::
operator > (const integer_type<_Tp>& __x) const
{
	return (this->_M_data > __x._M_data);
}

template<typename _Tp>
bool
integer_type<_Tp>::
operator >= (const integer_type<_Tp>& __x) const
{
	return (this->_M_data >= __x._M_data);
}

template<typename _T>
std::istream&
operator >> (std::istream& __in, integer_type<_T>& __x)
{
	__in >> __x._M_data;
	return __in;
}

template<typename _T>
std::ostream&
operator << (std::ostream& __out, const integer_type<_T>& __x)
{
	__out << __x._M_data;
	return __out;
}

}

#endif
