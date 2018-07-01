#ifndef _STDEXT_GRAPH_EDGE_TCC_
#define _STDEXT_GRAPH_EDGE_TCC_

#pragma GCC system_header

#include <iostream>

#include "../config"
#include "edge.h"

namespace stdext
{

namespace graph_type
{

edge::edge(size_type __x, size_type __y)
	: _M_begin(__x), _M_end(__y)
{
}

edge::edge(const edge& __e)
	: _M_begin(__e._M_begin), _M_end(__e._M_end)
{
}

edge::~edge() __noexcept
{
}

edge::size_type&
edge::begin()
{
	return (this->_M_begin);
}

const edge::size_type&
edge::begin() const
{
	return (this->_M_begin);
}

edge::size_type&
edge::end()
{
	return (this->_M_end);
}

const edge::size_type&
edge::end() const
{
	return (this->_M_end);
}

bool
edge::operator == (const edge& __e) const
{
	return (this->_M_begin == __e._M_begin)
		&& (this->_M_end == __e._M_end);
}

bool
edge::operator != (const edge& __e) const
{
	return (this->_M_begin != __e._M_begin)
		|| (this->_M_end != __e._M_end);
}

std::istream&
operator >> (std::istream& __in, edge& __e)
{
	__in >> __e._M_begin >> __e._M_end;
	return __in;
}

std::ostream&
operator << (std::ostream& __out, const edge& __e)
{
	__out << __e._M_begin << ' ' << __e._M_end;
	return __out;
}

template<typename _Tp>
edge_w<_Tp>::edge_w(size_type __x, size_type __y, value_type __w)
	: edge(__x, __y), _M_weight(__w)
{
}

template<typename _Tp>
edge_w<_Tp>::edge_w(edge __e, value_type __w)
	: edge(__e), _M_weight(__w)
{
}

template<typename _Tp>
edge_w<_Tp>::edge_w(const edge_w<value_type>& __e)
	: edge(__e._M_begin, __e._M_end), _M_weight(__e._M_weight)
{
}

template<typename _Tp>
edge_w<_Tp>::~edge_w() __noexcept
{
}

template<typename _Tp>
typename edge_w<_Tp>::value_type&
edge_w<_Tp>::weight()
{
	return (this->_M_weight);
}

template<typename _Tp>
const typename edge_w<_Tp>::value_type&
edge_w<_Tp>::weight() const
{
	return (this->_M_weight);
}

template<typename _Tp>
edge_w<_Tp>::operator edge() const
{
	return edge(this->_M_begin, this->_M_end);
}

template<typename _Tp>
bool
edge_w<_Tp>::operator == (const edge_w<value_type>& __e) const
{
	return (this->_M_begin == __e._M_begin)
		&& (this->_M_end == __e._M_end)
		&& (this->_M_weight == __e._M_weight);
}

template<typename _Tp>
bool
edge_w<_Tp>::operator != (const edge_w<value_type>& __e) const
{
	return (this->_M_begin != __e._M_begin)
		|| (this->_M_end != __e._M_end)
		|| (this->_M_weight != __e._M_weight);
}

template<typename _Tp>
bool
edge_w<_Tp>::operator < (const edge_w<value_type>& __e) const
{
	if (this->_M_weight != __e._M_weight)
		return (this->_M_weight < __e._M_weight);
	else if (this->_M_begin != __e._M_begin)
		return (this->_M_begin < __e._M_begin);
	else
		return (this->_M_end < __e._M_end);
}

template<typename _Tp>
bool
edge_w<_Tp>::operator > (const edge_w<value_type>& __e) const
{
	if (this->_M_weight != __e._M_weight)
		return (this->_M_weight > __e._M_weight);
	else if (this->_M_begin != __e._M_begin)
		return (this->_M_begin > __e._M_begin);
	else
		return (this->_M_end > __e._M_end);
}

template<typename _Tp>
bool
edge_w<_Tp>::operator <= (const edge_w<value_type>& __e) const
{
	if (this->_M_weight != __e._M_weight)
		return (this->_M_weight <= __e._M_weight);
	else if (this->_M_begin != __e._M_begin)
		return (this->_M_begin <= __e._M_begin);
	else
		return (this->_M_end <= __e._M_end);
}

template<typename _Tp>
bool
edge_w<_Tp>::operator >= (const edge_w<value_type>& __e) const
{
	if (this->_M_weight != __e._M_weight)
		return (this->_M_weight >= __e._M_weight);
	else if (this->_M_begin != __e._M_begin)
		return (this->_M_begin >= __e._M_begin);
	else
		return (this->_M_end >= __e._M_end);
}

template<typename _T>
std::istream&
operator >> (std::istream& __in, edge_w<_T>& __e)
{
	__in >> __e._M_begin >> __e._M_end >> __e._M_weight;
	return __in;
}

template<typename _T>
std::ostream&
operator << (std::ostream& __out, const edge_w<_T>& __e)
{
	__out << __e._M_begin << ' ' << __e._M_end << ' ' << __e._M_weight;
	return __out;
}

} // namespace stdext::graph_type

} // namespace stdext

#endif
