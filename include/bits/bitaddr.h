#ifndef _POL_BITADDR_H
#define _POL_BITADDR_H 1

#include <polaris/type>
#include <iosfwd>

namespace polaris
{

class bit_address;
class bit_ptr;
class bit_ref;
class bitfield_ptr;
class bitfield_ref;

std::istream&
operator >> (std::istream& __in, bit_address& __x);

std::ostream&
operator << (std::ostream& __out, const bit_address& __x);

class bit_address
{
public:
    constexpr static const char separator{'@'};

    constexpr bit_address() noexcept;
    constexpr bit_address(nullptr_t) noexcept;
    constexpr bit_address(void* __ptr, size_t __n) noexcept;

    void* byte_address() const noexcept;
    ubyte_t& byte_reference() const;
    size_t bit_level() const noexcept;

    bool empty() const noexcept;
    void assign(void* __ptr, size_t __n) noexcept;

    friend std::istream&
    operator >> (std::istream& __in, bit_address& __x);

    friend std::ostream&
    operator << (std::ostream& __out, const bit_address& __x);

private:
    void* _M_ptr;
    size_t _M_lev;
};

class bit_ptr
{
public:
    constexpr bit_ptr() noexcept = default;
    constexpr bit_ptr(nullptr_t) noexcept;
    constexpr bit_ptr(bit_address __a) noexcept;

    bool empty() const noexcept;
    explicit operator bool() const noexcept;
    bool operator! () const noexcept;
    bit_ref operator* ();
    bool operator* () const;

private:
    bit_address _M_adr;
};

class bit_ref
{
public:
    constexpr bit_ref() noexcept = delete;
    constexpr bit_ref(nullptr_t) noexcept = delete;
    constexpr bit_ref(bit_address __a) noexcept;

    explicit operator bool() const;
    bool operator! () const;

    bit_ref& operator = (bool __x);

private:
    bit_address _M_adr;
};

class bitfield_ptr
{
public:
    // TODO...

private:
    bit_ptr _M_left;
    bit_ptr _M_right;

public:
    // TODO...
};

}

#endif /* _POL_BITADDR_H */
