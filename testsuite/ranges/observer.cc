#include <iostream>
#include <vector>
#include <polaris/range_observer>

std::vector<int> v;

int main()
{
	for (int i=0; i<10; ++i)
		v.push_back(i);

	pol::range_observer ro{v, -5};
	std::cout << ro[10] << '\n';
	return 0;
}
