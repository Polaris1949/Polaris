#include <pol/typeinfo>
#include <pol/error>
#include <pol/format>

namespace pol
{

std::string
demangle(const char* __s)
{
    int __status;
    auto __deleter = [](char* __p)
    { if (__p) free(__p); };
    std::unique_ptr<char, decltype(__deleter)> __d
    {abi::__cxa_demangle(__s, nullptr, nullptr, &__status), __deleter};
    if (__status != 0)
	{
		cfmt_lock();
        error<std::runtime_error>("assert",
            cformat("demangle abi error: {}", __status));
		cfmt_unlock();
	}
    return __d.get();
}

}
