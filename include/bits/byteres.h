#ifndef _POL_BYTERES_H
#define _POL_BYTERES_H 1

namespace polaris
{

class byte_resource
{
public:
    unsigned char allocate();
};

byte_resource* global_byte_resource();

}

#endif /* _POL_BYTERES_H */
