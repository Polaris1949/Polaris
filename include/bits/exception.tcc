#ifndef _POL_EXCEPTION_TCC
#define _POL_EXCEPTION_TCC 1

namespace polaris
{

inline void
assert_always(bool __c)
{
	if (!__c)
		throw std::runtime_error("assertion failed");
}

inline void
assert_always(bool __c, const std::string& __msg)
{
	if (!__c)
		throw std::runtime_error(std::string("assertion failed: ") + __msg);
}

inline void
assert_debug(bool __c)
{
#if POL_DEBUG
	assert_always(__c);
#endif
}

inline void
assert_debug(bool __c, const std::string& __msg)
{
#if POL_DEBUG
	assert_always(__c, __msg);
#endif
}

inline void
assert_if(bool __p, bool __c)
{
	if (__p) assert_always(__c);
}

inline void
assert_if(bool __p, bool __c, const std::string& __msg)
{
	if (__p) assert_always(__c, __msg);
}

}

#endif
