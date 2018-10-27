#include <fstream>
#include <iostream>
#include <polaris/byte_stream>

pol::byte_stream<std::ifstream> bin;
pol::byte_stream<std::ofstream> bout;

int main()
{
	unsigned x{}, y{};
	char c[20]="ABCDE";
	c[6]='F';c[7]='G';c[8]='H';c[9]='\0';

	bout.open("stream.tmp", std::ios_base::out|std::ios_base::trunc);
	x=19260817u; y=66662333u;
	bout << x << y << c << '\0' << c+6;
	bout.close();

	bin.open("stream.tmp", std::ios_base::in);
	bin >> x >> y;
	std::cout << x << ' ' << y << '\n';
	char d[20];
	bin >> d;
	std::cout << d << '\n';
	bin >> d;
	std::cout << d << '\n';

	return 0;
}
