#ifndef _STDEXT_GRAPH_SCC_V_FWD_H_
#define _STDEXT_GRAPH_SCC_V_FWD_H_

#pragma GCC system_header

#include <iosfwd>

namespace stdext
{

namespace graph_type
{

class scc_v;

std::istream&
operator >> (std::istream& __in, scc_v& __scc);

std::ostream&
operator << (std::ostream& __out, const scc_v& __scc);

} // namespace stdext::graph_type

} // namespace stdext

#endif
