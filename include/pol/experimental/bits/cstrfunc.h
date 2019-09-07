#ifndef _POL_CSTRFUNC_H
#define _POL_CSTRFUNC_H 1

#include <polaris/type_traits>

namespace polaris
{

template<typename _CharT>
char_sint_t<_CharT>
__strcmp_impl(const _CharT*, const _CharT*);

template<typename _CharT>
int
strcmp(const _CharT*, const _CharT*);

}

#endif
