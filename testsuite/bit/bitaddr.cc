#include <iostream>
#include <pol/bit_memory>

int main()
{
    pol::uchar n;
    pol::bit_address x{&n, 0};
    std::cout << x << '\n';
    std::cout << sizeof(pol::bit_address) << '\n';
    std::cout << alignof(pol::bit_address) << '\n';
    pol::bit_ref r{x};
    r = true;
    std::cout << (unsigned)n << '\n';
	pol::bit_address nl{nullptr};
	pol::uchar& k = nl.byte_reference();
	std::cout << (void*)&k << '\n'; // ok
	std::cout << (int)k << '\n'; // error: segmentation fault
}
