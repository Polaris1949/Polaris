#ifndef _POL_VWRAP_H
#define _POL_VWRAP_H 1

#include <iosfwd>

namespace pol
{

template<typename _Tp>
class var_wrapper
{
public:
    typedef _Tp value_type;
    typedef _Tp& reference;

private:
    _Tp _M_data;

public:
    var_wrapper();

    var_wrapper(const value_type& __x);

    virtual ~var_wrapper();

    value_type data() const;

    reference data();

    operator value_type() const;

    operator reference();

    template<typename _T>
    friend std::istream&
    operator >> (std::istream& __in, var_wrapper<_T>& __x);

    template<typename _T>
    friend std::ostream&
    operator << (std::ostream& __out, const var_wrapper<_T>& __x);
};

#define POL_VW_MAKE_TAG_TYPE(__class, __type) \
    class __class : public pol::var_wrapper<__type> \
    { \
    public: \
        using pol::var_wrapper<__type>::var_wrapper; \
    };

}

#endif
