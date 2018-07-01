#include <fstream>
#include <iostream>
#include <polaris/byte_stream>
using namespace std;
using namespace polaris;

int main()
{
	byte_stream<ofstream> bout;
	bout.open("test-byte_stream.txt", ios_base::out|ios_base::trunc);
	char a='x';
	bout << a << '\n';
	bout.close();
	byte_stream<ifstream> bin;
	bin.open("test-byte_stream.txt", ios_base::in);
	a='y';
	cout << a << endl;
	bin >> a;
	cout << a << endl;
	return 0;
}
