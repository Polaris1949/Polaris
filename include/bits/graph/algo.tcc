#ifndef _POL_GRAPH_ALGO_TCC
#define _POL_GRAPH_ALGO_TCC 1

#include <vector>
#include <queue>

namespace polaris
{

inline namespace __graph_detail
{

struct _Gpath_helper
{
	std::vector<std::size_t> path;

	void operator() (std::size_t __pos)
	{ this->path.push_back(__pos); }
};

}

template<typename _Graph>
std::vector<std::size_t>
dfs(const _Graph& __g, std::size_t __pos)
{
	_Gpath_helper __f;
	dfs(__g, __pos, __f);
	return __f.path;
}

template<typename _Graph, typename _Func>
void
dfs(const _Graph& __g, std::size_t __pos, _Func __f)
{
	if (__pos >= __g.vertex_size()) return;
	std::vector<bool> __vis{__g.vertex_size()};
	__dfs_impl(__g, __pos, __vis, __f);
}

template<typename _Graph, typename _Func>
void
__dfs_impl(const _Graph& __g, std::size_t __pos,
	std::vector<bool>& __vis, _Func& __f)
{
	__f(__pos);
	__vis[__pos] = true;

	for (std::size_t __i{}; __i < __g.vertex_size(); ++__i)
		if (__g.good_edge(__pos, __i) && !__vis[__i])
			__dfs_impl(__g, __i, __vis, __f);
}

template<typename _Graph>
std::vector<std::size_t>
bfs(const _Graph& __g, std::size_t __pos)
{
	_Gpath_helper __f;
	bfs(__g, __pos, __f);
	return __f.path;
}

template<typename _Graph, typename _Func>
void
bfs(const _Graph& __g, std::size_t __pos, _Func __f)
{
	if (__pos >= __g.vertex_size()) return;
	std::vector<bool> __vis{__g.vertex_size()};
	__bfs_impl(__g, __pos, __vis, __f);
}

template<typename _Graph, typename _Func>
void
__bfs_impl(const _Graph& __g, std::size_t __pos,
	std::vector<bool>& __vis, _Func& __f)
{
	std::queue<std::size_t> __q;

	__f(__pos);
	__vis[__pos] = true;
	__q.push(__pos);

	while (!__q.empty())
	{
		std::size_t __i{__q.front()};
		__q.pop();

		for (std::size_t __j{}; __j < __g.vertex_size(); ++__j)
			if (__g.good_edge(__i, __j) && !__vis[__j])
			{
				__f(__j);
				__vis[__j] = true;
				__q.push(__j);
			}
	}
}

}

#endif /* _POL_GRAPH_ALGO_TCC */
