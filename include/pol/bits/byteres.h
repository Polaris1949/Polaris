#ifndef _POL_BYTERES_H
#define _POL_BYTERES_H 1

namespace pol
{

class byte_resource
{
public:
    using pointer = void*;
    using size_type = size_t;

    [[nodiscard]] pointer allocate(size_type __n);
    void deallocate(pointer __p);
    [[nodiscard]] pointer reallocate(pointer __p, size_type __n);
};

byte_resource* default_byte_resource();

}

#endif /* _POL_BYTERES_H */
