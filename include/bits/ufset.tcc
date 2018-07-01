#ifndef _POL_UFSET_TCC
#define _POL_UFSET_TCC 1

namespace polaris
{

#if _POL_NEWLIB
template<typename _Tp>
size_t
bhash<_Tp>::
operator() (const value_type& __x) const
{
	return reinterpret_cast<size_type>(&__x);
}

template<typename _Tp>
_Tp
bhash<_Tp>::
operator[] (const size_type& __x) const
{
	return *reinterpret_cast<value_type*>(__x);
}

size_t
bhash<size_t>::
operator() (const value_type& __x) const
{
	return __x;
}

size_t
bhash<size_t>::
operator[] (const size_type& __x) const
{
	return __x;
}
#endif

template<typename _Tp>
ufset<_Tp>::
ufset()
	: _M_storage()
{
}

template<typename _Tp>
typename ufset<_Tp>::_Hash&
ufset<_Tp>::
hash_func()
{
	return _M_hash_fun;
}

template<typename _Tp>
typename ufset<_Tp>::_Unhash&
ufset<_Tp>::
unhash_func()
{
	return _M_unhash_fun;
}

ufset<size_t>::
ufset()
	: _M_storage()
{
}

size_t&
ufset<size_t>::
operator[] (const value_type& __x)
{
	return _M_storage[__x];
}

}

#endif
