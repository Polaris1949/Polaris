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
    uint8_t __cl{__c.level()};

    if ((__gl == 1 && __cl == 1)
        || (__gl == 2 && (__cl == 1 || __cl == 2))
        || (__gl == 3) || (__cl == 3))
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
}

}
