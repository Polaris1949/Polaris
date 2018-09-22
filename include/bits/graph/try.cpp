#include <cstdio>
#include <iostream>
#include <windows.h>
#include <graph>
using namespace std;
using namespace stdext;
using namespace stdext::graph_type;

int n, e;
adjmatrix<uint>::container_type g;
adjmatrix<uint> ga(1,1,std::move(g),uint(),adjmatrix<uint>::value_good());
vector<edge_w<uint> > mst;
vector<uint> dist;
pair<vector<uint>, bool> dist1;
vector<vector<uint> > dist2;
vector<vector<adjmatrix<uint>::size_type> > scc;

int main()
{
	cout << adjmatrix<uint>().value_bad << endl;
	//Sleep(2000);
	
	/*
	edge e;
	e.begin() = 1216;
	e.end() = 1220;
	cout << e << endl;
	
	edge_w<int> ew;
	cin >> ew;
	cout << ew << endl;
	*/
	
	freopen("g19.in", "r", stdin);
	
	int i, j, x, y, s;
	
	cin >> n >> e;
	g.resize(n, std::vector<uint>(n));
	
	for (i=0; i<e; i++)
	{
		cin >> x >> y;
		--x;--y;
		g[x][y]=1;
		cout << "init>" << x << " " << y << endl;
	}
	
	fclose(stdin);
	
	ga.assign(n, e, g);
	
	mst=ga.prim();
	s=0;
	
	for (i=0; i<mst.size(); ++i)
	{
		cout << mst[i].begin() << ' ' << mst[i].end()
			<< ' ' << mst[i].weight() << endl;
		s+=mst[i].weight();
	}
	
	cout << s << endl;//47,ok
	
	cout << "----" << endl;
	
	edge temp;
	
	while (1)
	{
		temp=ga.find_edge(temp.begin(), temp.end()+1);
		
		if (temp==edge(adjmatrix<uint>::npos, adjmatrix<uint>::npos)) break;
		
		cout << temp.begin() << ' ' << temp.end() << endl;
	}
	
	cout << "----" << endl;
	
	mst=ga.kruskal();
	s=0;
	
	for (i=0; i<mst.size(); ++i)
	{
		cout << mst[i].begin() << ' ' << mst[i].end()
			<< ' ' << mst[i].weight() << endl;
		s+=mst[i].weight();
	}
	
	cout << s << endl;//47,ok
	
	cout << "----" << endl;
	
	dist=ga.dijkstra();//0 18 23 26 4 23,ok
	
	for (i=0; i<dist.size(); ++i)
	{
		cout << dist[i] << endl;
	}
	
	cout << "----" << endl;
	
	dist2=ga.floyd();//0 18 23 26 4 23...,ok
	
	for (i=0; i<dist2.size(); ++i)
	{
		for (j=0; j<dist2[i].size(); ++j)
		{
			cout << dist2[i][j] << ' ';
		}
		cout << endl;
	}
	
	cout << "----" << endl;
	
	dist1=ga.bellman_ford();
	
	for (i=0; i<dist1.first.size(); ++i)
	{
		cout << (dist1.first)[i] << endl;
	}
	
	cout << dist1.second << endl;
	
	cout << "----" << endl;
	
	dist1=ga.spfa();
	
	for (i=0; i<dist1.first.size(); ++i)
	{
		cout << (dist1.first)[i] << endl;
	}
	
	cout << dist1.second << endl;
	
	cout << "----" << endl;
	
	scc=ga.tarjan_all();
	
	for (i=0; i<scc.size(); i++)
	{
		for (j=0; j<scc[i].size(); j++)
		{
			cout << scc[i][j] << ' ';
		}
		cout << endl;
	}
	
	cout << "----" << endl;
	
	scc=ga.tarjan_transform(scc);
	
	for (i=0; i<scc.size(); i++)
	{
		for (j=0; j<scc[i].size(); j++)
		{
			cout << scc[i][j] << ' ';
		}
		cout << endl;
	}
	
	cout << "----" << endl;
	
	dist1=ga.toposort();
	
	for (i=0; i<dist1.first.size(); ++i)
	{
		cout << (dist1.first)[i] << endl;
	}
	
	cout << dist1.second << endl;
	
	cout << "OK" << endl;
	return 0;
}

/* data:
5 6
1 2
2 3
2 4
2 5
3 1
4 5
*/
