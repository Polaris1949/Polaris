#include <pol/error>
#include <iostream>

int main()
{
    std::cout << pol::__err_pretty_type("std::runtime_error") << '\n';
}