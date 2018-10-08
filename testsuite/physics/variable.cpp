#include <iostream>
#include <string>
#include <physics/variable>

int main()
{
	phy::variable m;
	phy::variable V("V", 5, "cm^3");
	phy::variable rho("rho", 2.1, "g/cm^3");
	m.name() = "m";
	m = rho * V;
	std::cout << m << std::endl;
	return 0;
}
