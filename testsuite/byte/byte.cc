#include <iostream>
#include <polaris/byte>

int main()
{
	pol::byte<pol::unsigned_type> bs(255);

	std::cout << bs << std::endl;
	std::cout << sizeof(bs) << std::endl;
	std::cout << sizeof(pol::byte<pol::signed_type>) << std::endl;
	std::cout << bs-1 << std::endl;
	std::cout << --bs << std::endl;
	std::cout << (bs=0) << std::endl;
	std::cout << (bs+=100) << std::endl;

	pol::exbyte<pol::unsigned_type> eb1(10);
	std::cout << eb1 << std::endl;
	pol::exbyte<pol::unsigned_type> eb2(std::move(eb1));
	std::cout << eb2 << std::endl;
	eb2 = 15;
	std::cout << eb2 << std::endl;
	pol::exbyte<pol::unsigned_type> eb3(bs);
	std::cout << eb3 << std::endl;

	pol::unsigned_byte b2(eb3);
	std::cout << (b2*(pol::unsigned_byte(eb2)/5)) << std::endl;

	return 0;
}
