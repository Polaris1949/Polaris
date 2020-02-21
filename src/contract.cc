#include <pol/contract>
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

void __ctr_violate(contract&& __c)
{
    uint8_t __gl{__ctr_get_level()};
    uint8_t __cl{__c.level_n()};

    if ((__gl == 1 && __cl == 1)
        || (__gl == 2 && (__cl == 1 || __cl == 2))
        || (__gl == 3) || (__cl == 3))
    {
        std::cerr << "contract violation occurred\n";
        std::cerr << "      mode: " << __c.mode()
            << " (" << static_cast<uint32_t>(__c.mode_n()) << ")\n";
        std::cerr << "     level: " << __c.level()
            << " (" << static_cast<uint32_t>(__c.level_n()) << ")\n";
        if (__c.code() > 0)
            std::cerr << "      code: " << __c.code() << '\n';
        if (!__c.type().empty())
            std::cerr << "      type: " << __c.type() << '\n';
        if (!__c.message().empty())
            std::cerr << "   message: " << __c.message() << '\n';

        std::cerr << "      file: " << __c.file() << " (" << __c.line()
            << ':' << __c.column() << ")\n";
        std::cerr << "  function: " << __c.function() << '\n';

        if (!__ctr_get_conti())
            std::terminate();
    }
}

void
__assert_violate(const std::string& __type, const std::string& __msg,
    uint16_t __code, uint8_t __level, srcloc_t __loc)
{ __ctr_violate({0, __level, __code, __type, __msg, __loc}); }

void
__expect_violate(const std::string& __type, const std::string& __msg,
    uint16_t __code, uint8_t __level, srcloc_t __loc)
{ __ctr_violate({1, __level, __code, __type, __msg, __loc}); }

void
__ensure_violate(const std::string& __type, const std::string& __msg,
    uint16_t __code, uint8_t __level, srcloc_t __loc)
{ __ctr_violate({2, __level, __code, __type, __msg, __loc}); }

}
