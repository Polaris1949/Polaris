#ifndef _POL_TEST_ALLOC_DB_H
#define _POL_TEST_ALLOC_DB_H 1

#include <limits>
#define __ASSERT_SIZE(X) static_assert((X) <= std::numeric_limits<size_t>::max())

using ullong = unsigned long long int;
constexpr size_t carry = 1024;

constexpr size_t
operator""_B (ullong num)
{ return num; }

constexpr size_t
operator""_KB (ullong num)
{ return operator""_B(num) * carry; }

constexpr size_t
operator""_MB (ullong num)
{ return operator""_KB(num) * carry; }

constexpr size_t
operator""_GB (ullong num)
{ return operator""_MB(num) * carry; }

struct foo
{
    size_t id;
    static size_t count;
    foo() : id{count++} { std::cerr << "(" << id << ") foo ctor default\n"; }
    ~foo() { std::cerr << "(" << id << ") foo dtor\n"; }
};

size_t foo::count = 0;

#undef __ASSERT_SIZE
#endif
