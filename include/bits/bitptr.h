#ifndef _POL_BITPTR_H
#define _POL_BITPTR_H 1

#include <iosfwd>

namespace polaris
{

class bit_ptr
{
public:
    using byte_type = unsigned char;
    using level_type = unsigned char;
    using size_type = std::size_t;

private:
    byte_type* _M_ptr;
    level_type _M_lev;

public:
    bit_ptr() = default;
    bit_ptr(byte_type* __ptr, level_type __lev);
    bit_ptr(byte_type* __ptr, size_type __lev);

    bool empty() const;
    explicit operator bool() const;
    bool operator! () const;

    bit_ptr& operator = (bool __x);
};

class bitfield_ptr
{
public:
    // TODO...

private:
    bit_ptr _M_left;
    bit_ptr _M_right;

public:
    // TODO...
};

}

#endif /* _POL_BITPTR_H */
