#include <iostream>
#include <vector>
#include <array>
#include <forward_list>
#include <list>
#include <polaris/sequence>
#define int long long
using namespace std;
using namespace polaris;

sequence<int> s;

signed main()
{
//	static_assert(has_push_front<std::list<int>>);
//	static_assert(!has_push_front<std::array<int, 2>>);
//	static_assert(!has_push_back<std::forward_list<int>>);
//	static_assert(has_push_back<std::list<int>>);
	
	int n=50;
	s.resize(n);
	s[0]=1;s[1]=1;
	for (int i=2;i<n;++i)
		s[i]=s[i-2]+s[i-1];
	for (int i=0;i<n;++i)
		cout<<s[i]<<' ';
	cout<<endl;
	
//	cout<<s.size()<<endl;
	return 0;
}
