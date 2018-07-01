#ifndef _POL_BITS_VWRAP_H
#define _POL_BITS_VWRAP_H

#include <iosfwd>

namespace polaris
{

template<typename _Tp>
class value_wrapper
{
public:
	typedef _Tp value_type;
	typedef _Tp& reference;
	
private:
	_Tp _M_data;
	
public:
	value_wrapper();
	
	value_wrapper(const value_type& __x);
	
	virtual ~value_wrapper();
	
	value_type data() const;
	
	reference data();
	
	operator value_type() const;
	
	operator reference();
	
	template<typename _T>
	friend std::istream&
	operator >> (std::istream& __in, value_wrapper<_T>& __x);
	
	template<typename _T>
	friend std::ostream&
	operator << (std::ostream& __out, const value_wrapper<_T>& __x);
};

#define POL_VW_MAKE_TAG_TYPE(__class, __type) \
	class __class : public polaris::value_wrapper<__type> \
	{ \
		using polaris::value_wrapper<__type>::value_wrapper; \
	};

}

#endif
