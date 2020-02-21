#ifndef _POL_INTBINBASE_H
#define _POL_INTBINBASE_H 1

namespace pol
{

class basic_binary_integer
    : protected _Int_genbase
{
public:
    using size_type = size_t;
    using data_type = _Int_data;

protected:
    template<typename _Tp>
    void
    _M_initialize(_Tp __x);

    template<typename _Func>
    basic_binary_integer&
    _M_basic_calc(const basic_binary_integer& __x, _Func&& __f);

    basic_binary_integer&
    _M_basic_plus(const basic_binary_integer& __x);

    basic_binary_integer&
    _M_basic_minus(const basic_binary_integer& __x);

    basic_binary_integer&
    _M_basic_multiplies(const basic_binary_integer& __x);

public:
    basic_binary_integer() = default;

    basic_binary_integer(char __x);

    basic_binary_integer(unsigned char __x);

    basic_binary_integer(int __x);

    basic_binary_integer(unsigned int __x);

    basic_binary_integer(long long __x);

    basic_binary_integer(unsigned long long __x);

    //basic_binary_integer(size_tag_t, size_type __n);

    size_type size() const;

    size_type capacity() const;

    data_type* data() const;

    basic_binary_integer&
    flip();

    basic_binary_integer&
    operator &= (const basic_binary_integer& __x);

    basic_binary_integer&
    operator |= (const basic_binary_integer& __x);

    basic_binary_integer&
    operator ^= (const basic_binary_integer& __x);

    basic_binary_integer
    operator & (const basic_binary_integer& __x) const;

    basic_binary_integer
    operator | (const basic_binary_integer& __x) const;

    basic_binary_integer
    operator ^ (const basic_binary_integer& __x) const;

    basic_binary_integer
    operator ~ () const;

    basic_binary_integer
    operator + (const basic_binary_integer& __x) const;

    basic_binary_integer
    operator - (const basic_binary_integer& __x) const;

    basic_binary_integer&
    operator += (const basic_binary_integer& __x);

    basic_binary_integer&
    operator -= (const basic_binary_integer& __x);
    
    void
    resize(size_type __s);
    
    data_type*
    begin() noexcept;
    
    data_type*
    end() noexcept;
};

using basic_bint = basic_binary_integer;

}

#endif
