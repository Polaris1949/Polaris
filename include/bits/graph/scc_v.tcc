#ifndef _POL_GRAPH_SCC_V_TCC
#define _POL_GRAPH_SCC_V_TCC 1

namespace polaris
{

scc_v::
scc_v(size_type __index, size_type __lowlink)
	: _M_index(__index), _M_lowlink(__lowlink)
{
}

scc_v::
~scc_v() __noexcept
{
}

scc_v::size_type&
scc_v::
index()
{
	return this->_M_index;
}

const scc_v::size_type&
scc_v::
index() const
{
	return this->_M_index;
}

scc_v::size_type&
scc_v::
lowlink()
{
	return this->_M_lowlink;
}

const scc_v::size_type&
scc_v::
lowlink() const
{
	return this->_M_lowlink;
}

std::istream&
operator >> (std::istream& __in, scc_v& __scc)
{
	__in >> __scc._M_index >> __scc._M_lowlink;
	return __in;
}

std::ostream&
operator << (std::ostream& __out, const scc_v& __scc)
{
	__out << __scc._M_index << ' ' << __scc._M_lowlink;
	return __out;
}

}

#endif /* _POL_GRAPH_SCC_V_TCC */
