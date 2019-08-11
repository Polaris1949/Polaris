#include <polaris/contract>
#include <iostream>

namespace pol
{

uint8_t __contr_flag{1};

void __contr_set_conti(uint8_t __x) noexcept
{ __contr_flag &= 0x7f; __contr_flag |= (__x << 7); }

uint8_t __contr_get_conti() noexcept
{ return (__contr_flag & 0x80) >> 7; }

void __contr_set_level(uint8_t __x) noexcept
{ __contr_flag &= 0x80; __contr_flag |= __x; }

uint8_t __contr_get_level() noexcept
{ return __contr_flag & 0x7f; }

bool __contr_check(const char* __f, bool __p, const char* __m,
    uint8_t __l, srcloc_t __s)
{
    if (uint8_t __cl = __contr_get_level();
        __l && __cl && __l <= __cl && !__p)
    {
        std::cerr << __f << " failed: ";
        if (__m && *__m) std::cerr << __m;
        else std::cerr << "contract violation";
        std::cerr << "\n    in " << __s.file_name() << ':'
            << __s.line() << ':' << __s.column() << ": "
            << __s.function_name() << '\n';

        if (__contr_get_conti() == 0)
            std::terminate();
    }

    return __p;
}

bool assert(bool __p, const char* __m, uint8_t __l, srcloc_t __s)
{ return __contr_check("assert", __p, __m, __l, __s); }

bool expect(bool __p, const char* __m, uint8_t __l, srcloc_t __s)
{ return __contr_check("expect", __p, __m, __l, __s); }

bool ensure(bool __p, const char* __m, uint8_t __l, srcloc_t __s)
{ return __contr_check("ensure", __p, __m, __l, __s); }

}
