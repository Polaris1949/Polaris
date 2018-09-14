#ifndef _POL_WEAK_RADIX_INTEGER_H
#define _POL_WEAK_RADIX_INTEGER_H 1

#include <string>
#include <polaris/version>

namespace polaris
{

template<typename _Tp>
class weak_radix_integer
{
public:
	typedef _Tp value_type;
	typedef size_t size_type;
	
	class reference
	{
	public:
		typedef size_t size_type;
		typedef _Tp value_type;
		
	private:
		_Tp* _M_data;
		size_t _M_pos;
		
		friend class weak_radix_integer<_Tp>;
		
		reference();
		reference(value_type* __ptr, size_type __pos);
		
	public:
		~reference() = default;
		reference& operator = (value_type __x);
		reference& operator = (const reference& __x);
		operator value_type() const;
	};
	
private:
	_Tp _M_data;
	
public:
	weak_radix_integer();
	explicit weak_radix_integer(const value_type& __x);
	
	value_type& raw();
	const value_type& raw() const;
	
	reference digit(size_type __pos);
	value_type digit(size_type __pos) const;
	
	reference operator[] (size_type __pos);
	value_type operator[] (size_type __pos) const;
};

}

#endif
