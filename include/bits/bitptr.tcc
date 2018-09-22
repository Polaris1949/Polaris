#ifndef _POL_BITPTR_TCC
#define _POL_BITPTR_TCC 1

namespace polaris
{

bit_ptr::
bit_ptr(byte_type* __ptr, level_type __lev)
    : _M_ptr{__ptr + __lev / char_bit}, _M_lev{__lev % char_bit}
{}

bool
bit_ptr::
empty() const
{ return this->_M_ptr == nullptr; }

bit_ptr::
operator bool() const
{ return (*this->_M_ptr >> this->_M_lev) & true; }

bool
bit_ptr::
operator! () const
{ return !this->operator bool(); }

bit_ptr&
bit_ptr::
operator = (bool __x)
{
    if (__x) *this->_M_ptr |= (true << this->_M_lev);
    else *this->_M_ptr &= ~(true << this->_M_lev);
    return *this;
}

}

#endif
