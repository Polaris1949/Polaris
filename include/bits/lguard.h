#ifndef _POL_BITS_LGUARD_H
#define _POL_BITS_LGUARD_H

namespace polaris
{

template<typename _Tp>
class literal_guard
{
public:
	typedef _Tp value_type;
	
private:
	_Tp _M_storage;
	
public:
	literal_guard() noexcept;
	literal_guard(value_type __arg) noexcept;
	literal_guard(const literal_guard& __arg) noexcept = default;
	literal_guard(literal_guard&& __arg) noexcept = default;
	
	~literal_guard() noexcept = default;
	
	literal_guard&
	operator = (value_type __arg) noexcept;
	literal_guard&
	operator = (const literal_guard& __arg) noexcept = default;
	literal_guard&
	operator = (literal_guard&& __arg) noexcept = default;
	
	operator value_type&() noexcept;
	operator value_type() const noexcept;
};

typedef literal_guard<bool>               bool_lg;
typedef literal_guard<char>               char_lg;
typedef literal_guard<signed char>        signed_char_lg;
typedef literal_guard<unsigned char>      unsigned_char_lg;
typedef literal_guard<short>              short_lg;
typedef literal_guard<unsigned short>     unsigned_short_lg;
typedef literal_guard<int>                int_lg;
typedef literal_guard<unsigned int>       unsigned_int_lg;
typedef literal_guard<long>               long_lg;
typedef literal_guard<unsigned long>      unsigned_long_lg;
typedef literal_guard<long long>          long_long_lg;
typedef literal_guard<unsigned long long> unsigned_long_long_lg;

template<typename _T>
literal_guard<_T>
make_lguard(_T __arg);

#if __cplusplus >= 201103L

inline literal_guard<unsigned long long>
operator"" _lg(unsigned long long __arg);

#endif

}

#endif
