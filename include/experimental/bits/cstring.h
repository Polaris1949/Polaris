#ifndef _POL_CSTRING_H
#define _POL_CSTRING_H 1

#include <iosfwd>

namespace polaris
{

class cstring;

std::ostream&
operator << (std::ostream& __out, const cstring& __s);

class cstring
{
public:
	typedef const char* value_type;

private:
	const char* _M_data;

public:
	constexpr
	cstring();

	constexpr
	cstring(value_type __s);

	constexpr bool
	operator == (const cstring& __s) const;

	constexpr explicit
	operator value_type() const;

	friend std::ostream&
	operator << (std::ostream& __out, const cstring& __s);
};

}

#endif
