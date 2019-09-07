#ifndef _POL_INTGENBASE_H
#define _POL_INTGENBASE_H 1

namespace polaris
{

struct _Int_genbase
    : public _Int_base
{
    _Int_genbase();
    _Int_genbase(size_t __n);

    size_t size() const;
    size_t capacity() const;

    bool _M_set_element(size_t __pos, _Int_data __x);
    _Int_reference _M_get_element(size_t __pos);
    _Int_data _M_get_element(size_t __pos) const;

    void _M_reallocate(size_t __n);
};

}

#endif
