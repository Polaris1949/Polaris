#ifndef _POL_GALGO_H
#define _POL_GALGO_H 1

namespace polaris
{

class graph;

template<typename _Tp>
class g_operation
{
public:
	typedef _Tp function_object;
	typedef _Tp* function_pointer;
	
private:
	_Tp* _M_func;
	
public:
	g_operation(function_object& __f);
	auto operator() ();
};

void g_dfs(graph& __g);

auto g_dfs(graph& __g, g_operation<auto>& __f);

void g_bfs(graph& __g);

auto g_bfs(graph& __g, g_operation<auto>& __f);

void g_tarjan(graph& __g);

}

#endif
