#ifndef _POL_INTREF_H
#define _POL_INTREF_H 1

namespace polaris
{

struct _Int_reference
{
	_Int_data* _M_p;
	
	_Int_reference();
	
	_Int_reference(_Int_base* __ptr, size_t __n);
	
	~_Int_reference();
	
	bool empty() const;
	
	operator _Int_data() const;
	
	_Int_reference&
	operator = (_Int_data __x);
	
	_Int_reference&
	operator = (const _Int_reference& __x);
};

}

#endif
