#include <iostream>
#include <polaris/matrix>
using namespace std;
using namespace polaris;

matrix<int> m;

int main()
{
	int n=10;
	m.resize(n);
	
	for (int i=0;i<n;++i)
		for (int j=0;j<n;++j)
		{
			m[i].resize(n);
			m[i][j]=(i+1)*(j+1);
		}

	for (int i=0;i<n;++i)
	{
		for (int j=0;j<n;++j)
			cout<<m[i][j]<<' ';
		cout<<'\n';
	}
	
	return 0;
}
