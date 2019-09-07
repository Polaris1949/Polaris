#ifndef _POL_GRAPH_ADJ_MATRIX_H
#define _POL_GRAPH_ADJ_MATRIX_H 1

#include <iosfwd>
#include <functional>
#include <vector>
#include <stack>
#include "edge"
#include "scc_v"

namespace polaris
{

/***
  *  @brief A type of graph of using adjmatrix.
  *
  *  @ingroup graph_type
  *
  *  @tparam _Tp  Type of the weight of each edge in the graph.
  *  @tparam _Pred  A predicate of judging the weight whether OK.
  *
  *  Adjmatrixes support bidirectional iterators.
*/
template<typename _Tp, typename _Pred = std::not_equal_to<_Tp> >
class adjmatrix
{
private:
	template<typename _T, typename _P>
	class graph_iterator
	{
	public:
		typedef size_t             size_type;
		typedef _T                 value_type;
		typedef _P                 value_good;
		typedef adjmatrix<_T, _P>  base_type;
		typedef adjmatrix<_T, _P>* base_ptr;

	private:
		base_ptr _M_base;
		size_type _M_i, _M_j;

	public:
		graph_iterator();

		~graph_iterator() __noexcept;

		graph_iterator<_T, _P>& operator++ ();
		graph_iterator<_T, _P>& operator-- ();

		graph_iterator<_T, _P> operator++ (int);
		graph_iterator<_T, _P> operator-- (int);

		bool
		operator == (const graph_iterator<_T, _P>& __o) const;

		bool
		operator != (const graph_iterator<_T, _P>& __o) const;

		value_type&
		operator* ();

		edge_w<value_type>
		operator* () const;

	private:
		explicit
		graph_iterator(base_ptr __b, size_type __i = 0, size_type __j = 0);
	};

public:
	// Types:
	typedef _Tp                              value_type;
	typedef _Pred                            value_good;
	typedef size_t                           size_type;
	typedef std::vector<std::vector<_Tp> >   container_type;
	typedef graph_iterator<_Tp, _Pred>       iterator;
	typedef const graph_iterator<_Tp, _Pred> const_iterator;
	typedef _Tp*                             pointer;
	typedef const _Tp*                       const_pointer;
	typedef _Tp&                             reference;
	typedef const _Tp&                       const_reference;

	friend class graph_iterator<_Tp, _Pred>;

public:
	// Data:
	static const size_type npos = static_cast<size_type>(-1);
	value_type value_bad;
	value_good predicate;

private:
	size_type _M_vertex, _M_edge;
	container_type _M_graph;

public:
	/***
	  *  @brief  Construct a graph using adjmatrix.
	  *  @param  __v  The number of the vertexes in this %adjmatrix.
	  *  @param  __e  The number of the edges in this %adjmatrix.
	  *  @param  __g  The graph.
	  *  @param  __b  The bad edge weight.
	  *  @param  __p  The predicate.
	  *
	  *  This constructor will not check __v, __e and __g whether a valid
	  *  graph. Please keep them valid.
	*/
	explicit
	adjmatrix(size_type __v = 0, size_type __e = 0,
		const container_type& __g = container_type(),
		const value_type& __b = value_type(),
		const value_good& __p = value_good());
#if __cplusplus >= 201103L
	explicit
	adjmatrix(size_type __v, size_type __e, container_type&& __g,
		value_type&& __b, value_good&& __p);
#endif

	/***
	  *  @brief  Copy a graph using adjmatrix to this.
	  *  @param  __g  The graph that the constructor will copy.
	*/
	adjmatrix(const adjmatrix<value_type, value_good>& __g);

#if __cplusplus >= 201103L
	/***
	  *  @brief  Move a graph using adjmatrix to this.
	  *  @param  __g  The graph that the constructor will move.
	*/
	adjmatrix(adjmatrix<value_type, value_good>&& __g)
		noexcept(noexcept(std::swap(_M_vertex, __g._M_vertex))
			&& noexcept(std::swap(_M_edge, __g._M_edge))
			&& noexcept(std::swap(_M_graph, __g._M_graph))
			&& noexcept(std::swap(value_bad, __g.value_bad))
			&& noexcept(std::swap(predicate, __g.predicate)));
#endif

	/***
	  *  @brief  Destroy a graph using adjmatrix.
	*/
	~adjmatrix() __noexcept;

