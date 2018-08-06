#include <experimental/source_location>
#include <string>
#include <iostream>
#define POL_DEBUG 1

#if POL_DEBUG

class debug_helper
{
protected:
    size_t _M_dbgid;
    static size_t _S_dbgnum;

public:
    debug_helper()
        : _M_dbgid(_S_dbgnum++)
    {}
};

size_t debug_helper::_S_dbgnum{};

std::string short_file(const std::string& __s)
{
    return __s.substr(std::string("/cygdrive/d/develop/lib/polaris/").size());
}

#define POL_DBG_FUN(MSG) \
{ \
    std::experimental::source_location __sl = \
        std::experimental::source_location::current(); \
    std::cerr << short_file(__sl.file_name()) << ": " << __sl.line() << ": " \
        << __sl.function_name() << ": {" << (this->_M_dbgid) << "} "<< (MSG); \
    if (this->_M_dbgid >= debug_helper::_S_dbgnum) \
        std::cerr << " !!!!!!"; \
    std::cerr << '\n'; \
}

#define POL_DBG_VAR(MSG) debug_var(std::experimental::source_location \
    ::current(), this->_M_dbgid, (MSG))

void debug_var(const std::experimental::source_location& __sl,
    size_t __id, const std::string& __x)
{
    std::cerr << short_file(__sl.file_name()) << ": " << __sl.line() << ": "
        << __sl.function_name() << ": {" << __id << "} " << __x << '\n';
}
#else
#define POL_DBG_SL(MSG)
#define POL_DBG_VAR(MSG) 0
#endif

#include <cerrno>
#include <polaris/tree>

int main()
{
    auto p = (new pol::tree_node_base)->ptr_unique();
    return 0;
}
