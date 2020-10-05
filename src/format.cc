#include <pol/format>
#include <pol/file>

namespace pol
{

#if POL_OLD
std::ostream&
operator << (std::ostream& __out, const ftext& __x)
{
    c_file_t* __dev{c_file(__out)};
    fmt::print(__dev, __x._M_style, __x._M_text);
    return __out;
}

std::ofstream&
operator << (std::ofstream& __out, const ftext& __x)
{
    c_file_t* __dev{c_file(__out)};
    fmt::print(__dev, __x._M_style, __x._M_text);
    return __out;
}
#else
std::ostream&
operator << (std::ostream& __out, const ftext& __x)
{
    __out << __x._M_text;
    return __out;
}
#endif

}
