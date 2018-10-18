#include <iostream>
#include <polaris/boolean>

int main()
{
	bool x{true};
	pol::boolean b{x};
	std::cout << b << '\n';
	std::cout << sizeof(b) << '\n';
}
