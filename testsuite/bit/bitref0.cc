#include <pol/bit_memory>
#include <iostream>

int main() try
{
    pol::bit_ptr p{nullptr};
    *p;
}
catch (std::exception& e)
{ std::terminate(); }
