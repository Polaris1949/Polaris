#ifndef _POL_GRAPH_EDGE_TCC
#define _POL_GRAPH_EDGE_TCC 1

#include <iostream>

namespace polaris
{

edge<void>::
edge(size_type __x, size_type __y)
	: _M_begin{__x}, _M_end{__y}
{}

inline std::size_t&
edge<void>::
begin()
{ return this->_M_begin; }

inline const std::size_t&
edge<void>::
begin() const
{ return this->_M_begin; }

inline std::size_t&
edge<void>::
end()
{ return this->_M_end; }

inline const std::size_t&
edge<void>::
end() const
{ return this->_M_end; }

inline bool
edge<void>::
operator == (const edge<void>& __e) const
{
	return (this->begin() == __e.begin())
		&& (this->end() == __e.end());
}

inline bool
edge<void>::
operator != (const edge<void>& __e) const
{ return !(*this == __e); }

inline bool
edge<void>::
operator < (const edge<void>& __e) const
{
	return (this->begin() == __e.begin() ?
		this->end() < __e.end() : this->begin() < __e.begin());
}

inline bool
edge<void>::
operator > (const edge<void>& __e) const
{ return __e < *this; }

inline bool
edge<void>::
operator <= (const edge<void>& __e) const
{ return !(__e < *this); }

inline bool
edge<void>::
operator >= (const edge<void>& __e) const
{ return !(*this < __e); }

std::istream&
operator >> (std::istream& __in, edge<void>& __e)
{
	__in >> __e.begin() >> __e.end();
	return __in;
}

std::ostream&
operator << (std::ostream& __out, const edge<void>& __e)
{
	__out << __e.begin() << ' ' << __e.end();
	return __out;
}

template<typename _Tp>
edge<_Tp>::
edge(size_type __x, size_type __y)
	: _Base{__x, __y}, _M_weight{}
{}

template<typename _Tp>
edge<_Tp>::
edge(size_type __x, size_type __y, const value_type& __w)
	: _Base{__x, __y}, _M_weight{__w}
{}

template<typename _Tp>
edge<_Tp>::
edge(const edge<void>& __e)
	: _Base{__e}, _M_weight{}
{}

template<typename _Tp>
edge<_Tp>::
edge(const edge<void>& __e, const value_type& __w)
	: _Base{__e}, _M_weight{__w}
{}

template<typename _Tp>
inline _Tp&
edge<_Tp>::
weight()
{ return this->_M_weight; }

template<typename _Tp>
inline const _Tp&
edge<_Tp>::
weight() const
{ return this->_M_weight; }

template<typename _Tp>
inline bool
edge<_Tp>::
operator == (const edge<value_type>& __e) const
{
	return (this->weight() == __e.weight())
		&& (_Base{*this} == _Base{__e});
}

template<typename _Tp>
inline bool
edge<_Tp>::
operator != (const edge<value_type>& __e) const
{ return !(*this == __e); }

template<typename _Tp>
inline bool
edge<_Tp>::
operator < (const edge<value_type>& __e) const
{
	return (this->weight() == __e.weight() ?
		_Base{*this} < _Base{__e} : this->weight() < __e.weight());
}

template<typename _Tp>
inline bool
edge<_Tp>::
operator > (const edge<value_type>& __e) const
{ return __e < *this; }

template<typename _Tp>
inline bool
edge<_Tp>::
operator <= (const edge<value_type>& __e) const
{ return !(__e < *this); }

template<typename _Tp>
inline bool
edge<_Tp>::
operator >= (const edge<value_type>& __e) const
{ return !(*this < __e); }

template<typename _Tp>
std::istream&
operator >> (std::istream& __in, edge<_Tp>& __e)
{
	__in >> __e.begin() >> __e.end() >> __e.weight();
	return __in;
}

template<typename _T>
std::ostream&
operator << (std::ostream& __out, const edge<_T>& __e)
{
	__out << __e.begin() << ' ' << __e.end() << ' ' << __e.weight();
	return __out;
}

}

#endif /* _POL_GRAPH_EDGE_TCC */
