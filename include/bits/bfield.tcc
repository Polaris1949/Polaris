#ifndef _POL_BFIELD_TCC
#define _POL_BFIELD_TCC 1

namespace polaris
{

bitfield::
bitfield()
	: _M_impl()
{
}

template<typename _T>
bitfield::
bitfield(const _T& __x)
	: _M_impl()
{
}

bool
bitfield::
operator[] (size_type __pos) const
{
	return _M_impl[__pos];
}

size_t
bitfield::
size() const
{
	return _M_impl.size();
}

void
bitfield::
resize(size_type __new_size, bool __x)
{
	_M_impl.resize(__new_size, __x);
}

}

#endif
