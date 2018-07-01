#ifndef _POL_CSTRING_TCC
#define _POL_CSTRING_TCC 1

namespace polaris
{

constexpr
cstring::
cstring()
	: _M_data()
{
}

constexpr
cstring::
cstring(value_type __s)
	: _M_data(__s)
{
}

constexpr bool
cstring::
operator == (const cstring& __s) const
{
	const char *__p = this->_M_data, *__q = __s._M_data;
	
	while ((*__p) && (*__q) && (*__p++ == *__q++));
	
	if (*--__p == *--__q) return true;
	else return false;
}

constexpr
cstring::
operator value_type() const
{
	return _M_data;
}

std::ostream&
operator << (std::ostream& __out, const cstring& __s)
{
	__out << __s._M_data;
	return __out;
}

}

#endif
