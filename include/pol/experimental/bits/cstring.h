#ifndef _POL_CSTRING_H
#define _POL_CSTRING_H 1

#include <iosfwd>

namespace polaris
{

template<typename _CharT>
class basic_cstring
{
public:
	using char_type = _CharT;

	constexpr
	basic_cstring();

	constexpr
	basic_cstring(nullptr_t);

	constexpr
	basic_cstring(char_type*);

	constexpr
	basic_cstring(const char_type*);

	constexpr explicit
	operator char_type*();

	constexpr explicit
	operator const char_type*() const;

	constexpr char_type*
	data() noexcept;

	constexpr const char_type*
	data() const noexcept;

private:
	char_type* _M_start;
	char_type* _M_finish;
};

template<typename _CharT>
constexpr _CharT*
__termptr(_CharT*);

template<typename _CharT>
constexpr const _CharT*
__termptr(const _CharT*);

template<typename _CharT>
size_t length(const _CharT*);

template<typename _CharT>
size_t length(const basic_cstring<_CharT>&);

template<typename _CharT>
int compare(const basic_cstring<_CharT>&,
	const basic_cstring<_CharT>&);

template<typename _CharT>
bool
operator == (const basic_cstring<_CharT>&,
	const basic_cstring<_CharT>&);

template<typename _CharT>
bool
operator == (const basic_cstring<_CharT>&, const _CharT*);

template<typename _CharT>
bool
operator != (const basic_cstring<_CharT>&,
	const basic_cstring<_CharT>&);

template<typename _CharT>
bool
operator != (const basic_cstring<_CharT>&, const _CharT*);

template<typename _CharT>
bool
operator < (const basic_cstring<_CharT>& __lhs,
	const basic_cstring<_CharT>& __rhs);

template<typename _CharT>
bool
operator < (const basic_cstring<_CharT>& __lhs,
	const _CharT* __rhs);

template<typename _CharT>
[[deprecated]] std::basic_istream<_CharT>&
operator >> (std::basic_istream<_CharT>&, basic_cstring<_CharT>&);

template<typename _CharT>
std::basic_ostream<_CharT>&
operator << (std::basic_ostream<_CharT>&, const basic_cstring<_CharT>&);

}

#endif
