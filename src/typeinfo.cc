#include <pol/typeinfo>
// #include <pol/error>
#include <pol/format>
#define POL_LOG 1
#if POL_LOG
#include <pol/log>
#endif

namespace pol
{

std::string
demangle(const char* __s)
{
#if __GNUC__
    int __status;
    auto __deleter = [](char* __p)
    { if (__p) free(__p); };
    std::unique_ptr<char, decltype(__deleter)> __d
    (abi::__cxa_demangle(__s, nullptr, nullptr, &__status), __deleter);
    if (__status != 0)
	{
#if POL_DEPRECATED
        cfmt_lock();
        error<std::runtime_error>("assert",
            cformat("demangle abi error: {}", __status));
		cfmt_unlock();
#elif POL_EXCEPTIONS
        throw std::runtime_error{format("demangle abi error: {}", __status)};
#elif POL_LOG
        pol::error_easy(format("demangle abi error: {}", __status));
#else
        return {};
#endif // POL
	}
    return __d.get();
#else
    return __s;
#endif // __GNUC__
}

std::string
demangle(const std::string& __s)
{ return demangle(__s.data()); }

}
