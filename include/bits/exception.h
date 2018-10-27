#ifndef _POL_EXCEPTION_H
#define _POL_EXCEPTION_H 1

namespace polaris
{

inline void
assert_always(bool __c POL_SOURCE_LOCATION_DECL);

inline void
assert_always(bool __c, const std::string& __msg POL_SOURCE_LOCATION_DECL);

inline void
assert_debug(bool __c POL_SOURCE_LOCATION_DECL);

inline void
assert_debug(bool __c, const std::string& __msg POL_SOURCE_LOCATION_DECL);

inline void
assert_if(bool __p, bool __c POL_SOURCE_LOCATION_DECL);

inline void
assert_if(bool __p, bool __c, const std::string& __msg
    POL_SOURCE_LOCATION_DECL);

}

#endif /* _POL_EXCEPTION_H */
