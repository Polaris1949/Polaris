#ifndef _POL_BITADDR_H
#define _POL_BITADDR_H 1

namespace pol
{

class bit_address
{
public:
    constexpr static const char separator{'@'};

    constexpr bit_address() noexcept;
    constexpr bit_address(nullptr_t) noexcept;
    constexpr bit_address(void* __ptr, size_t __n) noexcept;

    [[nodiscard]] void* byte_address() const noexcept;
    [[nodiscard]] ubyte_t& byte_reference() const;
    [[nodiscard]] size_t bit_level() const noexcept;

    [[nodiscard]] bool empty() const noexcept;
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

    [[nodiscard]] bool empty() const noexcept;
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
    constexpr bit_ref() = delete;
    constexpr bit_ref(nullptr_t) = delete;
    constexpr bit_ref(bit_address __a);
    constexpr bit_ref(const bit_ref& __x) noexcept;

    explicit operator bool() const;
    bool operator! () const;

    bit_ref& operator = (bool __x);
    bit_ref& operator = (const bit_ref& __x);

private:
    bit_address _M_adr;
};

}

#endif /* _POL_BITADDR_H */
