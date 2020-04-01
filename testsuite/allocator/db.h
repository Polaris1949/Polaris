#ifndef _POL_TEST_ALLOC_DB_H
#define _POL_TEST_ALLOC_DB_H 1

#include <limits>
#define __ASSERT_SIZE(X) static_assert((X) <= std::numeric_limits<size_t>::max())

#include <pol/type>
using namespace pol::size_literals;

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
