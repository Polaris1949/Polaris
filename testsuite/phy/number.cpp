#include <iostream>
#include <string>
#include <physics/number>
namespace phy = physics;

int main()
{
	double x, y;
	x = 5000000000;
	y = 7000000000;
	double z = x + y;
	std::cout << phy::sc_number(z) << std::endl;
	return 0;
}
