#include <iostream>
#include <vector>
#include <polaris/range_observer>
using namespace std;
using namespace polaris;

vector<int> v;

int main()
{
	for (int i=0; i<10; ++i)
		v.push_back(i);
	
	range_observer<decltype(v)> ro(v, -5);
	cout<<ro[10]<<endl;
	return 0;
}
