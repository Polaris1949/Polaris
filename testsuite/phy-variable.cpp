#include <iostream>
#include <string>
#include <physics/variable>
namespace phy = physics;

int main()
{
	phy::variable m;
	phy::variable vbig("V", 5, "cm^3");
	phy::variable rho("rho", 2.1, "g/cm^3");
	m.name() = "m";
	m = rho * vbig;
	std::cout << m << std::endl;
	return 0;
}
