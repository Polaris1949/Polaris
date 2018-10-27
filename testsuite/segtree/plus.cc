#include <polaris/segment_tree>
#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

struct df
{
	int operator() (int x, int y) const
	{
		return max(x, y);
	}
};

struct mf
{
	void operator() (segment_tree_node<int, void>* r, int x) const
	{
		r->data()=x;
	}
};

segment_tree<int, void, df> st;

void dfs(segment_tree_node<int, void>* r)
{
	cout<<'['<<r->begin()<<", "<<r->end()<<"): "<<r->data()<<endl;
	if (r->left()) dfs(r->left());
	if (r->right()) dfs(r->right());
}

int main()
{
	vector<int> v;
	srand((unsigned)time(nullptr));

	for (int i=0; i<20; ++i)
		v.push_back((rand()+rand())%rand());

	st.construct(0, v.size(), v);

	dfs(st.root());

	for (int i=0; i<20; ++i)
	{
		int x=rand();
		int y=i+rand()%20;
		st.modify(x, y, rand(), mf());
	}

	dfs(st.root());
	return 0;
}
