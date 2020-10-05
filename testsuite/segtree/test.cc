#include <pol/segment_tree>
#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

struct df
{
	int operator() (int x, int y) const
	{
		return std::max(x, y);
	}
};

struct mf
{
	void operator() (pol::segment_tree_node<int, void>* r, int x) const
	{
		r->data()=x;
	}
};

pol::segment_tree<int, void, df> st;

void dfs(pol::segment_tree_node<int, void>* r)
{
	std::cout<<'['<<r->begin()<<", "<<r->end()<<"): "<<r->data()<<std::endl;
	if (r->left()) dfs(r->left());
	if (r->right()) dfs(r->right());
}

int main()
{
	std::vector<int> v;
	srand((unsigned)time(nullptr));

	for (int i=0; i<20; ++i)
		v.push_back(rand()%100);

	st.construct(0, v.size(), v);

	std::cout << "------ TEST #1 ------" << std::endl;
	dfs(st.root());

	for (int i=0; i<20; ++i)
	{
		int x=rand()%20;
		int y=rand()%20;
		st.modify(x, y, rand()%100, mf());
	}

	std::cout << "------ TEST #2 ------" << std::endl;
	dfs(st.root());
	return 0;
}
