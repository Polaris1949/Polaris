#ifndef _STDEXT_GRAPH_IMPL_H_
#define _STDEXT_GRAPH_IMPL_H_

#include <vector>
#include <stack>
#include "../config"
#include "edge_fwd.h"
#include "scc_v_fwd.h"

namespace stdext
{

namespace graph_type
{

template<typename _Tp, typename _Pred, typename _Cont>
class graph_impl
{
protected:
	template<typename _T, typename _P, typename _C>
	class iterator_impl
	{
		public:
		typedef size_t                  size_type;
		typedef _T                      value_type;
		typedef _P                      value_good;
		typedef _C                      container_type;
		typedef graph_impl<_T, _P, _C>  base_type;
		typedef graph_impl<_T, _P, _C>* base_ptr;
		
	private:
		base_ptr _M_base;
		size_type _M_i, _M_j;
		
	public:
		iterator_impl();
		
		virtual ~iterator_impl() __noexcept;
		
		virtual iterator_impl<_T, _P, _C>& operator++ ();
		virtual iterator_impl<_T, _P, _C>& operator-- ();
		
		virtual iterator_impl<_T, _P, _C> operator++ (int);
		virtual iterator_impl<_T, _P, _C> operator-- (int);
		
		virtual bool
		operator == (const iterator_impl<_T, _P, _C>& __o) const;
		
		virtual bool
		operator != (const iterator_impl<_T, _P, _C>& __o) const;
		
		virtual value_type&
		operator* ();
		
		virtual edge_w<value_type>
		operator* () const;
		
	private:
		explicit
		iterator_impl(base_ptr __b, size_type __i, size_type __j);
	};
	
public:
	typedef _Tp                                    value_type;
	typedef _Pred                                  value_good;
	typedef size_t                                 size_type;
	typedef _Cont                                  container_type;
	typedef iterator_impl<_Tp, _Pred, _Cont>       iterator;
	typedef const iterator_impl<_Tp, _Pred, _Cont> const_iterator;
	typedef _Tp*                                   pointer;
	typedef const _Tp*                             const_pointer;
	typedef _Tp&                                   reference;
	typedef const _Tp&                             const_reference;
	
public:
	static const size_type npos = static_cast<size_type>(-1);
	value_type value_bad;
	value_good predicate;
	
protected:
	size_type _M_vertex, _M_edge;
	container_type _M_graph;
	
public:
	graph_impl(size_type __v, size_type __e, const container_type& __g,
		const value_type& __b, const value_good& __p);
#if __cplusplus >= 201103L
	explicit
	graph_impl(size_type __v, size_type __e, container_type&& __g,
		value_type&& __b, value_good&& __p);
#endif
	
	graph_impl(const graph_impl<value_type, value_good, container_type>& __g);
	
#if __cplusplus >= 201103L
	graph_impl(graph_impl<value_type, value_good, container_type>&& __g)
		noexcept(noexcept(std::swap(_M_vertex, __g._M_vertex))
			&& noexcept(std::swap(_M_edge, __g._M_edge))
			&& noexcept(std::swap(_M_graph, __g._M_graph))
			&& noexcept(std::swap(value_bad, __g.value_bad))
			&& noexcept(std::swap(predicate, __g.predicate)));
#endif
	
	virtual ~graph_impl() __noexcept;
	
#if __cplusplus < 201103L
	virtual inline bool
	good_value(const value_type& __val) const = 0;
#else
	virtual inline bool
	good_value(const value_type& __val) const
		noexcept(noexcept(predicate(__val, value_bad))) = 0;
	
	virtual inline bool
	good_value(value_type&& __val)
		noexcept(noexcept(predicate(__val, value_bad))) = 0;
#endif
	
#if __cplusplus < 201103L
	virtual inline bool
	bad_value(const value_type& __val) const = 0;
#else
	virtual inline bool
	bad_value(const value_type& __val) const
		noexcept(noexcept(predicate(__val, value_bad))) = 0;
	
	virtual inline bool
	bad_value(value_type&& __val) const
		noexcept(noexcept(predicate(__val, value_bad))) = 0;
#endif
	
	virtual inline bool
	good_edge(size_type __x, size_type __y) const = 0;
	
	virtual inline bool
	bad_edge(size_type __x, size_type __y) const = 0;
	
	template<typename _P>
	inline bool
	good_predicate(const value_type& __l, const value_type& __r,
		const _P& __p) const;
#if __cplusplus >= 201103L
	template<typename _P>
	inline bool
	good_predicate(value_type&& __l, value_type&& __r,
		_P&& __p) const;
#endif
	
	template<typename _P>
	inline bool
	bad_predicate(const value_type& __l, const value_type& __r,
		const _P& __p) const;
#if __cplusplus >= 201103L
	template<typename _P>
	inline bool
	bad_predicate(value_type&& __l, value_type&& __r,
		_P&& __p) const;
#endif
	
	template<typename _O>
	inline value_type
	value_operation(const value_type& __l, const value_type& __r,
		const _O& __o) const;
#if __cplusplus >= 201103L
	template<typename _O>
	inline value_type
	value_operation(value_type&& __l, value_type&& __r,
		_O&& __o) const;
#endif
	
	virtual void
	clear() = 0;
	
