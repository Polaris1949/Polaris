#ifndef _POL_TYPE_H
#define _POL_TYPE_H 1

#include <iosfwd>
#include <type_traits>

namespace pol
{

template<typename _Tp>
class basic_type
{
public:
	typedef _Tp     value_type;
	typedef size_t  size_type;
	
protected:
	_Tp _M_data;
	
public:
	basic_type();
	
	explicit
	basic_type(const value_type& __x);
	
	explicit
	basic_type(value_type&& __x);
	
	basic_type(const basic_type<value_type>& __x);
	
	basic_type(basic_type<value_type>&& __x);
	
	virtual
	~basic_type() noexcept;
	
	virtual void
	swap(value_type& __x);
	
	void
	swap(basic_type<value_type>& __x);
	
	basic_type<value_type>&
	operator = (const basic_type<value_type>& __x);
	
	basic_type<value_type>&
	operator = (basic_type<value_type>&& __x);
	
	virtual value_type&
	data();
	
	virtual value_type
	data() const;
	
	virtual size_type
	size() const;
	
	virtual
	operator value_type&();
	
	virtual
	operator value_type() const;
};

template<typename _Tp>
class integer_type : public basic_type<_Tp>
{
public:
	typedef _Tp     value_type;
	typedef size_t  size_type;
	
	static_assert(std::is_integral<_Tp>::value,
		"'_Tp' should be an integer type");
	
public:
	integer_type();
	
	explicit
	integer_type(const value_type& __x);
	
	explicit
	integer_type(value_type&& __x);
	
	integer_type(const integer_type<value_type>& __x);
	
	integer_type(integer_type<value_type>&& __x);
	
	virtual
	~integer_type() noexcept;
	
	void
	swap(value_type& __x);
	
	void
	swap(integer_type<value_type>& __x);
	
	integer_type<value_type>&
	operator = (const integer_type<value_type>& __x);
	
	integer_type<value_type>&
	operator = (integer_type<value_type>&& __x);
	
	integer_type<value_type>
	operator + (const integer_type<value_type>& __x) const;
	
	integer_type<value_type>
	operator - (const integer_type<value_type>& __x) const;
	
	integer_type<value_type>
	operator * (const integer_type<value_type>& __x) const;
	
	integer_type<value_type>
	operator / (const integer_type<value_type>& __x) const;
	
	integer_type<value_type>
	operator % (const integer_type<value_type>& __x) const;
	
	integer_type<value_type>&
	operator += (const integer_type<value_type>& __x);
	
	integer_type<value_type>&
	operator -= (const integer_type<value_type>& __x);
	
	integer_type<value_type>&
	operator *= (const integer_type<value_type>& __x);
	
	integer_type<value_type>&
	operator /= (const integer_type<value_type>& __x);
	
	integer_type<value_type>&
	operator %= (const integer_type<value_type>& __x);
	
	bool
	operator == (const integer_type<value_type>& __x) const;
	
	bool
	operator != (const integer_type<value_type>& __x) const;
	
	bool
	operator < (const integer_type<value_type>& __x) const;
	
	bool
	operator <= (const integer_type<value_type>& __x) const;
	
	bool
	operator > (const integer_type<value_type>& __x) const;
	
	bool
	operator >= (const integer_type<value_type>& __x) const;
	
	template<typename _T>
	friend std::istream&
	operator >> (std::istream& __in, integer_type<_T>& __x);
	
	template<typename _T>
	friend std::ostream&
	operator << (std::ostream& __out, const integer_type<_T>& __x);
};

}

#endif
