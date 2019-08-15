#include <polaris/exception>
#include <stdexcept>
#include <iostream>

int main()
{
    pol::exception e{std::runtime_error{"dove"}};
    std::cout << e.name() << ": " << e.what() << '\n';
}
