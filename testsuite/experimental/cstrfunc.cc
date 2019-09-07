#include <polaris/version>
#include <polaris/type>
#include <polaris/experimental/cstring>
#include <iostream>

int main()
{
    std::cout << pol::strcmp("aaa", "aaaz") << '\n';
}
