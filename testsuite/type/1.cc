#define POL_TYPE_KEYWORDS 1
#define POL_FUNC_KEYWORDS 1
#include <polaris/type>
#include <iostream>

struct foo
{
    unsigned char bf0:4;
};

int main()
{
    //std::cout << byteof<int>() << '\n';
    //std::cout << bitof<char>() << '\n';
    foo x;
    std::cout << byteof(x) << '\n';
    std::cout << bitof(x) << '\n';
    std::cout << bitof(x.bf0) << '\n';
    std::cout << typeid(decltype(x.bf0)).name() << '\n';
}
