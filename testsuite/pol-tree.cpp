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
    return __s;
    //return __s.substr(std::string("/cygdrive/d/develop/lib/polaris/").size());
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
/*
int f(int x) {std::cout<<"f"<<x<<'\n';return 10+x;}
int g(int x) {std::cout<<"g"<<x<<'\n';return 20+x;}

struct int_t : public debug_helper
{
    int data;

    int_t() {POL_DBG_FUN("Ctor")}
    int_t(int x) : data{x} {POL_DBG_FUN("Value Ctor")}
    int_t(const int_t& x) : data{x} {POL_DBG_FUN("Copy Ctor")}
    ~int_t() noexcept {POL_DBG_FUN("Dtor")}
    operator int() const {POL_DBG_FUN("Data Copy") return data;}
    operator int&() {POL_DBG_FUN("Data Ref") return data;}
};

auto dbg = [](const std::string& x){std::cerr<<x<<'\n';};

int_t plus1(int_t& k) {dbg("In plus1");return ++k;}
int_t plus2(int_t k) {dbg("In plus2");return k;}
void work(int_t a, int_t b) {dbg("In work");std::cerr<<a<<' '<<b<<'\n';}
*/
int main()
{
    /*
    {
        int_t a{0};
        work(plus1((dbg("Plus1 Init"), a)), plus2((dbg("Plus2 Init"), a)));
    }
    std::cout<<"------------\n";
    {
        int_t a{0};
        work(plus2((dbg("Plus2 Init"), a)), plus1((dbg("Plus1 Init"), a)));
    }
    */
    auto p = (new pol::tree_node_base)->ptr_unique();
}
