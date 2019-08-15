#ifndef _POL_BITADDR_TCC
#define _POL_BITADDR_TCC 1

#include <iostream>

namespace polaris
{

constexpr
bit_address::
bit_address() noexcept
    : _M_ptr{}, _M_lev{}
{ }

constexpr
bit_address::
bit_address(nullptr_t) noexcept
    : _M_ptr{nullptr}, _M_lev{}
{ }

constexpr
bit_address::
bit_address(void* __ptr, size_t __n) noexcept
    : _M_ptr{static_cast<ubyte_t*>(__ptr) + __n / char_bit},
        _M_lev{__n % char_bit}
{ }

void*
bit_address::
byte_address() const noexcept
{ return this->_M_ptr; }

ubyte_t&
bit_address::
byte_reference() const
{ return *static_cast<ubyte_t*>(this->byte_address()); }

size_t
bit_address::
bit_level() const noexcept
{ return this->_M_lev; }

bool
bit_address::
empty() const noexcept
{ return this->_M_ptr == nullptr; }

void
bit_address::
assign(void* __ptr, size_t __n) noexcept
{
    this->_M_ptr = static_cast<ubyte_t*>(__ptr) + __n / char_bit;
    this->_M_lev = __n % char_bit;
}

std::istream&
operator >> (std::istream& __in, bit_address& __x)
{
    void* __p; char __c; size_t __n;
    __in >> __p >> __c >> __n;

    if (__c == bit_address::separator)
        __x.assign(__p, __n);
    else
        __in.setstate(std::ios_base::failbit);

    return __in;
}

std::ostream&
operator << (std::ostream& __out, const bit_address& __x)
{
    __out << __x.byte_address() << bit_address::separator << __x.bit_level();
    return __out;
}

constexpr
bit_ptr::
bit_ptr(nullptr_t) noexcept
    : _M_adr{nullptr}
{}

constexpr
bit_ptr::
bit_ptr(bit_address __a) noexcept
    : _M_adr{__a}
{}

bool
bit_ptr::
empty() const noexcept
{ return this->_M_adr.empty(); }

bit_ptr::
operator bool() const noexcept
{ return !this->_M_adr.empty(); }

bool
bit_ptr::
operator! () const noexcept
{ return this->_M_adr.empty(); }

bit_ref
bit_ptr::
operator* ()
{ return bit_ref{this->_M_adr}; }

bool
bit_ptr::
operator* () const
{
    return (this->_M_adr.byte_reference() >> this->_M_adr.bit_level())
        & ubyte_t{1};
}

constexpr
bit_ref::
bit_ref(bit_address __a)
    : _M_adr{__a}
{ expect(!__a.empty(), "null bit address"); }

constexpr
bit_ref::
bit_ref(const bit_ref& __a) noexcept
    : _M_adr{__a._M_adr}
{ }

bit_ref&
bit_ref::
operator = (bool __x)
{
    if (__x) this->_M_adr.byte_reference()
        |= (ubyte_t{1} << this->_M_adr.bit_level());
    else this->_M_adr.byte_reference()
        &= ~(ubyte_t{1} << this->_M_adr.bit_level());
    return *this;
}

bit_ref&
bit_ref::
operator = (const bit_ref& __x)
{ return *this = bool(__x); }

bit_ref::
operator bool() const
{
    return this->_M_adr.byte_reference()
        & (ubyte_t{1} << this->_M_adr.bit_level());
}

bool
bit_ref::
operator! () const
{ return !bool(*this); }

}

#endif /* _POL_BITADDR_TCC */
