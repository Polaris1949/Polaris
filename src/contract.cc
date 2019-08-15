#include <polaris/contract>
#include <iostream>

namespace pol
{

uint8_t __ctr_flag{1};

void __ctr_set_conti(bool __x) noexcept
{
    __ctr_flag &= 0x7f; __ctr_flag |= (__x << 7);
}

bool __ctr_get_conti() noexcept
{ return __ctr_flag & 0x80; }

void __ctr_set_level(uint8_t __x) noexcept
{
    expect(__x < 4, "out of range", "bad contract level");
    __ctr_flag &= 0x80; __ctr_flag |= __x;
}

uint8_t __ctr_get_level() noexcept
{ return __ctr_flag & 0x7f; }

contract::
contract(const char* __mode, uint8_t __level, bool __pred,
    const char* __type, const char* __msg, srcloc_t __loc) noexcept
    : _M_mode{__mode ? __mode : "bad"}, _M_level{__level}, _M_pred{__pred},
        _M_type{__type}, _M_msg{__msg}, _M_loc{__loc}
{ }

const char*
contract::
mode() const noexcept
{ return this->_M_mode; }

uint8_t
contract::
level() const noexcept
{ return this->_M_level; }

bool
contract::
predicate() const noexcept
{ return this->_M_pred; }

const char*
contract::
type() const noexcept
{ return this->_M_type; }

const char*
contract::
message() const noexcept
{ return this->_M_msg; }

srcloc_t
contract::
location() const noexcept
{ return this->_M_loc; }

const char*
contract::
file() const noexcept
{ return this->_M_loc.file_name(); }

const char*
contract::
function() const noexcept
{ return this->_M_loc.function_name(); }

uint32_t
contract::
line() const noexcept
{ return this->_M_loc.line(); }

uint32_t
contract::
column() const noexcept
{ return this->_M_loc.column(); }

const char*
__ctr_level_str(uint8_t __lev) noexcept
{
    switch (__lev)
    {
        case 0: return "axiom";
        case 1: return "default";
        case 2: return "audit";
        case 3: return "always";
        default: return "bad";
    }
}

bool
__ctr_check(contract&& __c)
{
    uint8_t __gl = __ctr_get_level();
    uint8_t __cl = __c.level();
    bool __p = __c.predicate();

    if ((!__p) && ((__gl == 1 && __cl == 1)
        || (__gl == 2 && (__cl == 1 || __cl == 2))
        || (__gl == 3) || (__cl == 3)))
    {
        std::cerr << "contract violation occurred\n";
        std::cerr << "      mode: " << __c.mode() << '\n';
        std::cerr << "     level: " << static_cast<uint>(__c.level())
            << " (" << __ctr_level_str(__c.level()) << ")\n";
        if (__c.type())
            std::cerr << "      type: " << __c.type() << '\n';
        if (__c.message())
            std::cerr << "   message: " << __c.message() << '\n';

        std::cerr << "      file: " << __c.file() << " (" << __c.line()
            << ':' << __c.column() << ")\n";
        std::cerr << "  function: " << __c.function() << '\n';

        if (!__ctr_get_conti())
            std::terminate();
    }

    return __p;
}

bool
assert(bool __pred, const char* __type, const char* __msg,
    uint8_t __level, srcloc_t __loc)
{ return __ctr_check({"assert", __level, __pred, __type, __msg, __loc}); }

bool
expect(bool __pred, const char* __type, const char* __msg,
    uint8_t __level, srcloc_t __loc)
{ return __ctr_check({"expect", __level, __pred, __type, __msg, __loc}); }

bool
ensure(bool __pred, const char* __type, const char* __msg,
    uint8_t __level, srcloc_t __loc)
{ return __ctr_check({"ensure", __level, __pred, __type, __msg, __loc}); }

}
