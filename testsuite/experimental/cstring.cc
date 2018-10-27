#include <iostream>
#include <polaris/experimental/cstring>
using namespace std;
using namespace polaris;

int main()
{
	cstring cs("ui");
	string s("ui2");
	cout << cs << endl;
	cout << s.substr(0, 2).c_str() << endl;
	cout << (cs==s.substr(0, 2).c_str()) << endl;//
	return 0;
}
