#ifndef _POL_GADJLIST_H
#define _POL_GADJLIST_H 1

#include <iosfwd>
#include "../config.h"

namespace polairs
{

template<typename _Tp, typename _Pred>
class adjlist
{
private:
	template<typename _T, typename _P>
	class graph_iterator
	{
	public:
		typedef size_t           size_type;
		typedef _T               value_type;
		typedef _P               value_good;
		typedef adjlist<_T, _P>  base_type;
		typedef adjlist<_T, _P>* base_ptr;
		
	private:
		base_ptr _M_base;
		size_type _M_i, _M_j;
		
	public:
		graph_iterator();
		
		~graph_iterator() __noexcept;
		
		graph_iterator<_T, _P>& operator++ ();
		graph_iterator<_T, _P>& operator-- ();
		
		// graph_iterator<_T, _P> operator++ (int);
		// graph_iterator<_T, _P> operator-- (int);
		
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
	typedef _Tp                              value_type;
	typedef _Pred                            value_good;
	typedef size_t                           size_type;
	typedef std::list<std::list<_Tp> >       container_type;
	typedef graph_iterator<_Tp, _Pred>       iterator;
	typedef const graph_iterator<_Tp, _Pred> const_iterator;
	typedef _Tp*                             pointer;
	typedef const _Tp*                       const_pointer;
	typedef _Tp&                             reference;
	typedef const _Tp&                       const_reference;
	
public:
	// Data:
	static const size_type npos = static_cast<size_type>(-1);
	value_type value_bad;
	value_good predicate;
	
private:
	size_type _M_vertex, _M_edge;
	container_type _M_graph;
	
public:
	adjlist(size_type __v = 0, size_type __e = 0,
		const container_type& __g = container_type(),
		const value_type& __b = value_type(),
		const value_good& __p = value_good());
#if __cplusplus >= 201103L
	explicit
	adjmatrix(size_type __v, size_type __e, container_type&& __g,
		value_type&& __b, value_good&& __p);
#endif
	
	~adjlist() __noexcept;
};

}
/*
#if __cplusplus >= 201103L
template<typename _T, typename _P>
using __gl_ = graph_type::adjlist<_T, _P>;
#endif
*/
}

#endif
