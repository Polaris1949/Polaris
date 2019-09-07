#include <pol/bit_memory>
#include <iostream>

pol::bit_ref nullref()
{
	pol::bit_address a;
	return pol::bit_cast<pol::bit_ref>(a);
}

int main()
{
	pol::bit_ref x{nullref()}; // ok
	std::cout << x.address() << '\n'; // ok
    (bool)x; // error: segmentation fault
}
