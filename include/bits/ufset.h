#ifndef _POL_UFSET_H
#define _POL_UFSET_H 1

#include <map>
#include <vector>

namespace polaris
{

template<typename _Tp>
class basic_ufset
{
public:
	typedef _Tp value_type;
	typedef std::size_t size_type;

private:
	std::map<_Tp, _Tp> _M_parent;
	std::map<_Tp, std::size_t> _M_rank;

public:
	basic_ufset();

	value_type& parent(const value_type& __x);
	size_type& rank(const value_type& __x);

	value_type& find(const value_type& __x);
	bool merge(const value_type& __x, const value_type& __y);
	bool is_brother(const value_type& __x, const value_type& __y);

	value_type& operator[] (const value_type& __x);
};

class seq_ufset
{
public:
	using value_type = std::size_t;
	using size_type = std::size_t;

private:
	std::vector<std::size_t> _M_parent;
	std::vector<std::size_t> _M_rank;

public:
	seq_ufset();
	explicit seq_ufset(size_type __n);

	void init(size_type __n);

	value_type& parent(const value_type& __x);
	const value_type& parent(const value_type& __x) const;
	size_type& rank(const value_type& __x);
	const value_type& rank(const value_type& __x) const;

	value_type& find(const value_type& __x);
	bool merge(const value_type& __x, const value_type& __y);
	bool is_brother(const value_type& __x, const value_type& __y);

	value_type& operator[] (const value_type& __x);
};

}

#endif