	/***
	  *  @brief  Check that __val whether a valid value.
	  *  @param  __val  The value to be checked.
	*/
#if __cplusplus < 201103L
	inline bool
	good_value(const value_type& __val) const;
#else
	inline bool
	good_value(const value_type& __val) const
		noexcept(noexcept(predicate(__val, value_bad)));

	inline bool
	good_value(value_type&& __val)
		noexcept(noexcept(predicate(__val, value_bad)));
#endif

	/***
	  *  @brief  Check that __val whether an invalid value.
	  *  @param  __val  The value to be checked.
	*/
#if __cplusplus < 201103L
	inline bool
	bad_value(const value_type& __val) const;
#else
	inline bool
	bad_value(const value_type& __val) const
		noexcept(noexcept(predicate(__val, value_bad)));

	inline bool
	bad_value(value_type&& __val) const
		noexcept(noexcept(predicate(__val, value_bad)));
#endif

	/***
	  *  @brief  Check that edge(__x, __y) whether a valid edge.
	  *  @param  __x  The begin vertex of the edge to be checked.
	  *  @param  __y  The end vertex of the edge to be checked.
	*/
	inline bool
	good_edge(size_type __x, size_type __y) const;

	/***
	  *  @brief  Check that edge(__x, __y) whether an invalid edge.
	  *  @param  __x  The begin vertex of the edge to be checked.
	  *  @param  __y  The end vertex of the edge to be checked.
	*/
	inline bool
	bad_edge(size_type __x, size_type __y) const;

	/***
	  *  @brief  Check that predicate(__l, __r) whether a valid predicate.
	  *  @param  __l  The lvalue of the predicate to be checked.
	  *  @param  __y  The rvalue of the predicate to be checked.
	*/
	template<typename _P>
	inline bool
	good_predicate(const value_type& __l, const value_type& __r,
		const _P& __p = _P()) const;
#if __cplusplus >= 201103L
	template<typename _P>
	inline bool
	good_predicate(value_type&& __l, value_type&& __r,
		_P&& __p = _P()) const;
#endif

	/***
	  *  @brief  Check that predicate(__l, __r) whether an invalid predicate.
	  *  @param  __l  The lvalue of the predicate to be checked.
	  *  @param  __y  The rvalue of the predicate to be checked.
	*/
	template<typename _P>
	inline bool
	bad_predicate(const value_type& __l, const value_type& __r,
		const _P& __p = _P()) const;
#if __cplusplus >= 201103L
	template<typename _P>
	inline bool
	bad_predicate(value_type&& __l, value_type&& __r,
		_P&& __p = _P()) const;
#endif

	/***
	  *  @brief  Operate that predicate(__l, __r) if it is a valid predicate.
	  *  @param  __l  The lvalue of the predicate to be checked.
	  *  @param  __y  The rvalue of the predicate to be checked.
	*/
	template<typename _O>
	inline value_type
	value_operation(const value_type& __l, const value_type& __r,
		const _O& __o = _O()) const;
#if __cplusplus >= 201103L
	template<typename _O>
	inline value_type
	value_operation(value_type&& __l, value_type&& __r,
		_O&& __o = _O()) const;
#endif

	/***
	  *  @brief  Clear the vertex_size, the edge_size and the graph.
	*/
	void
	clear();

	/***
	  *  @brief  Swap this graph and the other graph.
	  *  @param  __g  The graph to be swaped.
	*/
	void
	swap(adjmatrix<value_type, value_good>& __g);
#if __cplusplus >= 201103L
	void
	swap(adjmatrix<value_type, value_good>&& __g);
#endif

	/***
	  *  @brief  Assign infomation to this graph.
	  *  @param  __v  The vertex size of the graph to be assigned.
	  *  @param  __e  The edge size of the graph to be assigned.
	  *  @param  __g  The adjmatrix of the graph to be assigned.
	  *  @param  __b  The @value_bad of the graph to be assigned.
	  *  @param  __p  The @predicate of the graph to be assigned.
	*/
	void
	assign(size_type __v, size_type __e, const container_type& __g,
		const value_type& __b = value_type(),
		const value_good& __p = value_good());
#if __cplusplus >= 201103L
	void
	assign(size_type __v, size_type __e, container_type&& __g,
		value_type&& __b = value_type(), value_good&& __p = value_good());
#endif

	void
	assign(const adjmatrix<value_type, value_good>& __g);
#if __cplusplus >= 201103L
	void
	assign(adjmatrix<value_type, value_good>&& __g);
#endif

	/***
	  *  @brief  Return the number of the vertexes in the graph.
	*/
	inline size_type
	vertex_size() const __noexcept;

