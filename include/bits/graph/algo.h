#ifndef _POL_GRAPH_ALGO_H
#define _POL_GRAPH_ALGO_H 1

namespace polaris
{

template<typename _Graph>
std::vector<std::size_t>
dfs(const _Graph& __g, std::size_t __pos);

template<typename _Graph, typename _Func>
void
dfs(const _Graph& __g, std::size_t __pos, _Func __f);

template<typename _Graph, typename _Func>
void
__dfs_impl(const _Graph& __g, std::size_t __pos,
	std::vector<bool>& __vis, _Func& __f);

}

#endif /* _POL_GRAPH_ALGO_H */
