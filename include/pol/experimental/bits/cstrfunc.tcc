#ifndef _POL_CSTRFUNC_TCC
#define _POL_CSTRFUNC_TCC 1

namespace polaris
{

template<typename _CharT>
char_sint_t<_CharT>
__strcmp_impl(const _CharT* p1, const _CharT* p2)
{
    using _CharU = char_uint_t<_CharT>;

    const _CharU* s1 = (const _CharU*) p1;
    const _CharU* s2 = (const _CharU*) p2;
    _CharU c1, c2;

    do
    {
        c1 = (_CharU) *s1++;
        c2 = (_CharU) *s2++;
        if (c1 == '\0') return c1 - c2;
    }
    while (c1 == c2);

    return c1 - c2;
}

template<typename _CharT>
int
strcmp(const _CharT* p1, const _CharT* p2)
{
    char_sint_t<_CharT> ret = __strcmp_impl(p1, p2);
    return ret == 0 ? 0 : ret < 0 ? -1 : 1;
}

}

#endif
