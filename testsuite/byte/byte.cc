#include <iostream>
#include <pol/byte>

int main()
{
	pol::byte bs(255);

	std::cout << bs << std::endl;
	std::cout << sizeof(bs) << std::endl;
	std::cout << sizeof(pol::basic_byte<pol::signed_tag>) << std::endl;
	std::cout << bs+1 << std::endl;
	std::cout << --bs << std::endl;
	std::cout << (bs=0) << std::endl;
	std::cout << (bs+=100) << std::endl;

	return 0;
}
