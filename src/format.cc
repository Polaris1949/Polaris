#include <pol/format>
#include <pol/file>

namespace pol
{

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

namespace __format
{
std::string buffer;
#if POL_DEPRECATED
std::mutex mutex;
#endif
}

#if POL_DEPRECATED
void
cfmt_lock()
{ __format::mutex.lock(); }

void
cfmt_unlock()
{ __format::mutex.unlock(); }
#endif

}
