#include <pol/bit_memory>
#include <iostream>

namespace pol
{

ubyte_t&
bit_address::
byte_reference() const noexcept
{ return *static_cast<ubyte_t*>(this->byte_address()); }

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
    return this->_M_adr.byte_reference()
        & (1 << this->_M_adr.bit_level());
}

bit_ptr::
operator bit_address() const noexcept
{ return this->_M_adr; }

bit_address
bit_ptr::
address() const noexcept
{ return this->_M_adr; }

bit_ptr&
bit_ptr::
operator = (const bit_address& __a) noexcept
{
	this->_M_adr = __a;
	return *this;
}

std::istream&
operator >> (std::istream& __in, bit_ptr& __x)
{
	bit_address __a;
	__in >> __a;
	__x = __a;
	return __in;
}

std::ostream&
operator << (std::ostream& __out, const bit_ptr& __x)
{
	__out << __x.address();
	return __out;
}

bit_ref&
bit_ref::
operator = (bool __x) noexcept
{
    if (__x) this->_M_adr.byte_reference()
        |= (1 << this->_M_adr.bit_level());
    else this->_M_adr.byte_reference()
        &= ~(1 << this->_M_adr.bit_level());
    return *this;
}

bit_ref&
bit_ref::
operator = (const bit_ref& __x) noexcept
{ return *this = bool(__x); }

bit_ref::
operator bool() const noexcept
{
    return this->_M_adr.byte_reference()
        & (1 << this->_M_adr.bit_level());
}

bool
bit_ref::
operator! () const noexcept
{ return !bool(*this); }

bit_ref::
operator bit_address() const noexcept
{ return this->_M_adr; }

bit_address
bit_ref::
address() const noexcept
{ return this->_M_adr; }

std::istream&
operator >> (std::istream& __in, bit_ref& __x)
{
	bool __v;
	__in >> __v;
	__x = __v;
	return __in;
}

std::ostream&
operator << (std::ostream& __out, const bit_ref& __x)
{
	__out << bool(__x);
	return __out;
}

bitmem_ptr::
bitmem_ptr(nullptr_t) noexcept
    : _M_ptr{nullptr}, _M_size{0}
{ }

bitmem_ptr::
bitmem_ptr(pointer __p, size_type __n) noexcept
    : _M_ptr{__p}, _M_size{__n}
{ }

bitmem_ptr::
operator bool() const noexcept
{ return bool(this->_M_ptr); }

bit_ptr
bitmem_ptr::
ptr() const noexcept
{ return this->_M_ptr; }

size_t
bitmem_ptr::
size() const noexcept
{ return this->_M_size; }

}
