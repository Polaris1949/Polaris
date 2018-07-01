#ifndef _STDEXT_GRAPH_EDGE_FWD_H_
#define _STDEXT_GRAPH_EDGE_FWD_H_

#pragma GCC system_header

#include <iosfwd>

namespace stdext
{

namespace graph_type
{

class edge;

std::istream&
operator >> (std::istream& __in, edge& __e);

std::ostream&
operator << (std::ostream& __out, const edge& __e);

template<typename _Tp>
class edge_w;

template<typename _T>
std::istream&
operator >> (std::istream& __in, edge_w<_T>& __e);

template<typename _T>
std::ostream&
operator << (std::ostream& __out, const edge_w<_T>& __e);

} // namespace stdext::graph_type

} // namespace stdext

#endif /* EDGE_FWD.H */
