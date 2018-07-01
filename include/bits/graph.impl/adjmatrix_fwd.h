#ifndef _STDEXT_GRAPH_ADJMATRIX_FWD_H_
#define _STDEXT_GRAPH_ADJMATRIX_FWD_H_

#pragma GCC system_header

#include <iosfwd>

namespace stdext
{

namespace graph_type
{

template<typename _Tp, typename _Pred>
class adjmatrix;

template<typename _T, typename _P>
std::istream&
operator >> (std::istream& __in, adjmatrix<_T, _P>& __scc);

template<typename _T, typename _P>
std::ostream&
operator << (std::ostream& __out, const adjmatrix<_T, _P>& __scc);

} // namespace stdext::graph_type

} // namespace stdext

#endif
