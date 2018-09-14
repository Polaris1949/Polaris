#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include "../graph.impl/galgo.h"
#include "../graph.impl/galgo.tcc"
using namespace std;
using namespace polaris;

ofstream fout;

struct ex_op
{
	size_t operator() ()
	{
		return rand();
	}
};
ex_op eo;
g_operation<ex_op> go{eo};
namespace polaris{class graph{};}
graph g;

struct unify_out{
	template<typename _T>
	unify_out& operator<<(_T __arg)
	{
		cout<<__arg;
		fout<<__arg;
		return *this;
	}
}out;

int main()
{
	fout.open("test-galgo.log");
	srand((unsigned)time(nullptr));
	cout<<g_dfs(g, go)<<endl;
	out<<'\n';
	return 0;
}
