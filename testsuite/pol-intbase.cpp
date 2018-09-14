#define _POL_DEBUG 1
#define _POL_NEWLIB 1
#define _POL_DEPRECATED 1
#include <iostream>
#include <polaris/integer>
#include <vector>
using namespace std;
using namespace polaris;

_Int_genbase x;

int main()
{
	cout<<x.size()<<endl;
	return 0;
}
