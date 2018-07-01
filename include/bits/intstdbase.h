#ifndef _POL_INTSTDBASE_H
#define _POL_INTSTDBASE_H 1

namespace polaris
{

struct _Int_stdbase
#if _POL_NEWLIB
	: public _Int_base
#endif
{
	typedef unsigned int    _Radix;
	
	static _Int_allocator _S_default_alloc;
	
#if !_POL_NEWLIB
	_Int_data* _M_dataplus;
	size_t _M_length;
	size_t _M_capacity;
#endif
	bool _M_sign;
	
	_Int_stdbase();
	
	_Int_stdbase(int __arg);
	
	_Int_stdbase(unsigned int __arg);
	
	_Int_stdbase(long int __arg);
	
	_Int_stdbase(unsigned long int __arg);
	
	_Int_stdbase(long long int __arg);
	
	_Int_stdbase(unsigned long long int __arg);
	
	explicit
	_Int_stdbase(float __arg);
	
	explicit
	_Int_stdbase(double __arg);
	
	explicit
	_Int_stdbase(long double __arg);
	
	explicit
	_Int_stdbase(const char* __arg);
	
	explicit
	_Int_stdbase(const char* __arg, _Radix __radix);
	
	explicit
	_Int_stdbase(const std::string& __arg);
	
	explicit
	_Int_stdbase(const std::string& __arg, _Radix __radix);
	
	_Int_stdbase(const _Int_stdbase& __arg);
	
	virtual
	~_Int_stdbase();
	
	static _Int_allocator*
	_S_get_default_allocator();
	
	_Int_pointer
	_M_begin() const;
	
	_Int_pointer
	_M_end() const;
	
	_Int_data
	_M_front() const;
	
	_Int_data
	_M_back() const;
	
	void
	_M_initialize(size_t __n = 0);
	
	void
	_M_realloc(size_t __n);
	
	void
	_M_reserve(size_t __n);
	
	void
	_M_reserve(size_t __n, _Int_data __arg);
	
	void
	_M_request(size_t __n);
	
	void
	_M_shrink();
	
	bool
	_M_boolean() const;
	
	template<typename _FP>
	static size_t
	_S_extract_fp(_Int_data* __v, _FP __fp);
	
	template<typename _FP>
	void
	_M_set_fp(_FP __fp);
	
	template<typename _FP>
	_FP
	_M_get_fp();
	
	template<typename _SI>
	void
	_M_set_si(_SI __si);
	
	template<typename _SI>
	_SI
	_M_get_si();
	
	template<typename _UI>
	void
	_M_set_ui(_UI __ui);
	
	template<typename _UI>
	_UI
	_M_get_ui();
	
	void
	_M_basic_increment();
	
	void
	_M_basic_decrement();
	
	void
	_M_increment();
	
	void
	_M_decrement();
	
	void
	_M_basic_swap(_Int_stdbase& __arg);
	
	void
	_M_swap(_Int_stdbase& __arg);
	
	void
	_M_basic_plus(const _Int_stdbase& __arg);
	
	void
	_M_plus(const _Int_stdbase& __arg);
	
	void
	_M_basic_minus(const _Int_stdbase& __arg);
	
	void
	_M_minus(const _Int_stdbase& __arg);
	
	void
	_M_basic_multiplies(const _Int_stdbase& __arg);
	
	void
	_M_multiplies(const _Int_stdbase& __arg);
	
	void
	_M_basic_divides(const _Int_stdbase& __arg);
	
	void
	_M_divides(const _Int_stdbase& __arg);
	
	void
	_M_basic_modulus(const _Int_stdbase& __arg);
	
	void
	_M_modulus(const _Int_stdbase& __arg);
	
	_Int_allocator*
	_M_get_allocator() const;
	
	_Int_stdbase*
	_M_create() const;
	
	_Int_stdbase*
	_M_clone() const;
	
	_Int_stdbase&
	_M_normalize();
	
	_Int_data
	_M_get_element(size_t __pos) const;
	
	void
	_M_set_element(size_t __pos, _Int_data __x);
	
	bool
	_M_get_bit(size_t __pos) const;
	
	void
	_M_set_bit(size_t __pos, bool __x);
	
	_Int_stdbase
	_M_get_sub(size_t __pos, size_t __n);
	
	void
	_M_negate();
	
	void
	_M_abs();
	
	void
	_M_assign(const _Int_stdbase& __arg);
	
	bool
	_M_is_zero() const;
	
	bool
	_M_is_odd() const;
	
	size_t
	_M_size() const;
	
	int
	_M_arsign() const;
	
	int
	_M_compare(const _Int_stdbase& __arg) const;
	
	int
	_M_basic_compare(const _Int_stdbase& __arg) const;
	
	bool
	_M_is_equal_to(const _Int_stdbase& __arg) const;
	
	bool
	_M_is_not_equal_to(const _Int_stdbase& __arg) const;
	
	bool
	_M_is_less_than(const _Int_stdbase& __arg) const;
	
	bool
	_M_is_greater_than(const _Int_stdbase& __arg) const;
	
	bool
	_M_is_less_than_equal_to(const _Int_stdbase& __arg) const;
	
	bool
	_M_is_greater_than_equal_to(const _Int_stdbase& __arg) const;
};

}

#endif
