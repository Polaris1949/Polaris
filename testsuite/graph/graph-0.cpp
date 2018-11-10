#include <cstdio>
#include "graph"
using namespace std;
using namespace stdext;
using namespace stdext::graph_type;

uint n, e;
adjmatrix<uint> ga;
vector<vector<uint> > v;

int main()
{
	freopen("try0.in", "r", stdin);
	
	uint i, j, x, y, w;
	cin >> n >> e;
	v.resize(n, vector<uint>(n));
	
	for (i=0; i<e; i++)
	{
		cin >> x >> y >> w;
		v[x][y]=w;
	}
	
	ga.assign(n, e, v);
	
	v=ga.adjmatrix_graph();
	
	for (i=0; i<v.size(); i++)
	{
		for (j=0; j<v[i].size(); j++)
		{
			cout << v[i][j] << " ";
		}
		cout << endl;
	}
	
	cout << "------" << endl;
	
	ga.insert_vertex(2); // ok
	
	v=ga.adjmatrix_graph();
	
	for (i=0; i<v.size(); i++)
	{
		for (j=0; j<v[i].size(); j++)
		{
			cout << v[i][j] << " ";
		}
		cout << endl;
	}
	
	cout << "------" << endl;
	
	ga.erase_vertex(2);
	
	v=ga.adjmatrix_graph();
	
	for (i=0; i<v.size(); i++)
	{
		for (j=0; j<v[i].size(); j++)
		{
			cout << v[i][j] << " ";
		}
		cout << endl;
	}
	
	fclose(stdin);	
	return 0;
}

/* data:
5 10
0 1 1
0 3 1
0 4 1
1 2 1
2 0 1
2 4 1
3 1 1
3 4 1
4 1 1
4 2 1
*/
