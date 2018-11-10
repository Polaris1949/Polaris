#ifndef _POL_GRAPH_EDGE_H
#define _POL_GRAPH_EDGE_H 1

#include <iosfwd>

namespace polaris
{

template<>
class edge<void>
{
public:
	using value_type = void;
	using size_type = std::size_t;

protected:
	size_type _M_begin;
	size_type _M_end;

public:
	edge() = default;
	edge(size_type __x, size_type __y);

	virtual ~edge() noexcept = default;

	virtual size_type& begin();
	virtual const size_type& begin() const;

	virtual size_type& end();
	virtual const size_type& end() const;

	bool operator == (const edge& __e) const;
	bool operator != (const edge& __e) const;

	bool operator < (const edge& __e) const;
	bool operator > (const edge& __e) const;

	bool operator <= (const edge& __e) const;
	bool operator >= (const edge& __e) const;
};

template<typename _Tp>
class edge : public edge<void>
{
public:
	using value_type = _Tp;
	using size_type = std::size_t;

protected:
	using _Base = edge<void>;

	value_type _M_weight;

public:
	edge() = default;
	edge(size_type __x, size_type __y);
	edge(size_type __x, size_type __y, const value_type& __w);
	explicit edge(const edge<void>& __e);
	edge(const edge<void>& __e, const value_type& __w);

	virtual ~edge() noexcept = default;

	virtual value_type& weight();
	virtual const value_type& weight() const;

	bool operator == (const edge<value_type>& __e) const;
	bool operator != (const edge<value_type>& __e) const;

	bool operator < (const edge<value_type>& __e) const;
	bool operator > (const edge<value_type>& __e) const;

	bool operator <= (const edge<value_type>& __e) const;
	bool operator >= (const edge<value_type>& __e) const;
};

}

#endif /* _POL_GRAPH_EDGE_H */