	virtual void
	swap(graph_impl<value_type, value_good, container_type>& __g) = 0;
#if __cplusplus >= 201103L
	virtual void
	swap(graph_impl<value_type, value_good, container_type>&& __g) = 0;
#endif
	
	virtual void
	assign(size_type __v, size_type __e, const container_type& __g,
		const value_type& __b, const value_good& __p) = 0;
#if __cplusplus >= 201103L
	virtual void
	assign(size_type __v, size_type __e, container_type&& __g,
		value_type&& __b, value_good&& __p) = 0;
#endif
	
	virtual void
	assign(const graph_impl<value_type, value_good, container_type>& __g) = 0;
#if __cplusplus >= 201103L
	virtual void
	assign(graph_impl<value_type, value_good, container_type>&& __g) = 0;
#endif
	
	virtual inline size_type
	vertex_size() const __noexcept = 0;
	
	virtual inline size_type
	edge_size() const __noexcept = 0;
	
	virtual inline const container_type&
	adjmatrix_graph() const __noexcept = 0;
	
	virtual inline value_type&
	edge_weight(size_type __x, size_type __y) = 0;
	
	virtual inline const value_type&
	edge_weight(size_type __x, size_type __y) const = 0;
	
	virtual inline const value_type&
	edge_weight(edge __e) const = 0;
	
	virtual void
	insert_edge(size_type __x, size_type __y, value_type __w) = 0;
	
	virtual inline void
	insert_edge(edge __e, value_type __w) = 0;
	
	virtual inline void
	insert_edge(edge_w<value_type> __e) = 0;
	
	virtual void
	erase_edge(size_type __x, size_type __y) = 0;
	
	virtual inline void
	erase_edge(edge __e) = 0;
	
	virtual inline void
	erase_edge() = 0;
	
	virtual void
	insert_vertex(size_type __pos) = 0;
	
	virtual void
	insert_vertex() = 0;
	
	virtual void
	erase_vertex(size_type __pos) = 0;
	
	virtual void
	erase_vertex() = 0;
	
	virtual std::vector<edge>
	to_edge_array() const = 0;
	
	virtual std::vector<edge_w<value_type> >
	to_edge_w_array() const = 0;
	
	virtual size_type
	find_vertex(size_type __x, size_type __y) const = 0;
	
	virtual edge
	find_edge(size_type __x, size_type __y) const = 0;
	
	virtual inline edge_w<value_type>
	find_edge_w(size_type __x, size_type __y) const = 0;
	
	virtual size_type
	indegree(size_type __pos) const = 0;
	
	virtual size_type
	outdegree(size_type __pos) const = 0;
	
	virtual inline size_type
	degree(size_type __pos) const = 0;
	
	virtual inline std::vector<size_type>
	dfs(size_type __pos) const = 0;
	
	virtual inline std::vector<size_type>
	bfs(size_type __pos) const = 0;
	
	virtual std::vector<edge_w<value_type> >
	prim(size_type __pos) const = 0;
	
	virtual std::vector<edge_w<value_type> >
	kruskal() const = 0;
	
	virtual std::vector<value_type>
	dijkstra(size_type __pos) const = 0;
	
	virtual std::vector<std::vector<value_type> >
	floyd() const = 0;
	
	virtual std::pair<std::vector<value_type>, bool>
	bellman_ford(size_type __pos = 0) const = 0;
	
	virtual std::pair<std::vector<value_type>, bool>
	spfa(size_type __pos = 0) const = 0;
	
	virtual std::vector<std::vector<size_type> >
	tarjan(size_type __pos = 0) const = 0;
	
	virtual std::vector<std::vector<size_type> >
	tarjan_all() const = 0;
	
	static std::vector<std::vector<size_type> >
	tarjan_transform(const std::vector<std::vector<size_type> >& __v);
	
	virtual std::pair<std::vector<size_type>, bool>
	toposort() const = 0;
	
	virtual graph_impl<value_type, value_good, container_type>&
	operator = (const graph_impl<value_type, value_good,
		container_type>& __g) = 0;
	
#if __cplusplus >= 201103L
	virtual graph_impl<value_type, value_good, container_type>&
	operator = (graph_impl<value_type, value_good,
		container_type>&& __g) = 0;
#endif
	
	virtual bool
	operator == (const graph_impl<value_type, value_good,
		container_type>& __g) const;
	
	virtual bool
	operator != (const graph_impl<value_type, value_good,
		container_type>& __g) const;
	
#if __cplusplus >= 201103L
	virtual bool
	operator == (graph_impl<value_type, value_good,
		container_type>&& __g) const;
	
	virtual bool
	operator != (graph_impl<value_type, value_good,
		container_type>&& __g) const;
#endif
	
private:
	virtual void
	_M_dfs(size_type __pos, std::vector<size_type>& __v,
		std::vector<bool>& __visited) const = 0;
	
	virtual void
	_M_bfs(size_type __pos, std::vector<size_type>& __v,
		std::vector<bool>& __visited) const = 0;
	
	virtual void
	_M_tarjan(size_type __pos, std::vector<bool>& __visited,
		std::vector<std::vector<size_type> >& __v, std::vector<scc_v>& __scc,
		std::stack<size_type>& __s, std::vector<bool>& __in_s) const = 0;
};

} // namespace stdext::graph_type

} // namespace stdext

#endif
