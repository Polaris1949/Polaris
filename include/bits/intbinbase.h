#ifndef _POL_INTBINBASE_H
#define _POL_INTBINBASE_H 1

namespace polaris
{

class basic_binary_integer
	: protected _Int_genbase
{
public:
	typedef size_t size_type;
	typedef _Int_data data_type;
	
protected:
	template<typename _Tp, typename _Req = require<std::is_integral<_Tp>>>
	void _M_initialize(_Tp __x);
	
public:
	basic_binary_integer() = default;
	
	basic_binary_integer(char __x);
	
	basic_binary_integer(unsigned char __x);
	
	basic_binary_integer(int __x);
	
	basic_binary_integer(unsigned int __x);
	
	basic_binary_integer(long long __x);
	
	basic_binary_integer(unsigned long long __x);
	
	basic_binary_integer(size_type_tag_t, size_type __n);
	
	size_type size() const;
	
	size_type capacity() const;
	
	data_type* data() const;
	
	basic_binary_integer&
	flip();
	
	basic_binary_integer&
	operator &= (const basic_binary_integer& __x);
	
	basic_binary_integer&
	operator |= (const basic_binary_integer& __x);
	
	basic_binary_integer&
	operator ^= (const basic_binary_integer& __x);
	
	basic_binary_integer
	operator & (const basic_binary_integer& __x) const;
	
	basic_binary_integer
	operator | (const basic_binary_integer& __x) const;
	
	basic_binary_integer
	operator ^ (const basic_binary_integer& __x) const;
	
	basic_binary_integer
	operator ~ () const;
	
	basic_binary_integer
	operator + (const basic_binary_integer& __x) const;
	
	basic_binary_integer&
	operator += (const basic_binary_integer& __x);
};

}

#endif
