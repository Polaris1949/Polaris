#ifndef _POL_GADJMATRIX_H
#define _POL_GADJMATRIX_H 1

namespace polaris
{

template<typename _Tp, typename _Mat = matrix<_Tp>, \
	typename _Comp = std::less<_Tp>>
class g_adjmatrix
{
	typedef typename _Mat::sequence_type _Seq;
	static_assert(std::is_same<_Tp, typename _Mat::value_type>::value);
	
public:
	typedef _Tp value_type;
	typedef _Mat container_type;
	typedef size_t size_type;
	
private:
	_Mat _M_storage;
	
public:
	g_adjmatrix();
	
	void resize(size_type __new_size, const value_type& __x);
};

}

#endif
