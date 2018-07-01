#include <polaris/byte>
#include <iostream>
using namespace polaris;
using namespace std;

int main()
{
	byte<unsigned_type> bs(255);
	cout << bs << endl;
	cout << sizeof(bs) << endl;
	cout << sizeof(byte<signed_type>) << endl;
	cout << bs-1 << endl;
	cout << --bs << endl;
	cout << (bs=0) << endl;
	cout << (bs+=100) << endl;
	return 0;
}
