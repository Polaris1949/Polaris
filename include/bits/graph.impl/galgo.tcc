#ifndef _POL_GALGO_TCC
#define _POL_GALGO_TCC 1

namespace polaris
{

template<typename _Tp>
g_operation<_Tp>::
g_operation(function_object& __f)
	: _M_func(&__f)
{
}

template<typename _Tp>
auto
g_operation<_Tp>::
operator() ()
//	-> decltype(_M_func())
{
	return _M_func->operator()();
}

auto g_dfs(graph& __g, g_operation<auto>& __f)
//	-> decltype(__f())
{
	return __f();
//	return __g_dfs_impl(0);
}

auto __g_dfs_impl(size_t __pos)
{
	/*
	if (__v[__pos]) return __f();
	
	for (size_t __e : __edge)
	{
		if (!__v[__e]) __g_dfs_impl(__e);
	}
	*/
	return __pos;
}

}

#endif
