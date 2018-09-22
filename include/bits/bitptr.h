#ifndef _POL_BITPTR_H
#define _POL_BITPTR_H 1

namespace polaris
{

class bit_ptr
{
public:
    using byte_type = unsigned char;
    using level_type = unsigned char;

private:
    byte_type* _M_ptr;
    level_type _M_lev;

public:
    bit_ptr() = default;
    bit_ptr(byte_type* __ptr, level_type __lev);

    bool empty() const;
    explicit operator bool() const;
    bool operator! () const;

    bit_ptr& operator = (bool __x);
};

}

#endif /* _POL_BITPTR_H */
