#ifndef _POL_INTREF_TCC
#define _POL_INTREF_TCC 1

namespace polaris
{

inline
_Int_reference::
_Int_reference()
	: _M_p()
{
}

inline
_Int_reference::
_Int_reference(_Int_base* __ptr, size_t __n)
	: _M_p(__ptr->_M_impl._M_start + __n)
{
}

inline
_Int_reference::
~_Int_reference()
{
}

inline bool
_Int_reference::
empty() const
{
	return !_M_p;
}

inline
_Int_reference::
operator _Int_data() const
{
	if (_M_p == nullptr) return 0;
	return *_M_p;
}

inline _Int_reference&
_Int_reference::
operator = (_Int_data __x)
{
	if (_M_p) *_M_p = __x;
	return *this;
}

inline _Int_reference&
_Int_reference::
operator = (const _Int_reference& __x)
{
	_M_p = __x._M_p;
	return *this;
}

}

#endif
