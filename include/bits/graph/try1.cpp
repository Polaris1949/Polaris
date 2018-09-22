#include <vector>
#include <iostream>
using namespace std;

vector<int> v;

int main()
{
	int i;
	
	for (i=0; i<10; i++)
	{
		v.push_back(i);
	}
	
	v.erase(v.begin()+2);
	
	for (i=0; i<v.size(); i++)
	{
		cout << v[i] << endl;
	}
	
	return 0;
}
