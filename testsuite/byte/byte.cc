#include <iostream>
#include <pol/byte>

int main()
{
	pol::basic_byte<pol::unsigned_tag> bs(255);

	std::cout << bs << std::endl;
	std::cout << sizeof(bs) << std::endl;
	std::cout << sizeof(pol::basic_byte<pol::signed_tag>) << std::endl;
	std::cout << bs-1 << std::endl;
	std::cout << --bs << std::endl;
	std::cout << (bs=0) << std::endl;
	std::cout << (bs+=100) << std::endl;

	pol::exbyte<pol::unsigned_tag> eb1(10);
	std::cout << eb1 << std::endl;
	pol::exbyte<pol::unsigned_tag> eb2(std::move(eb1));
	std::cout << eb2 << std::endl;
	eb2 = 15;
	std::cout << eb2 << std::endl;
	pol::exbyte<pol::unsigned_tag> eb3(bs);
	std::cout << eb3 << std::endl;

	pol::unsigned_byte b2(eb3);
	std::cout << (b2*(pol::unsigned_byte(eb2)/5)) << std::endl;

	return 0;
}
