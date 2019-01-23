#include <polaris/type_traits>
#include <functional>
#include <iostream>

int main()
{
	std::cout << pol::is_operable_v<std::plus<>, int, int> << '\n';
	std::cout << pol::is_plusable_v<int> << '\n';
	std::cout << pol::is_plusable_with_v<int, short> << '\n';
	std::cout << pol::is_plus_assignable_v<int> << '\n';
	std::cout << pol::is_equality_comparable_v<int> << '\n';
	std::cout << pol::is_less_than_comparable_v<int> << '\n';
	return 0;
}
