#ifndef _POL_BOOLOBS_H
#define _POL_BOOLOBS_H 1

#include <iosfwd>

namespace polaris
{

class basic_bool_observer
{
public:
    using size_type = std::size_t;

private:
    bool b0 : 1;
    bool b1 : 1;
    bool b2 : 1;
    bool b3 : 1;
    bool b4 : 1;
    bool b5 : 1;
    bool b6 : 1;
    bool b7 : 1;

public:
    bool
    at(size_type __pos) const;

    bool
    operator[] (size_type __pos) const noexcept;

    void
    set(size_type __pos);

    void
    reset(size_type __pos);

    void
    flip(size_type __pos);

    friend std::istream&
	operator >> (std::istream& __in, basic_bool_observer& __x);

    friend std::ostream&
	operator << (std::ostream& __out, const basic_bool_observer& __x);
};

template<typename _Tp>
class bool_observer
{
public:
    using value_type = _Tp;
    using size_type = std::size_t;

private:
    inline constexpr static size_type _S_len = sizeof(_Tp);

    union _Impl
    {
        _Tp _M_data;
        basic_bool_observer _M_obs[_S_len];

        _Impl() = default;
        _Impl(const value_type& __x);
    };

    _Impl _M_impl;

public:
    bool
    at(size_type __pos) const;

    bool
    operator[] (size_type __pos) const noexcept;
};

}

#endif /* _POL_BOOLOBS_H */
