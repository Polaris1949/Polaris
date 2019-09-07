#include <polaris/dynamic>
#include <iostream>

namespace pol
{
POL_DEF_INFO_TYPE(int)
POL_DEF_INFO_TYPE(char)
}

int main()
{
    pol::dynamic x{'x'};
}
