#ifndef _POL_GRAPH_SCC_V_H
#define _POL_GRAPH_SCC_V_H 1

namespace polaris
{

class scc_v
{
public:
	typedef size_t size_type;

protected:
	size_type _M_index, _M_lowlink;

public:
	explicit
	scc_v(size_type __index = 0, size_type __lowlink = 0);

	virtual
	~scc_v() __noexcept;

	size_type&
	index();

	const size_type&
	index() const;

	size_type&
	lowlink();

	const size_type&
	lowlink() const;

	friend std::istream&
	operator >> (std::istream& __in, scc_v& __scc);

	friend std::ostream&
	operator << (std::ostream& __out, const scc_v& __scc);
};

}

#endif /* _POL_GRAPH_SCC_V_H */
