#ifndef _POL_BITADDR_TCC
#define _POL_BITADDR_TCC 1

#include <polaris/exception>

namespace polaris
{

constexpr
bit_address::
bit_address() noexcept
    : _M_ptr{nullptr}, _M_lev{}
{}

constexpr
bit_address::
bit_address(nullptr_t) noexcept
    : _M_ptr{nullptr}, _M_lev{}
{}

bit_address::
bit_address(byte_type* __ptr, level_type __n) noexcept
    : _M_ptr{__ptr}, _M_lev{__n}
{ pol::expect(__n >= 0 && __n < 8, "bad bit level"); }

bit_address::
bit_address(byte_type* __ptr, size_type __n) noexcept
    : _M_ptr{__ptr + __n / char_bit}, _M_lev{__n % char_bit}
{}

uchar*
bit_address::
byte_address() const noexcept
{ return this->_M_ptr; }

uchar
bit_address::
bit_level() const noexcept
{ return this->_M_lev; }

void
bit_address::
assign(byte_type* __ptr, level_type __n) noexcept
{
    pol::expect(__n >= 0 && __n < 8, "bad bit level");
    this->_M_ptr = __ptr;
    this->_M_lev = __n;
}

void
bit_address::
assign(byte_type* __ptr, size_type __n) noexcept
{
    this->_M_ptr = __ptr + __n / char_bit;
    this->_M_lev = __n % char_bit;
}

std::istream&
operator >> (std::istream& __in, bit_address& __x)
{
    void* __p; char __c; size_t __n;
    __in >> __p >> __c >> __n;

    if (__c == '@')
        __x.assign(static_cast<uchar*>(__p), __n);
    else
        __in.setstate(std::ios_base::failbit);

    return __in;
}

std::ostream&
operator << (std::ostream& __out, const bit_address& __x)
{
    __out << static_cast<void*>(__x.byte_address()) << '@'
        << static_cast<size_t>(__x.bit_level());
    return __out;
}

bit_ptr::
bit_ptr(byte_type* __ptr, level_type __n)
    : _M_ptr{__ptr}, _M_lev{__n}
{}

bit_ptr::
bit_ptr(byte_type* __ptr, size_type __n)
    : _M_ptr{__ptr + __n / char_bit}, _M_lev{__n % char_bit}
{}

bool
bit_ptr::
empty() const
{ return this->_M_ptr == nullptr; }

bit_ptr::
operator bool() const
{ return !this->empty(); }

bool
bit_ptr::
operator* () const
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

#endif /* _POL_BITADDR_TCC */