	/***
	  *  @brief  Return the number of the edges in the graph.
	*/
	inline size_type
	edge_size() const __noexcept;

	/***
	  *  @brief  Return the container of the graph.
	*/
	inline const container_type&
	adjmatrix_graph() const __noexcept;

	/***
	  *  @brief  Return the weight of the edge(__x, __y) of the graph.
	  *  @param  __x  The begin vertex of the edge.
	  *  @param  __y  The end vertex of the edge.
	*/
	inline value_type&
	edge_weight(size_type __x, size_type __y);

	inline const value_type&
	edge_weight(size_type __x, size_type __y) const;

	/***
	  *  @brief  Return the weight of the edge(__e) of the graph.
	  *  @param  __e  The edge.
	*/
	inline const value_type&
	edge_weight(edge __e) const;

	void
	insert_edge(size_type __x, size_type __y, value_type __w);

	inline void
	insert_edge(edge __e, value_type __w);

	inline void
	insert_edge(edge_w<value_type> __e);

	void
	erase_edge(size_type __x, size_type __y);

	inline void
	erase_edge(edge __e);

	inline void
	erase_edge();

	void
	insert_vertex(size_type __pos);

	void
	insert_vertex(); // insert at end. ...

	void
	erase_vertex(size_type __pos);

	void
	erase_vertex(); // erase at end. ...

	std::vector<edge>
	to_edge_array() const;

	std::vector<edge_w<value_type> >
	to_edge_w_array() const;

	size_type
	find_vertex(size_type __x, size_type __y = 0) const;

	edge
	find_edge(size_type __x = 0, size_type __y = 0) const;

	inline edge_w<value_type>
	find_edge_w(size_type __x = 0, size_type __y = 0) const;

	size_type
	indegree(size_type __pos) const;

	size_type
	outdegree(size_type __pos) const;

	inline size_type
	degree(size_type __pos) const;

	inline std::vector<size_type>
	dfs(size_type __pos = 0) const;

	inline std::vector<size_type>
	bfs(size_type __pos = 0) const;

	/***
	  *  @brief  Calculate the minimum spanning tree of this graph by
	  *  prim algorithm.
	*/
	std::vector<edge_w<value_type> >
	prim(size_type __pos = 0) const;

	/***
	  *  @brief  Calculate the minimum spanning tree of this graph by
	  *  kruskal algorithm.
	*/
	std::vector<edge_w<value_type> >
	kruskal() const;

	std::vector<value_type>
	dijkstra(size_type __pos = 0) const;

	std::vector<std::vector<value_type> >
	floyd() const;

	std::pair<std::vector<value_type>, bool>
	bellman_ford(size_type __pos = 0) const;

	std::pair<std::vector<value_type>, bool>
	spfa(size_type __pos = 0) const;

	std::vector<std::vector<size_type> >
	tarjan(size_type __pos = 0) const;

	std::vector<std::vector<size_type> >
	tarjan_all() const;

	static std::vector<std::vector<size_type> >
	tarjan_transform(const std::vector<std::vector<size_type> >& __v);

	std::pair<std::vector<size_type>, bool>
	toposort() const;

	adjmatrix<value_type, value_good>&
	operator = (const adjmatrix<value_type, value_good>& __g);

#if __cplusplus >= 201103L
	adjmatrix<value_type, value_good>&
	operator = (adjmatrix<value_type, value_good>&& __g);
#endif

	bool
	operator == (const adjmatrix<value_type, value_good>& __g) const;

	bool
	operator != (const adjmatrix<value_type, value_good>& __g) const;

#if __cplusplus >= 201103L
	bool
	operator == (adjmatrix<value_type, value_good>&& __g) const;

	bool
	operator != (adjmatrix<value_type, value_good>&& __g) const;
#endif

private:
	void
	_M_dfs(size_type __pos, std::vector<size_type>& __v,
		std::vector<bool>& __visited) const;

	void
	_M_bfs(size_type __pos, std::vector<size_type>& __v,
		std::vector<bool>& __visited) const;

	void
	_M_tarjan(size_type __pos, std::vector<bool>& __visited,
		std::vector<std::vector<size_type> >& __v, std::vector<scc_v>& __scc,
		std::stack<size_type>& __s, std::vector<bool>& __in_s) const;
};

template<typename _T, typename _P>
using __ga_t = graph_type::adjmatrix<_T, _P>;

template<typename _T, typename _P>
using graph_a = __ga_t<_T, _P>;

}

#endif /* _POL_GRAPH_ADJ_MATRIX_H */
