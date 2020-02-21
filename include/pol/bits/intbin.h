#ifndef _POL_INTBIN_H
#define _POL_INTBIN_H 1

#include <vector>

namespace pol
{

using _Int_cont = std::vector<_Int_data>;
using _Int_cont_iter = _Int_cont::iterator;
using _Int_cont_citer = _Int_cont::const_iterator;

class binary_integer
{
public:
    using iterator = _Int_cont_iter;
    using const_iterator = _Int_cont_citer;

    binary_integer() = default;
    
    void
    set_element(size_type __pos, _Int_data __x);
    
    _Int_ref
    get_element(size_type __pos);
    
    _Int_data
    get_element(size_type __pos) const;
    
    binary_integer&
    operator &= (const binary_integer& __x);
    
    binary_integer&
    operator |= (const binary_integer& __x);
    
    binary_integer&
    operator += (const binary_integer& __x);
    
    binary_integer&
    flip();
    
    binary_integer&
    negate();
    
    binary_integer&
    increase();
    
    binary_integer&
    decrease();
    
    iterator
    begin();
    
    iterator
    end();
    
    const_iterator
    cbegin();
    
    const_iterator
    cend();
    
private:
    std::vector<_Int_data> _M_data;
    
    void _M_autofill(size_t __pos);
};

binary_integer
operator + (const binary_integer& __lhs, const binary_integer& __rhs);

binary_integer
__plus_impl(const binary_integer& __lhs, const binary_integer& __rhs);

}

#endif
