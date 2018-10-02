#include <iostream>
#include <polaris/utility>

int main()
{
	std::cout << pol::min_of(0, 1, 2) << '\n';
	std::cout << pol::max_of(3, 4, 5) << '\n';
	return 0;
}
