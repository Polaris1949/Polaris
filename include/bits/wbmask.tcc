#ifndef _POL_WBMASK_TCC
#define _POL_WBMASK_TCC 1

namespace polaris
{

template<typename _Tp>
weak_bitmask<_Tp>::
weak_bitmask()
	: _M_value(), _M_mask()
{
}

template<typename _Tp>
weak_bitmask<_Tp>::
weak_bitmask(const value_type& __x)
	: _M_value(__x), _M_mask()
{
}

template<typename _Tp>
weak_bitmask<_Tp>::
weak_bitmask(const value_type& __x, const mask_type& __y)
	: _M_value(__x), _M_mask(__y)
{
}

template<typename _Tp>
_Tp&
weak_bitmask<_Tp>::
value()
{
	return _M_value;
}

template<typename _Tp>
_Tp&
weak_bitmask<_Tp>::
mask()
{
	return _M_mask;
}

template<typename _Tp>
_Tp&
weak_bitmask<_Tp>::
apply()
{
	return _M_value &= ~_M_mask;
}

template<typename _Tp>
_Tp
weak_bitmask<_Tp>::
calc() const
{
	return _M_value & ~_M_mask;
}

}

#endif
