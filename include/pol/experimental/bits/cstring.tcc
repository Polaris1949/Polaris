#ifndef _POL_CSTRING_TCC
#define _POL_CSTRING_TCC 1

namespace polaris
{

template<typename _CharT>
constexpr
basic_cstring<_CharT>::
basic_cstring()
	: _M_start(), _M_finish()
{ }

template<typename _CharT>
constexpr
basic_cstring<_CharT>::
basic_cstring(nullptr_t)
	: _M_start(nullptr), _M_finish(nullptr)
{ }

template<typename _CharT>
constexpr
basic_cstring<_CharT>::
basic_cstring(char_type* __s)
	: _M_start(__s), _M_finish(__termptr(__s))
{ }

template<typename _CharT>
constexpr
basic_cstring<_CharT>::
basic_cstring(const char_type* __s)
	: basic_cstring(const_cast<char_type*>(__s))
{ }

template<typename _CharT>
constexpr
basic_cstring<_CharT>::
operator char_type*()
{ return this->data(); }

template<typename _CharT>
constexpr
basic_cstring<_CharT>::
operator const char_type*() const
{ return this->data(); }

template<typename _CharT>
constexpr _CharT*
basic_cstring<_CharT>::
data() noexcept
{ return this->_M_start; }

template<typename _CharT>
constexpr const _CharT*
basic_cstring<_CharT>::
data() const noexcept
{ return this->_M_start; }

template<typename _CharT>
constexpr _CharT*
__termptr(_CharT* __s)
{
	if (__s == nullptr) return __s;
	while (*__s) ++__s;
	return __s;
}

template<typename _CharT>
constexpr const _CharT*
__termptr(const _CharT* __s)
{
	if (__s == nullptr) return __s;
	while (*__s) ++__s;
	return __s;
}

template<typename _CharT>
size_t
length(const _CharT* __s)
{ return __termptr(__s) - __s; }

template<typename _CharT>
int
compare(const basic_cstring<_CharT>& __lhs,
	const basic_cstring<_CharT>& __rhs)
{ return strcmp(__lhs.data(), __rhs.data()); }

template<typename _CharT>
bool
operator == (const basic_cstring<_CharT>& __lhs,
	const basic_cstring<_CharT>& __rhs)
{ return compare(__lhs, __rhs) == 0; }

template<typename _CharT>
bool
operator == (const basic_cstring<_CharT>& __lhs,
	const _CharT* __rhs)
{ return __lhs == basic_cstring<_CharT>(__rhs); }

template<typename _CharT>
bool
operator < (const basic_cstring<_CharT>& __lhs,
	const basic_cstring<_CharT>& __rhs)
{ return compare(__lhs, __rhs) < 0; }

template<typename _CharT>
bool
operator < (const basic_cstring<_CharT>& __lhs,
	const _CharT* __rhs)
{ return __lhs < basic_cstring<_CharT>(__rhs); }

template<typename _CharT>
bool
operator > (const basic_cstring<_CharT>& __lhs,
	const basic_cstring<_CharT>& __rhs)
{ return compare(__lhs, __rhs) > 0; }

template<typename _CharT>
std::basic_ostream<_CharT>&
operator << (std::basic_ostream<_CharT>& __out,
	const basic_cstring<_CharT>& __s)
{
	__out << __s.data();
	return __out;
}

}

#endif
