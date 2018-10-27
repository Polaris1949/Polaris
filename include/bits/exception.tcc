#ifndef _POL_EXCEPTION_TCC
#define _POL_EXCEPTION_TCC 1

namespace polaris
{

inline void
assert_always(bool __c POL_SOURCE_LOCATION_DEFN)
{
    if (!__c)
        throw std::runtime_error(POL_SOURCE_LOCATION_ARGU
			"assertion failed");
}

inline void
assert_always(bool __c, const std::string& __msg POL_SOURCE_LOCATION_DEFN)
{
    if (!__c)
        throw std::runtime_error(POL_SOURCE_LOCATION_ARGU
			std::string("assertion failed: ") + __msg);
}

inline void
assert_debug(bool __c POL_SOURCE_LOCATION_DEFN)
{
#if POL_DEBUG
    assert_always(__c POL_SOURCE_LOCATION_PARA);
#endif
}

inline void
assert_debug(bool __c, const std::string& __msg POL_SOURCE_LOCATION_DEFN)
{
#if POL_DEBUG
    assert_always(__c, __msg POL_SOURCE_LOCATION_PARA);
#endif
}

inline void
assert_if(bool __p, bool __c POL_SOURCE_LOCATION_DEFN)
{
    if (__p)
	    assert_always(__c POL_SOURCE_LOCATION_PARA);
}

inline void
assert_if(bool __p, bool __c, const std::string& __msg
    POL_SOURCE_LOCATION_DEFN)
{
    if (__p)
	    assert_always(__c, __msg POL_SOURCE_LOCATION_PARA);
}

}

#endif /* _POL_EXCEPTION_TCC */
