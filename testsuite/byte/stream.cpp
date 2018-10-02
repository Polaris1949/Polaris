#include <fstream>
#include <iostream>
#include <polaris/byte_stream>
using namespace std;
using namespace polaris;

byte_stream<ifstream> bin;
byte_stream<ofstream> bout;

int main()
{
	unsigned x{}, y{};
	char c[20]="ABCDE";
	c[6]='F';c[7]='G';c[8]='H';c[9]='\0';

	bout.open("test-byte_stream.txt", ios_base::out|ios_base::trunc);
	x=3242398579u; y=2811149670u;
	bout << x << y << c << '\0' << c+6;
	bout.close();

	bin.open("test-byte_stream.txt", ios_base::in);
	bin >> x >> y;
	cout << x << ' ' << y << endl;
	char d[20];
	bin >> d;
	cout << d << endl;
	bin >> d;
	cout << d << endl;

	return 0;
}
