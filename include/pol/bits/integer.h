#ifndef _POL_INTEGER_H
#define _POL_INTEGER_H 1

#include <string>

namespace polaris
{

class integer :
#if _POL_DEBUG
public
#else
protected
#endif
_Int_stdbase
{
	typedef _Int_stdbase          _Base;
	typedef _Int_allocator        _Alloc;
	typedef _Int_reference        _Ref;
	typedef const _Int_reference  _CRef;
	
public:
	// Types:
	typedef _Int_data       data_type;
	typedef size_t          size_type;
	typedef int             sign_type;
	typedef _Radix          radix_type;
	typedef _Int_reference  reference;
	//typedef _Int_data_type  const_reference;
	//typedef _Alloc          allocator_type;
	
//private:
	//static integer_allocator* _XS_default_allocator;
	
	/*data_type* _XM_dataplus;
	size_type _XM_length;
	size_type _XM_capacity;*/
	
	/*// _T must be an integer type.
	template<typename _T>
	size_type
	_XM_nlength(_T __n);
	
	template<typename _T>
	void
	_XM_construct(_T __n, bool __int);//???
	
	void
	_XM_basic_swap(const integer& __arg);*/
	
/*public:
	// _T must be an integer type.
	template<typename _T>
	static bool
	_XS_sign_bit(_T __n);
	
	data_type*
	_XM_data() const;*/
	
public:
	// 2.3 constructors and destructor:
	integer();
	integer(int __arg);
	integer(unsigned int __arg);
	integer(long int __arg);
	integer(unsigned long int __arg);
	integer(long long int __arg);
	integer(unsigned long long int __arg);
	explicit integer(float __arg);
	explicit integer(double __arg);
	explicit integer(long double __arg);
	explicit integer(const char* __arg);
	explicit integer(const char* __arg, radix_type __radix);
	explicit integer(const std::string& __arg);
	explicit integer(const std::string& __arg, radix_type __radix);
	integer(const integer& __arg);
	virtual ~integer();
	
	// 2.4 conversion member operators:
	operator boolean() const;
	
	// 2.5 copying member functions (NVI design pattern):
	static integer_allocator* get_default_allocator();
	integer_allocator* get_allocator() const;
	integer* create() const;
	integer* clone() const;
	integer& normalize();
	integer& swap(integer& __arg);
	
	// 2.6 bit and element access member functions:
	sign_type sign() const;
	bool is_zero() const;
	bool is_odd() const;
	size_type highest_bit() const;
	size_type lowest_bit() const;
	bool get_bit(size_type __pos) const;
	integer& set_bit(size_type __pos, bool __x);
	integer get_sub(size_type __pos, size_type __n) const;
	size_type size() const;
	
	reference operator[] (size_type __pos);
	const reference operator[] (size_type __pos) const;
	
	// 2.7 arithmetic member operators (NVI design pattern):
	integer& negate();
	integer& abs();
	integer& operator++ ();
	integer& operator-- ();
	integer& operator = (const integer& __x);
	integer& operator += (const integer& __x);
	integer& operator -= (const integer& __x);
	integer& operator *= (const integer& __x);
	integer& operator /= (const integer& __x);
	integer& operator %= (const integer& __x);
	integer& operator <<= (size_type __n);
	integer& operator >>= (size_type __n);
	integer& operator &= (const integer& __x);
	integer& operator |= (const integer& __x);
	integer& operator ^= (const integer& __x);
#if _POL_DEBUG
public:
#else
protected:
#endif
	friend class _Int_reference;
	
	// 2.5 copying member functions:
	virtual integer_allocator* do_get_allocator() const;
	virtual integer* do_create() const;
	virtual integer* do_clone() const;
	virtual integer& do_normalize();
	virtual integer& do_swap(integer& __arg);
	
	// 2.8 arithmetic member functions:
	virtual data_type get_element(size_type __pos) const;
	virtual integer& set_element(size_type __pos, data_type __x);
	virtual integer& do_negate();
	virtual integer& do_abs();
	virtual integer& increment();
	virtual integer& decrement();
	virtual integer& assign(const integer& __x);
	virtual integer& add(const integer& __x);
	virtual integer& subtract(const integer& __x);
	virtual integer& multiply(const integer& __x);
	virtual integer& divide(const integer& __x);
	virtual integer& remainder(const integer& __x);
	virtual integer& shift_left(size_type __n);
	virtual integer& shift_right(size_type __n);
	virtual integer& bitwise_and(const integer& __x);
	virtual integer& bitwise_or(const integer& __x);
	virtual integer& bitwise_xor(const integer& __x);
};

// 2.9 arithmetic non-member operators:
integer operator++ (integer& __arg, int);
integer operator-- (integer& __arg, int);
integer operator + (const integer& __arg);
integer operator - (const integer& __arg);
integer operator + (const integer& __lhs, const integer& __rhs);
integer operator - (const integer& __lhs, const integer& __rhs);
integer operator * (const integer& __lhs, const integer& __rhs);
integer operator / (const integer& __lhs, const integer& __rhs);
integer operator % (const integer& __lhs, const integer& __rhs);
integer operator << (const integer& __lhs, integer::size_type __rhs);
integer operator >> (const integer& __lhs, integer::size_type __rhs);
integer operator & (const integer& __lhs, const integer& __rhs);
integer operator | (const integer& __lhs, const integer& __rhs);
integer operator ^ (const integer& __lhs, const integer& __rhs);

// 2.10 boolean non-member operators:
bool operator == (const integer& __lhs, const integer& __rhs);
bool operator != (const integer& __lhs, const integer& __rhs);
bool operator < (const integer& __lhs, const integer& __rhs);
bool operator <= (const integer& __lhs, const integer& __rhs);
bool operator > (const integer& __lhs, const integer& __rhs);
bool operator >= (const integer& __lhs, const integer& __rhs);

// 2.11 arithmetic non-member functions:
integer abs(const integer& __arg);
integer sqr(const integer& __arg);
integer sqrt(const integer& __arg);
void sqrtrem(const integer& __arg, integer& __res, integer& __rem);
void divrem(const integer& __lhs, const integer& __rhs,
	integer& __quot, integer& __rem);
integer pow(const integer& __x, const integer& __n);
integer mod(const integer& __x, const integer& __y);
integer powmod(const integer& __x, const integer& __n, const integer& __y);
integer invmod(const integer& __x, const integer& __y);
integer gcd(const integer& __x, const integer& __y);
integer lcm(const integer& __x, const integer& __y);
integer extgcd(const integer& __x, const integer& __y,
	integer& __a, integer& __b);
void swap(integer& __x, integer& __y);

// 2.12 conversion non-member functions:
int to_int(const integer& __arg);
unsigned int to_unsigned_int(const integer& __arg);
long int to_long_int(const integer& __arg);
unsigned long int to_unsigned_long_int(const integer& __arg);
long long int to_long_long_int(const integer& __arg);
unsigned long long int to_unsigned_long_long_int(const integer& __arg);
float to_float(const integer& __arg);
double to_double(const integer& __arg);
long double to_long_double(const integer& __arg);
std::string to_string(const integer& __arg);
std::string to_string(const integer& __arg, integer::radix_type __radix);

// 2.13 stream non-member operators:
template<class _CharT, class _Traits>
std::basic_istream<_CharT, _Traits> &
operator >> (std::basic_istream<_CharT, _Traits>& __lhs,
	integer& __rhs);
template<class _CharT, class _Traits>
std::basic_ostream<_CharT, _Traits> &
operator << (std::basic_ostream<_CharT, _Traits>& __lhs,
	const integer& __rhs);

// 2.14 random non-member functions:
integer random(const integer& __min, const integer& __max);
/*
class unsigned_integer : public integer
{
public:
	// 2.17 unsigned integer constructors and destructor
	unsigned_integer();
	unsigned_integer( int );
	unsigned_integer( unsigned int );
	unsigned_integer( long int );
	unsigned_integer( unsigned long int );
	unsigned_integer( long long int );
	unsigned_integer( unsigned long long int );
	explicit unsigned_integer( float );
	explicit unsigned_integer( double );
	explicit unsigned_integer( long double );
	explicit unsigned_integer( const char * );
	explicit unsigned_integer( const char *, radix_type );
	explicit unsigned_integer( const std::string & );
	explicit unsigned_integer( const std::string &, radix_type );
	unsigned_integer( const integer & );
	~unsigned_integer();
	
protected:
	// 2.18 unsigned integer member functions
	integer_allocator * do_get_allocator() const;
	unsigned_integer * do_create() const;
	unsigned_integer * do_clone() const;
	unsigned_integer & do_normalize();
	unsigned_integer & do_swap( integer & );
	unsigned_integer & set_element( size_type, data_type );
	unsigned_integer & do_negate();
	unsigned_integer & do_abs();
	unsigned_integer & increment();
	unsigned_integer & decrement();
	unsigned_integer & assign( const integer & );
	unsigned_integer & add( const integer & );
	unsigned_integer & subtract( const integer & );
	unsigned_integer & multiply( const integer & );
	unsigned_integer & divide( const integer & );
	unsigned_integer & remainder( const integer & );
	unsigned_integer & shift_left( size_type );
	unsigned_integer & shift_right( size_type );
	unsigned_integer & bitwise_and( const integer & );
	unsigned_integer & bitwise_or( const integer & );
	unsigned_integer & bitwise_xor( const integer & );
};

template<int _Tag, class _ModT>
class modular_integer : public integer
{
private:
	static _ModT _S_modulus, _S_offset; // for exposition only
	
public:
	// 2.19 modular integer static functions
	static void set_modulus( const integer & );
	static void set_offset( const integer & );
	static const _ModT & get_modulus();
	static const _ModT & get_offset();
	
	// 2.20 modular integer constructors and destructor
	modular_integer();
	modular_integer( int );
	modular_integer( unsigned int );
	modular_integer( long int );
	modular_integer( unsigned long int );
	modular_integer( long long int );
	modular_integer( unsigned long long int );
	explicit modular_integer( float );
	explicit modular_integer( double );
	explicit modular_integer( long double );
	explicit modular_integer( const char * );
	explicit modular_integer( const char *, radix_type );
	explicit modular_integer( const std::string & );
	explicit modular_integer( const std::string &, radix_type );
	modular_integer( const integer & );
	~modular_integer();
	
protected:
	// 2.21 modular integer member functions
	integer_allocator * do_get_allocator() const;
	modular_integer * do_create() const;
	modular_integer * do_clone() const;
	modular_integer & do_normalize();
	modular_integer & do_swap( integer & );
	modular_integer & set_element( size_type, data_type );
	modular_integer & do_negate();
	modular_integer & do_abs();
	modular_integer & increment();
	modular_integer & decrement();
	modular_integer & assign( const integer & );
	modular_integer & add( const integer & );
	modular_integer & subtract( const integer & );
	modular_integer & multiply( const integer & );
	modular_integer & divide( const integer & );
	modular_integer & remainder( const integer & );
	modular_integer & shift_left( size_type );
	modular_integer & shift_right( size_type );
	modular_integer & bitwise_and( const integer & );
	modular_integer & bitwise_or( const integer & );
	modular_integer & bitwise_xor( const integer & );
};

template<int tag>
class allocated_integer : public integer
{
private:
	static integer_allocator * the_allocator; // for exposition only
	
public:
	// 2.22 allocated integer static functions
	static void set_allocator( integer_allocator * );
	
	// 2.23 allocated integer constructors and destructor
	allocated_integer();
	allocated_integer( int );
	allocated_integer( unsigned int );
	allocated_integer( long int );
	allocated_integer( unsigned long int );
	allocated_integer( long long int );
	allocated_integer( unsigned long long int );
	explicit allocated_integer( float );
	explicit allocated_integer( double );
	explicit allocated_integer( long double );
	explicit allocated_integer( const char * );
	explicit allocated_integer( const char *, radix_type );
	explicit allocated_integer( const std::string & );
	explicit allocated_integer( const std::string &, radix_type );
	allocated_integer( const integer & );
	~allocated_integer();
	
protected:
	// 2.24 allocated integer member functions
	integer_allocator * do_get_allocator() const;
	allocated_integer * do_create() const;
	allocated_integer * do_clone() const;
	allocated_integer & do_normalize();
	allocated_integer & do_swap( integer & );
	allocated_integer & set_element( size_type, data_type );
	allocated_integer & do_negate();
	allocated_integer & do_abs();
	allocated_integer & increment();
	allocated_integer & decrement();
	allocated_integer & assign( const integer & );
	allocated_integer & add( const integer & );
	allocated_integer & subtract( const integer & );
	allocated_integer & multiply( const integer & );
	allocated_integer & divide( const integer & );
	allocated_integer & remainder( const integer & );
	allocated_integer & shift_left( size_type );
	allocated_integer & shift_right( size_type );
	allocated_integer & bitwise_and( const integer & );
	allocated_integer & bitwise_or( const integer & );
	allocated_integer & bitwise_xor( const integer & );
};

template<int tag>
class allocated_unsigned_integer : public integer
{
private:
	static integer_allocator * the_allocator; // for exposition only
	
public:
	// 2.25 allocated unsigned integer static functions
	static void set_allocator( integer_allocator * );
	
	// 2.26 allocated unsigned integer constructors and destructor
	allocated_unsigned_integer();
	allocated_unsigned_integer( int );
	allocated_unsigned_integer( unsigned int );
	allocated_unsigned_integer( long int );
	allocated_unsigned_integer( unsigned long int );
	allocated_unsigned_integer( long long int );
	allocated_unsigned_integer( unsigned long long int );
	explicit allocated_unsigned_integer( float );
	explicit allocated_unsigned_integer( double );
	explicit allocated_unsigned_integer( long double );
	explicit allocated_unsigned_integer( const char * );
	explicit allocated_unsigned_integer( const char *, radix_type );
	explicit allocated_unsigned_integer( const std::string & );
	explicit allocated_unsigned_integer( const std::string &, radix_type );
	allocated_unsigned_integer( const integer & );
	~allocated_unsigned_integer();
	
protected:
	// 2.27 allocated unsigned integer member functions
	integer_allocator * do_get_allocator() const;
	allocated_unsigned_integer * do_create() const;
	allocated_unsigned_integer * do_clone() const;
	allocated_unsigned_integer & do_normalize();
	allocated_unsigned_integer & do_swap( integer & );
	allocated_unsigned_integer & set_element( size_type, data_type );
	allocated_unsigned_integer & do_negate();
	allocated_unsigned_integer & do_abs();
	allocated_unsigned_integer & increment();
	allocated_unsigned_integer & decrement();
	allocated_unsigned_integer & assign( const integer & );
	allocated_unsigned_integer & add( const integer & );
	allocated_unsigned_integer & subtract( const integer & );
	allocated_unsigned_integer & multiply( const integer & );
	allocated_unsigned_integer & divide( const integer & );
	allocated_unsigned_integer & remainder( const integer & );
	allocated_unsigned_integer & shift_left( size_type );
	allocated_unsigned_integer & shift_right( size_type );
	allocated_unsigned_integer & bitwise_and( const integer & );
	allocated_unsigned_integer & bitwise_or( const integer & );
	allocated_unsigned_integer & bitwise_xor( const integer & );
};

template<int _Tag, class _ModT>
class allocated_modular_integer : public integer
{
private:
	static _ModT the_modulus, the_offset; // for exposition only
	static integer_allocator * the_allocator; // for exposition only
	
public:
	// 2.28 allocated modular integer static functions
	static void set_modulus( const integer & );
	static void set_offset( const integer & );
	static const _ModT & get_modulus();
	static const _ModT & get_offset();
	static void set_allocator( integer_allocator * );
	
	// 2.29 allocated modular integer constructors and destructor
	allocated_modular_integer();
	allocated_modular_integer( int );
	allocated_modular_integer( unsigned int );
	allocated_modular_integer( long int );
	allocated_modular_integer( unsigned long int );
	allocated_modular_integer( long long int );
	allocated_modular_integer( unsigned long long int );
	explicit allocated_modular_integer( float );
	explicit allocated_modular_integer( double );
	explicit allocated_modular_integer( long double );
	explicit allocated_modular_integer( const char * );
	explicit allocated_modular_integer( const char *, radix_type );
	explicit allocated_modular_integer( const std::string & );
	explicit allocated_modular_integer( const std::string &, radix_type );
	allocated_modular_integer( const integer & );
	~allocated_modular_integer();
	
protected:
	// 2.30 allocated modular integer member functions
	integer_allocator * do_get_allocator() const;
	allocated_modular_integer * do_create() const;
	allocated_modular_integer * do_clone() const;
	allocated_modular_integer & do_normalize();
	allocated_modular_integer & do_swap( integer & );
	allocated_modular_integer & set_element( size_type, data_type );
	allocated_modular_integer & do_negate();
	allocated_modular_integer & do_abs();
	allocated_modular_integer & increment();
	allocated_modular_integer & decrement();
	allocated_modular_integer & assign( const integer & );
	allocated_modular_integer & add( const integer & );
	allocated_modular_integer & subtract( const integer & );
	allocated_modular_integer & multiply( const integer & );
	allocated_modular_integer & divide( const integer & );
	allocated_modular_integer & remainder( const integer & );
	allocated_modular_integer & shift_left( size_type );
	allocated_modular_integer & shift_right( size_type );
	allocated_modular_integer & bitwise_and( const integer & );
	allocated_modular_integer & bitwise_or( const integer & );
	allocated_modular_integer & bitwise_xor( const integer & );
};
*/
}

#endif
