#define POL_DEBUG 1
#include <polaris/exception>

int main()
{
    pol::assert_debug(false, "test");
    return 0;
}
