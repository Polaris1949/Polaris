#ifndef _STDEXT_GRAPH_EDGE_H_
#define _STDEXT_GRAPH_EDGE_H_

#pragma GCC system_header

#include <iostream>

#include "../config"

namespace stdext
{

namespace graph_type
{

class edge
{
public:
	// Types:
	typedef size_t size_type;
	
protected:
	// Data Members (protected):
	size_type _M_begin, _M_end;
	
public:
	explicit edge(size_type __x = 0, size_type __y = 0);
	edge(const edge& __e);
	
	virtual ~edge() __noexcept;
	
	virtual size_type& begin();
	virtual const size_type& begin() const;
	
	virtual size_type& end();
	virtual const size_type& end() const;
	
	bool operator == (const edge& __e) const;
	bool operator != (const edge& __e) const;
	
	// For standard input.
	friend std::istream& operator >> (std::istream& __in, edge& __e);
	
	// For standard output.
	friend std::ostream& operator << (std::ostream& __out, const edge& __e);
};

template<typename _Tp>
class edge_w : public edge
{
public:
	// Types:
	typedef _Tp value_type;
	typedef size_t size_type;
	
protected:
	// Data Members (protected):
	value_type _M_weight;
	
public:
	explicit edge_w(size_type __x = 0, size_type __y = 0,
		value_type __w = value_type());
	explicit edge_w(edge __e, value_type __w = value_type());
	edge_w(const edge_w<value_type>& __e);
	
	virtual ~edge_w() __noexcept;
	
	virtual value_type& weight();
	virtual const value_type& weight() const;
	
	operator edge() const;
	
	bool operator == (const edge_w<value_type>& __e) const;
	bool operator != (const edge_w<value_type>& __e) const;
	
	bool operator < (const edge_w<value_type>& __e) const;
	bool operator > (const edge_w<value_type>& __e) const;
	
	bool operator <= (const edge_w<value_type>& __e) const;
	bool operator >= (const edge_w<value_type>& __e) const;
	
	// For standard input.
	template<typename _T>
	friend std::istream& operator >> (std::istream& __in,
		edge_w<_T>& __e);
	
	// For standard output.
	template<typename _T>
	friend std::ostream& operator << (std::ostream& __out,
		const edge_w<_T>& __e);
};

} // namespace stdext::graph_type

#if __cplusplus >= 201103L
using __gee_ = graph_type::edge;

template<typename _T>
using __gew_ = graph_type::edge_w<_T>;
#endif

} // namespace stdext

#endif
