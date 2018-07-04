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

	return 0;
}
