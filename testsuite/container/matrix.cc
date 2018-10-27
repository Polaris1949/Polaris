#include <iostream>
#include <polaris/matrix>

pol::matrix<int> m;

int main()
{
	pol::size_t m;
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
			std::cout<<m[i][j]<<' ';
		std::cout<<'\n';
	}

	return 0;
}
