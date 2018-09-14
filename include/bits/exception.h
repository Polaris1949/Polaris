#ifndef _POL_EXCEPTION_H
#define _POL_EXCEPTION_H 1

namespace polaris
{

inline void
assert_always(bool __c);

inline void
assert_always(bool __c, const std::string& __msg);

inline void
assert_debug(bool __c);

inline void
assert_debug(bool __c, const std::string& __msg);

inline void
assert_if(bool __p, bool __c);

inline void
assert_if(bool __p, bool __c, const std::string& __msg);

}

#endif
