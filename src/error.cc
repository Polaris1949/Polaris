#include <pol/error>

namespace pol
{

// Consider set log mode to default
uint8_t __eh_method{0};

std::string
__err_pretty_type(const std::string& __e)
{
    std::string __ret{__e};
    size_t __pos;
    // Need optimizing
    while ((__pos = __ret.find("::")) != npos)
        __ret.erase(0, __pos + 2);
    __pos = 0;
    while ((__pos = __ret.find('_', __pos)) != npos)
        __ret[__pos] = ' ';
    return __ret;
}

}
