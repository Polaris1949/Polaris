#ifndef _POL_INTBIN_TCC
#define _POL_INTBIN_TCC 1

namespace pol
{

_Int_cont_iter
binary_integer::
begin()
{
    return this->_M_data.begin();
}

_Int_cont_iter
binary_integer::
end()
{
    return this->_M_data.end();
}

binary_integer&
binary_integer::
flip()
{
    iterator __it = this->_M_data.begin();

    while (__it != this->_M_data.end())
    {
        *__it = ~*__it;
        ++__it;
    }

    return *this;
}

binary_integer&
binary_integer::
negate()
{
    this->flip();
    this->increase();
    return *this;
}

binary_integer&
binary_integer::
increase()
{
    size_t __pos = 0;
    while (__pos < this->size())
    {
        
    }
}

binary_integer
operator + (const binary_integer& __lhs, const binary_integer& __rhs)
{
    if (__lhs.size()<__rhs.size())
        return __plus_impl(__lhs, __rhs);
    else
        return __plus_impl(__rhs, __lhs);
}

binary_integer
__plus_impl(const binary_integer& __lhs, const binary_integer& __rhs)
{
    binary_integer __ret;
    _Int_exdata __tmp = 0;
    size_t __pos;
    for (__pos = 0; __pos < __lhs.size(); ++__pos)
    {
        __tmp += _Int_exdata(__lhs[__pos]) + _Int_exdata(__rhs[__pos]);
        __ret.push_back(_Int_data(__tmp));
        __tmp >>= bitof(_Int_data);
    }
    for (__pos = __lhs.size(); __pos < __rhs.size(); ++__pos)
    {
        __tmp += _Int_exdata(__rhs[__pos]);
        __ret.push_back(_Int_data(__tmp));
        __tmp >>= bitof(_Int_data);
    }
    if (__tmp > 0) __ret.push_back(_Int_data(__tmp));
    return __ret;
}

binary_integer
operator - (const binary_integer& __lhs, const binary_integer& __rhs)
{
    return __lhs + (-__rhs);
}

}

#endif
