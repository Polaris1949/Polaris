#include <polaris/typeinfo>
#include <iostream>

int main()
{
    std::cout << POL_CHECK_TYPEOF(std::move(1)) << '\n';
    std::cout << POL_CHECK_TYPE(int[0]) << '\n';
    std::cout << POL_CHECK_TYPE(int[]) << '\n';
    std::cout << POL_CHECK_TYPE(int[-1u]) << '\n';
}
