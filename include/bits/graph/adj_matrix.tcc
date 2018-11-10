#ifndef _POL_GRAPH_ADJ_MATRIX_TCC
#define _POL_GRAPH_ADJ_MATRIX_TCC 1

#include <typeinfo>
#include <stdexcept>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <set>
#include <stack>
#include <queue>
#include <utility>

namespace polaris
{

template<typename _Tp, typename _Pred>
template<typename _T, typename _P>
adjmatrix<_Tp, _Pred>::graph_iterator<_T, _P>::
graph_iterator()
	: _M_base(), _M_i(), _M_j()
{
	if (typeid(_Tp) != typeid(_T) || typeid(_Pred) != typeid(_P))
		throw std::bad_cast();
}

template<typename _Tp, typename _Pred>
template<typename _T, typename _P>
adjmatrix<_Tp, _Pred>::graph_iterator<_T, _P>::
graph_iterator(base_ptr __b, size_type __i, size_type __j)
	: _M_base(__b), _M_i(__i), _M_j(__j)
{
	if (typeid(_Tp) != typeid(_T) || typeid(_Pred) != typeid(_P))
		throw std::bad_cast();
}

template<typename _Tp, typename _Pred>
template<typename _T, typename _P>
adjmatrix<_Tp, _Pred>::graph_iterator<_T, _P>::
~graph_iterator() __noexcept
{
}

template<typename _Tp, typename _Pred>
template<typename _T, typename _P>
adjmatrix<_Tp, _Pred>::graph_iterator<_T, _P>&
adjmatrix<_Tp, _Pred>::graph_iterator<_T, _P>::
operator++ ()
{
	if (this->_M_i >= this->_M_base->vertex_size())
		throw std::out_of_range("stdext::adjmatrix::graph_iterator::"
			"operator++ ()");

	if ((++this->_M_j) >= this->_M_base->vertex_size())
	{
		this->_M_j = 0;
		++this->_M_i;
	}

	return *this;
}

template<typename _Tp, typename _Pred>
template<typename _T, typename _P>
adjmatrix<_Tp, _Pred>::graph_iterator<_T, _P>&
adjmatrix<_Tp, _Pred>::graph_iterator<_T, _P>::
operator-- ()
{
	if (this->_M_i <= size_type(0) && this->_M_j <= size_type(0))
		throw std::out_of_range("stdext::adjmatrix::graph_iterator::"
			"operator-- ()");

	if ((this->_M_j--) <= size_type(0))
	{
		this->_M_j = 0;
		--this->_M_i;
	}

	return *this;
}

template<typename _Tp, typename _Pred>
template<typename _T, typename _P>
bool
adjmatrix<_Tp, _Pred>::graph_iterator<_T, _P>::
operator == (const graph_iterator<_T, _P>& __o) const
{
	return (this->_M_base == __o._M_base &&
		this->_M_i == __o._M_i && this->_M_j == __o._M_j);
}

template<typename _Tp, typename _Pred>
template<typename _T, typename _P>
bool
adjmatrix<_Tp, _Pred>::graph_iterator<_T, _P>::
operator != (const graph_iterator<_T, _P>& __o) const
{
	return (this->_M_base != __o._M_base ||
		this->_M_i != __o._M_i || this->_M_j != __o._M_j);
}

template<typename _Tp, typename _Pred>
template<typename _T, typename _P>
_T&
adjmatrix<_Tp, _Pred>::graph_iterator<_T, _P>::
operator* ()
{
	return this->_M_base->edge_weight(this->_M_i, this->_M_j);
}

template<typename _Tp, typename _Pred>
template<typename _T, typename _P>
edge_w<_T>
adjmatrix<_Tp, _Pred>::graph_iterator<_T, _P>::
operator* () const
{
	return edge_w<value_type>(this->_M_i, this->_M_j,
		this->_M_base->edge_weight(this->_M_i, this->_M_j));
}

template<typename _Tp, typename _Pred>
adjmatrix<_Tp, _Pred>::
adjmatrix(size_type __v, size_type __e, const container_type& __g,
	const value_type& __b, const value_good& __p)
	: _M_vertex(__v), _M_edge(__e), _M_graph(__g),
		value_bad(__b), predicate(__p)
{
}

#if __cplusplus >= 201103L
template<typename _Tp, typename _Pred>
adjmatrix<_Tp, _Pred>::
adjmatrix(size_type __v, size_type __e, container_type&& __g,
	value_type&& __b, value_good&& __p)
	: _M_vertex(__v), _M_edge(__e), _M_graph(__g),
		value_bad(__b), predicate(__p)
{
}
#endif

template<typename _Tp, typename _Pred>
adjmatrix<_Tp, _Pred>::
adjmatrix(const adjmatrix<value_type, value_good>& __g)
	: _M_vertex(__g._M_vretex), _M_edge(__g._M_edge),
		_M_graph(__g._M_graph), value_bad(__g.value_bad),
		predicate(__g.predicate)
{
}

#if __cplusplus >= 201103L
template<typename _Tp, typename _Pred>
adjmatrix<_Tp, _Pred>::
adjmatrix(adjmatrix<value_type, value_good>&& __g)
	noexcept(noexcept(std::swap(_M_vertex, __g._M_vertex))
		&& noexcept(std::swap(_M_edge, __g._M_edge))
		&& noexcept(std::swap(_M_graph, __g._M_graph))
		&& noexcept(std::swap(value_bad, __g.value_bad))
		&& noexcept(std::swap(predicate, __g.predicate)))
	: _M_vertex(), _M_edge(), _M_graph(), value_bad(), predicate()
{
	std::swap(this->_M_vertex, __g._M_vertex);
	std::swap(this->_M_edge, __g._M_edge);
	std::swap(this->_M_graph, __g._M_graph);
	std::swap(this->value_bad, __g.value_bad);
	std::swap(this->predicate, __g.predicate);
}
#endif

template<typename _Tp, typename _Pred>
adjmatrix<_Tp, _Pred>::
~adjmatrix() __noexcept
{
}

template<typename _Tp, typename _Pred>
bool
adjmatrix<_Tp, _Pred>::
good_value(const value_type& __val) const
#if __cplusplus >= 201103L
	noexcept(noexcept(predicate(__val, value_bad)))
#endif
{
	return (this->predicate)(__val, value_bad);
}

#if __cplusplus >= 201103L
template<typename _Tp, typename _Pred>
bool
adjmatrix<_Tp, _Pred>::
good_value(value_type&& __val)
	noexcept(noexcept(predicate(__val, value_bad)))
{
	return (this->predicate)(__val, value_bad);
}
#endif

template<typename _Tp, typename _Pred>
bool
adjmatrix<_Tp, _Pred>::
bad_value(const value_type& __val) const
#if __cplusplus >= 201103L
	noexcept(noexcept(predicate(__val, value_bad)))
#endif
{
	return !(this->predicate)(__val, value_bad);
}

#if __cplusplus >= 201103L
template<typename _Tp, typename _Pred>
bool
adjmatrix<_Tp, _Pred>::
bad_value(value_type&& __val) const
	noexcept(noexcept(predicate(__val, value_bad)))
{
	return !(this->predicate)(__val, value_bad);
}
#endif

template<typename _Tp, typename _Pred>
bool
adjmatrix<_Tp, _Pred>::
good_edge(size_type __x, size_type __y) const
{
	return this->good_value(this->edge_weight(__x, __y));
}

template<typename _Tp, typename _Pred>
bool
adjmatrix<_Tp, _Pred>::
bad_edge(size_type __x, size_type __y) const
{
	return this->bad_value(this->edge_weight(__x, __y));
}

template<typename _Tp, typename _Pred>
template<typename _P>
bool
adjmatrix<_Tp, _Pred>::
good_predicate(const value_type& __l, const value_type& __r,
	const _P& __p) const
{
	if (this->good_value(__l))
	{
		if (this->good_value(__r))
			return __p(__l, __r);
		else
			return true;
	}
	else
		return false;
}

#if __cplusplus >= 201103L
template<typename _Tp, typename _Pred>
template<typename _P>
bool
adjmatrix<_Tp, _Pred>::
good_predicate(value_type&& __l, value_type&& __r,
	_P&& __p) const
{
	if (this->good_value(__l))
	{
		if (this->good_value(__r))
			return __p(__l, __r);
		else
			return true;
	}
	else
		return false;
}
#endif

template<typename _Tp, typename _Pred>
template<typename _P>
bool
adjmatrix<_Tp, _Pred>::
bad_predicate(const value_type& __l, const value_type& __r,
	const _P& __p) const
{
	if (this->good_value(__l))
	{
		if (this->good_value(__r))
			return !__p(__l, __r);
		else
			return false;
	}
	else
		return true;
}

#if __cplusplus >= 201103L
template<typename _Tp, typename _Pred>
template<typename _P>
bool
adjmatrix<_Tp, _Pred>::
bad_predicate(value_type&& __l, value_type&& __r,
	_P&& __p) const
{
	if (this->good_value(__l))
	{
		if (this->good_value(__r))
			return !__p(__l, __r);
		else
			return false;
	}
	else
		return true;
}
#endif

template<typename _Tp, typename _Pred>
template<typename _O>
typename adjmatrix<_Tp, _Pred>::value_type
adjmatrix<_Tp, _Pred>::
value_operation(const value_type& __l, const value_type& __r,
	const _O& __o) const
{
	if (this->good_value(__l) && this->good_value(__r))
		return __o(__l, __r);
	else
		return value_bad;
}

#if __cplusplus >= 201103L
template<typename _Tp, typename _Pred>
template<typename _O>
typename adjmatrix<_Tp, _Pred>::value_type
adjmatrix<_Tp, _Pred>::
value_operation(value_type&& __l, value_type&& __r,
	_O&& __o) const
{
	if (this->good_value(__l) && this->good_value(__r))
		return __o(__l, __r);
	else
		return value_bad;
}
#endif

template<typename _Tp, typename _Pred>
void
adjmatrix<_Tp, _Pred>::
clear()
{
	this->_M_vertex = size_type();
	this->_M_edge = size_type();
	this->_M_graph = container_type();
	this->value_bad = value_type();
	this->predicate = value_good();
}

template<typename _Tp, typename _Pred>
void
adjmatrix<_Tp, _Pred>::
swap(adjmatrix<value_type, value_good>& __g)
{
	adjmatrix<value_type, value_good> temp(*this);
	__g = temp;
	*this = __g;
}

template<typename _Tp, typename _Pred>
void
adjmatrix<_Tp, _Pred>::
assign(size_type __v, size_type __e, const container_type& __g,
	const value_type& __b, const value_good& __p)
{
	this->_M_vertex = __v;
	this->_M_edge = __e;
	this->_M_graph = __g;
	this->value_bad = __b;
	this->predicate = __p;
}

template<typename _Tp, typename _Pred>
typename adjmatrix<_Tp, _Pred>::size_type
adjmatrix<_Tp, _Pred>::
vertex_size() const __noexcept
{
	return (this->_M_vertex);
}

template<typename _Tp, typename _Pred>
typename adjmatrix<_Tp, _Pred>::size_type
adjmatrix<_Tp, _Pred>::
edge_size() const __noexcept
{
	return (this->_M_edge);
}

template<typename _Tp, typename _Pred>
typename adjmatrix<_Tp, _Pred>::value_type&
adjmatrix<_Tp, _Pred>::
edge_weight(size_type __x, size_type __y)
{
	if (__x > this->vertex_size()) return value_bad;
	if (__y > this->vertex_size()) return value_bad;

	return (this->adjmatrix_graph())[__x][__y];
}

template<typename _Tp, typename _Pred>
const typename adjmatrix<_Tp, _Pred>::value_type&
adjmatrix<_Tp, _Pred>::
edge_weight(size_type __x, size_type __y) const
{
	if (__x > this->vertex_size()) return value_bad;
	if (__y > this->vertex_size()) return value_bad;

	return (this->adjmatrix_graph())[__x][__y];
}

template<typename _Tp, typename _Pred>
const typename adjmatrix<_Tp, _Pred>::value_type&
adjmatrix<_Tp, _Pred>::
edge_weight(edge __e) const
{
	return this->edge_weight(__e.begin(), __e.end());
}

template<typename _Tp, typename _Pred>
const typename adjmatrix<_Tp, _Pred>::container_type&
adjmatrix<_Tp, _Pred>::
adjmatrix_graph() const __noexcept
{
	return (this->_M_graph);
}

template<typename _Tp, typename _Pred>
typename adjmatrix<_Tp, _Pred>::size_type
adjmatrix<_Tp, _Pred>::
indegree(size_type __pos) const
{
	size_type i, s = 0;

	for (i = 0; i < (this->vertex_size()); ++i)
		if (this->good_edge(i, __pos)) ++s;

	return s;
}

template<typename _Tp, typename _Pred>
typename adjmatrix<_Tp, _Pred>::size_type
adjmatrix<_Tp, _Pred>::
outdegree(size_type __pos) const
{
	size_type i, s = 0;

	for (i = 0; i < (this->vertex_size()); ++i)
		if (this->good_edge(__pos, i)) ++s;

	return s;
}

template<typename _Tp, typename _Pred>
typename adjmatrix<_Tp, _Pred>::size_type
adjmatrix<_Tp, _Pred>::
degree(size_type __pos) const
{
	return (this->indegree(__pos) + this->outdegree(__pos));
}

template<typename _Tp, typename _Pred>
void
adjmatrix<_Tp, _Pred>::
insert_edge(size_type __x, size_type __y, value_type __w)
{
	if (__x >= this->vertex_size() || __y >= this->vertex_size()
		|| this->bad_value(__w)) return;

	(this->adjmatrix_graph())[__x][__y] = __w;
	++this->_M_edge;
}

template<typename _Tp, typename _Pred>
void
adjmatrix<_Tp, _Pred>::
insert_edge(edge __e, value_type __w)
{
	this->insert_edge(__e.begin(), __e.end(), __w);
}

template<typename _Tp, typename _Pred>
void
adjmatrix<_Tp, _Pred>::
insert_edge(edge_w<value_type> __e)
{
	this->insert_edge(__e.begin(), __e.end(), __e.weight());
}

template<typename _Tp, typename _Pred>
void
adjmatrix<_Tp, _Pred>::
erase_edge(size_type __x, size_type __y)
{
	if (__x >= this->vertex_size() || __y >= this->vertex_size()) return;

	(this->adjmatrix_graph())[__x][__y] = value_bad;
	--this->_M_edge;
}

template<typename _Tp, typename _Pred>
void
adjmatrix<_Tp, _Pred>::
erase_edge(edge __e)
{
	this->erase_edge(__e.begin(), __e.end());
}

template<typename _Tp, typename _Pred>
void
adjmatrix<_Tp, _Pred>::
erase_edge()
{
	edge e = this->find_edge();

	while (e != edge(npos, npos))
	{
		this->erase_edge(e);
		e = this->find_edge(e.begin(), ++e.end());
	}
}

template<typename _Tp, typename _Pred>
void
adjmatrix<_Tp, _Pred>::
insert_vertex(size_type __pos)
{
	if (__pos > this->vertex_size()) return;

	++this->_M_vertex;

	if (__pos == this->vertex_size())
	{
		(this->_M_graph).resize(this->vertex_size(),
			std::vector<value_type>(this->vertex_size(), value_bad));
	}
	else
	{
		size_type i;

		for (i = 0; i < this->vertex_size(); ++i)
		{
			if (i == __pos)
			{
				(this->_M_graph).insert((this->_M_graph).begin() + __pos,
					std::vector<value_type>(this->vertex_size(), value_bad));
			}
			else
			{
				(this->_M_graph)[i].insert((this->_M_graph)[i].begin() + \
					__pos, value_bad);
			}
		}
	}
}

template<typename _Tp, typename _Pred>
void
adjmatrix<_Tp, _Pred>::
insert_vertex()
{
	++this->_M_vertex;
	this->_M_graph.resize(this->vertex_size(),
		std::vector<value_type>(this->vertex_size(), value_bad));
}

template<typename _Tp, typename _Pred>
void
adjmatrix<_Tp, _Pred>::
erase_vertex(size_type __pos)
{
	if (__pos >= this->vertex_size()) return;
	if (this->vertex_size() == 0) throw std::out_of_range("erase_vertex(p)");

	--this->_M_vertex;

	if (__pos == this->vertex_size() - 1)
	{
		(this->_M_graph).resize(this->vertex_size(),
			std::vector<value_type>(this->vertex_size()));
	}
	else
	{
		size_type i;

		for (i = this->vertex_size(); i >= 0; i--)
		{
			if (i == __pos)
			{
				(this->_M_graph).erase((this->_M_graph).begin() + __pos);
			}
			else
			{
				(this->_M_graph)[i].erase((this->_M_graph)[i].begin() +
					__pos);
			}

			if (i == 0) break;
		}
	}
}

template<typename _Tp, typename _Pred>
void
adjmatrix<_Tp, _Pred>::
erase_vertex()
{
	if (this->_M_vertex == 0) throw std::out_of_range("erase_vertex()");
	--this->_M_vertex;
	this->_M_graph.resize(this->vertex_size(),
		std::vector<value_type>(this->vertex_size()));
}

template<typename _Tp, typename _Pred>
void
adjmatrix<_Tp, _Pred>::
_M_dfs(size_type __pos, std::vector<size_type>& __v,
	std::vector<bool>& __visited) const
{
	size_type i;

	__v.push_back(__pos);
	__visited[__pos] = true;

	for (i = 0; i < (this->vertex_size()); ++i)
		if (this->good_edge(__pos, i) && !__visited[i])
			this->_M_dfs(i, __v, __visited);
}

template<typename _Tp, typename _Pred>
std::vector<typename adjmatrix<_Tp, _Pred>::size_type>
adjmatrix<_Tp, _Pred>::
dfs(size_type __pos) const
{
	std::vector<size_type> v;

	if (__pos >= (this->_M_v)) return v;

	std::vector<bool> visited(this->vertex_size());

	this->_M_dfs(__pos, v, visited);
	return v;
}

template<typename _Tp, typename _Pred>
void
adjmatrix<_Tp, _Pred>::
_M_bfs(size_type __pos, std::vector<size_type>& __v,
	std::vector<bool>& __visited) const
{
	std::queue<size_type> q;
	size_type i, j;

	__v.push_back(__pos);
	__visited[__pos] = true;
	q.push(__pos);

	while (!q.empty())
	{
		j = q.front();

		for (i = 0; i < (this->vertex_size()); ++i)
			if (this->good_edge(j, i) && !__visited[i])
			{
				__v.push_back(i);
				__visited[i] = true;
				q.push(i);
			}

		q.pop();
	}
}

template<typename _Tp, typename _Pred>
std::vector<typename adjmatrix<_Tp, _Pred>::size_type>
adjmatrix<_Tp, _Pred>::
bfs(size_type __pos) const
{
	std::vector<size_type> v;

	if (__pos >= (this->_M_v)) return v;

	std::vector<bool> visited(this->vertex_size());

	this->_M_bfs(__pos, v, visited);
	return v;
}

template<typename _Tp, typename _Pred>
adjmatrix<typename adjmatrix<_Tp, _Pred>::value_type,
	typename adjmatrix<_Tp, _Pred>::value_good>&
adjmatrix<_Tp, _Pred>::
operator = (const adjmatrix<value_type, value_good>& __g)
{
	this->_M_vertex = __g._M_vertex;
	this->_M_edge = __g._M_edge;
	this->_M_graph = __g._M_graph;
	this->value_bad = __g.value_bad;
	this->predicate = __g.predicate;
}

template<typename _Tp, typename _Pred>
typename adjmatrix<_Tp, _Pred>::size_type
adjmatrix<_Tp, _Pred>::
find_vertex(size_type __x, size_type __y) const
{
	if (__x >= this->vertex_size() || __y >= this->vertex_size())
		return npos;

	size_type i;

	for (i = __y; i < this->vertex_size(); ++i)
	{
		if (this->good_edge(__x, i)) return i;
	}

	return npos;
}

template<typename _Tp, typename _Pred>
edge
adjmatrix<_Tp, _Pred>::
find_edge(size_type __x, size_type __y) const
{
	if (__x >= (this->vertex_size()))
		return edge(npos, npos);

	if (__y >= (this->vertex_size()))
	{
		++__x;
		__y = 0;
	}

	size_type i, j;

	for (i = __x; i < (this->vertex_size()); ++i)
	{
		if (i == __x) j = __y;
		else j = 0;

		for (; j < (this->vertex_size()); ++j)
			if (this->good_edge(i, j))
				return edge(i, j);
	}

	return edge(npos, npos);
}

template<typename _Tp, typename _Pred>
edge_w<typename adjmatrix<_Tp, _Pred>::value_type>
adjmatrix<_Tp, _Pred>::
find_edge_w(size_type __x, size_type __y) const
{
	edge e = this->find_edge(__x, __y);

	if (e == edge(npos, npos)) return edge_w<value_type>(e, value_bad);
	else return edge_w<value_type>(e, this->edge_weight(e));
}

template<typename _Tp, typename _Pred>
std::vector<edge>
adjmatrix<_Tp, _Pred>::
to_edge_array() const
{
	edge e = this->find_edge();
	size_type bv = e.begin(), ev = e.end();
	std::vector<edge> ge;

	while ((bv < (this->vertex_size())) && (ev < (this->vertex_size())))
	{
		ge.push_back(edge(bv, ev));

		e = this->find_edge(bv, ++ev);
		bv = e.begin();
		ev = e.end();
	}

	return ge;
}

template<typename _Tp, typename _Pred>
std::vector<edge_w<typename adjmatrix<_Tp, _Pred>::value_type> >
adjmatrix<_Tp, _Pred>::
to_edge_w_array() const
{
	edge e = this->find_edge();
	size_type bv = e.begin(), ev = e.end();
	std::vector<edge_w<value_type> > ge;

	while ((bv < (this->vertex_size())) && (ev < (this->vertex_size())))
	{
		ge.push_back(edge_w<value_type>(bv, ev,
			(this->edge_weight(bv, ev))));

		e = this->find_edge(bv, ++ev);
		bv = e.begin();
		ev = e.end();
	}

	return ge;
}

template<typename _Tp, typename _Pred>
std::vector<edge_w<typename adjmatrix<_Tp, _Pred>::value_type> >
adjmatrix<_Tp, _Pred>::
prim(size_type __pos) const
{
	std::vector<edge_w<value_type> > mst(this->vertex_size() - 1,
		edge_w<value_type>(npos, npos, value_bad));

	if (__pos >= (this->vertex_size())) return mst;

	size_type i, j, k, minpos;
	value_type minv, w;

	for (i = 0, j = 0; i < (this->vertex_size() - 1) &&
		j < (this->vertex_size()); ++i, ++j)
	{
		if (j == __pos) ++j;

		mst[i].begin() = __pos;
		mst[i].end() = j;
		mst[i].weight() = this->edge_weight(__pos, j);
	}

	for (k = 0; k < (this->vertex_size() - 1); ++k)
	{
		minv = this->value_bad;
		minpos = k;

		for (j = k; j < (this->vertex_size() - 1); ++j)
		{
			if (this->good_predicate<std::less<value_type> >
				(mst[j].weight(), minv))
			{
				minv = mst[j].weight();
				minpos = j;
			}
		}

		if (minpos != k) std::swap(mst[k], mst[minpos]);
		j = mst[k].end();

		for (i = k + 1; i < (this->vertex_size() - 1); ++i)
		{
			w = this->edge_weight(j, mst[i].end());

			if (this->good_predicate<std::less<value_type> >
				(w, mst[i].weight()))
			{
				mst[i].weight() = w;
				mst[i].begin() = j;
			}
		}
	}

	return mst;
}

template<typename _Tp, typename _Pred>
std::vector<edge_w<typename adjmatrix<_Tp, _Pred>::value_type> >
adjmatrix<_Tp, _Pred>::
kruskal() const
{
	std::vector<edge_w<value_type> > mst(this->vertex_size());

	size_type i, j, jb, je, k, bi, ei;
	std::vector<std::set<size_type> > s(this->vertex_size());

	std::vector<edge_w<value_type> > ge = this->to_edge_w_array();
	std::sort(ge.begin(), ge.end());

	for (i = 0; i < (this->vertex_size()); i++)
		s[i].insert(i);

	i = 0; j = 0;

	while (i < (this->vertex_size() - 1))
	{
		jb = ge[j].begin();
		je = ge[j].end();

		for (k = 0; k < (this->vertex_size()); ++k)
		{
			if (s[k].find(jb) != s[k].end()) bi = k;
			if (s[k].find(je) != s[k].end()) ei = k;
		}

		if (bi != ei)
		{
			mst[i] = edge_w<value_type>(jb, je, this->edge_weight(jb, je));
			++i;
			s[bi].insert(s[ei].begin(), s[ei].end());
			s[ei].clear();
		}

		++j;
	}

	return mst;
}

template<typename _Tp, typename _Pred>
std::vector<typename adjmatrix<_Tp, _Pred>::value_type>
adjmatrix<_Tp, _Pred>::
dijkstra(size_type __pos) const
{
	std::vector<value_type> dist(this->vertex_size(), value_bad);

	if (__pos >= this->vertex_size()) return dist;

	size_type i, j, minpos;
	value_type w;
	std::vector<bool> s(this->vertex_size());

	for (i = 0; i < (this->vertex_size()); ++i)
	{
		if (i != __pos) s[i] = false;
		else s[i] = true;

		dist[i] = this->edge_weight(__pos, i);
	}

	for (i = 0; i < (this->vertex_size() - 2); ++i)
	{
		w = value_bad;
		minpos = __pos;

		for (j = 0; j < (this->vertex_size()); ++j)
		{
			if (!s[j] && this->good_predicate<std::less<value_type> >
				(dist[j], w))
			{
				minpos = j;
				w = dist[j];
			}
		}

		if (minpos != __pos) s[minpos] = true;
		else break;

		for (j = 0; j < (this->vertex_size()); ++j)
		{
			if (!s[j] && this->good_predicate<std::less<value_type> >
				(this->value_operation<std::plus<value_type> >
				(dist[minpos], this->edge_weight(minpos, j)), dist[j]))
			{
				dist[j] = dist[minpos] + this->edge_weight(minpos, j);
			}
		}
	}

	return dist;
}

template<typename _Tp, typename _Pred>
std::vector<std::vector<typename adjmatrix<_Tp, _Pred>::value_type> >
adjmatrix<_Tp, _Pred>::
floyd() const
{
	std::vector<std::vector<value_type> > dist(this->vertex_size(),
		std::vector<value_type>(this->vertex_size()));

	size_type i, j, k;

	for (i = 0; i < (this->vertex_size()); ++i)
		for (j = 0; j < (this->vertex_size()); ++j)
			dist[i][j] = this->edge_weight(i, j);

	for (k = 0; k < (this->vertex_size()); ++k)
		for (i = 0; i < (this->vertex_size()); ++i)
			for (j = 0; j < (this->vertex_size()); ++j)
			{
				if (i == k || j == k || i == j) continue;

				if (this->good_predicate<std::less<value_type> >
					(this->value_operation<std::plus<value_type> >
					(dist[i][k], dist[k][j]), dist[i][j]))
				{
					dist[i][j] = dist[i][k] + dist[k][j];
				}
			}

	return dist;
}

template<typename _Tp, typename _Pred>
std::pair<std::vector<typename adjmatrix<_Tp, _Pred>::value_type>, bool>
adjmatrix<_Tp, _Pred>::
bellman_ford(size_type __pos) const
{
	std::vector<value_type> dist(this->vertex_size(), value_bad);

	if (__pos >= this->vertex_size()) return std::make_pair(dist, false);

	size_type i, j;
	std::vector<edge_w<value_type> > ge = this->to_edge_w_array();

	for (i = 0; i < (this->vertex_size() - 1); ++i)
	{
		for (j = 0; j < (this->edge_size()); ++j)
		{
			if (this->good_predicate<std::less<value_type> >
				(dist[ge[j].begin()] + ge[j].weight(), dist[ge[j].end()]))
			{
				dist[ge[j].end()] = dist[ge[j].begin()] + ge[j].weight();
			}
		}
	}

	for (i = 0; i < (this->edge_size()); ++i)
	{
		if (this->good_predicate<std::less<value_type> >
			(dist[ge[i].begin()] + ge[i].weight(), dist[ge[i].end()]))
		{
			return std::make_pair(dist, false);
		}
	}

	return std::make_pair(dist, true);
}

template<typename _Tp, typename _Pred>
std::pair<std::vector<typename adjmatrix<_Tp, _Pred>::value_type>, bool>
adjmatrix<_Tp, _Pred>::
spfa(size_type __pos) const
{
	std::vector<value_type> dist(this->vertex_size(), value_bad);

	if (__pos >= this->vertex_size()) return std::make_pair(dist, false);

	size_type i, x;
	std::queue<size_type> q;
	std::vector<bool> in_q(this->vertex_size(), false);
	std::vector<size_type> in_q_s(this->vertex_size(), 0);

	q.push(__pos);
	in_q[__pos] = true;
	++in_q_s[__pos];

	while (!q.empty())
	{
		x = q.front();
		in_q[x] = false;

		for (i = 0; i < this->vertex_size(); ++i)
		{
			if (this->good_value(this->edge_weight(x, i)) &&
				this->good_predicate<std::less<value_type> >
				(dist[x] + this->edge_weight(x, i), dist[i]))
			{
				dist[i] = dist[x] + this->edge_weight(x, i);

				if (!in_q[i])
				{
					q.push(i);
					in_q[i] = true;
					++in_q_s[i];

					if (in_q_s[i] > this->vertex_size())
						return std::make_pair(dist, false);
				}
			}
		}

		q.pop();
	}

	return std::make_pair(dist, true);
}

template<typename _Tp, typename _Pred>
void
adjmatrix<_Tp, _Pred>::
_M_tarjan(size_type __pos, std::vector<bool>& __visited,
	std::vector<std::vector<size_type> >& __v, std::vector<scc_v>& __scc,
	std::stack<size_type>& __s, std::vector<bool>& __in_s) const
{
	__scc[__pos].index() = __pos;
	__scc[__pos].lowlink() = __pos;
	__visited[__pos] = true;
	__s.push(__pos);
	__in_s[__pos] = true;

	size_type i;

	for (i = 0; i < this->vertex_size(); ++i)
	{
		if (this->good_edge(__pos, i))
		{
			if (!__visited[i])
			{
				this->_M_tarjan(i, __visited, __v,
					__scc, __s, __in_s);
				__scc[__pos].lowlink() = std::min(__scc[__pos].lowlink(),
					__scc[i].lowlink());
			}
			else if (__in_s[i])
			{
				__scc[__pos].lowlink() = std::min(__scc[__pos].lowlink(),
					__scc[i].index());
			}
		}
	}

	if (__scc[__pos].lowlink() == __scc[__pos].index())
	{
		size_type temp;
		__v.push_back(std::vector<size_type>());

		do
		{
			temp = __s.top();
			__s.pop();
			__in_s[temp] = false;
			__v.back().push_back(temp);
		}
		while (temp != __pos);
	}
}

template<typename _Tp, typename _Pred>
std::vector<std::vector<typename adjmatrix<_Tp, _Pred>::size_type> >
adjmatrix<_Tp, _Pred>::
tarjan(size_type __pos) const
{
	std::vector<std::vector<size_type> > v;
	std::vector<bool> visited(this->vertex_size());
	std::vector<scc_v> scc(this->vertex_size());
	std::stack<size_type> s;
	std::vector<bool> in_s(this->vertex_size());

	this->_M_tarjan(__pos, visited, v, scc, s, in_s);

	return v;
}

template<typename _Tp, typename _Pred>
std::vector<std::vector<typename adjmatrix<_Tp, _Pred>::size_type> >
adjmatrix<_Tp, _Pred>::
tarjan_all() const
{
	std::vector<std::vector<size_type> > v;
	std::vector<bool> visited(this->vertex_size());
	std::vector<scc_v> scc(this->vertex_size());
	std::stack<size_type> s;
	std::vector<bool> in_s(this->vertex_size());
	size_type i;

	for (i = 0; i < this->vertex_size(); ++i)
	{
		if (!visited[i])
		{
			this->_M_tarjan(i, visited, v, scc, s, in_s);
		}
	}

	return v;
}

template<typename _Tp, typename _Pred>
std::vector<std::vector<typename adjmatrix<_Tp, _Pred>::size_type> >
adjmatrix<_Tp, _Pred>::
tarjan_transform(const std::vector<std::vector<size_type> >& __v)
{
	std::vector<std::vector<size_type> > v(__v.size());
	size_type i, j, vi;

	for (i = __v.size() - 1, vi = 0; i >= 0 && vi < v.size(); --i, ++vi)
	{
		for (j = __v[i].size() - 1; j >= 0; --j)
		{
			v[vi].push_back(__v[i][j]);

			if (j == 0) break;
		}

		if (i == 0) break;
	}

	return v;
}

template<typename _Tp, typename _Pred>
std::pair<std::vector<typename adjmatrix<_Tp, _Pred>::size_type>, bool>
adjmatrix<_Tp, _Pred>::
toposort() const
{
	std::vector<size_type> v, in_d(this->vertex_size());
	std::stack<size_type> s;
	size_type i, j;

	for (i = 0; i < this->vertex_size(); ++i)
	{
		in_d[i] = this->indegree(i);

		if (in_d[i] == 0) s.push(i);
	}

	while (!s.empty())
	{
		i = s.top();
		s.pop();
		v.push_back(i);
		j = this->find_vertex(i);

		while (j != npos)
		{
			--in_d[j];
			if (in_d[j] == 0) s.push(j);
			j = find_vertex(i, j + 1);
		}
	}

	if (v.size() < this->vertex_size())
		return std::make_pair(v, false);
	else
		return std::make_pair(v, true);
}

}

#endif /* _POL_GRAPH_ADJ_MATRIX_TCC */
