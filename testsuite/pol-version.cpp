#define POL_DEPRECATED 1
#include <iostream>
#include <polaris/version>
using namespace std;
using namespace polaris;

int main()
{
	cout << __POLLIB__ << '.' << __POLLIB_MINOR__ \
		<< '.' << __POLLIB_PATCHLEVEL__ << endl;
	return 0;
}
