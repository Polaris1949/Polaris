#ifndef _POL_BITADDR_H
#define _POL_BITADDR_H 1

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
    using byte_type = uchar;
    using level_type = uchar;
    using size_type = size_t;

private:
    byte_type* _M_ptr; // void* _M_ptr;
    level_type _M_lev; // size_t _M_lev;

public:
    constexpr bit_address() noexcept;
    constexpr bit_address(nullptr_t) noexcept;
    [[deprecated]] bit_address(byte_type* __ptr, level_type __n) noexcept;
    bit_address(byte_type* __ptr, size_type __n) noexcept;

    byte_type* byte_address() const noexcept;
    level_type bit_level() const noexcept;

    [[deprecated]] void assign(byte_type* __ptr, level_type __n) noexcept;
    void assign(byte_type* __ptr, size_type __n) noexcept;

    friend std::istream&
    operator >> (std::istream& __in, bit_address& __x);

    friend std::ostream&
    operator << (std::ostream& __out, const bit_address& __x);
};

class bit_ptr
{
public:
    using byte_type = unsigned char;
    using level_type = unsigned char;
    using size_type = size_t;

private:
    byte_type* _M_ptr;
    level_type _M_lev;

public:
    bit_ptr() = default;
    bit_ptr(nullptr_t);
    bit_ptr(byte_type* __ptr, level_type __n);
    bit_ptr(byte_type* __ptr, size_type __n);

    bool empty() const;
    explicit operator bool() const;
    bool operator* () const;
    bool operator! () const;

    void swap(bit_ptr& __o) noexcept;

    bit_ptr& operator = (bool __x);
};

class bit_ref
{
public:
    using byte_type = unsigned char;
    using level_type = unsigned char;
    using size_type = size_t;

private:
    bit_ptr _M_data;

public:
    bit_ref() = delete;
    bit_ref(byte_type& __ref, level_type __n);
    bit_ref(byte_type& __ref, size_type __n);

    explicit operator bool() const;
    bool operator! () const;

    bit_ref& operator = (bool __x);
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
