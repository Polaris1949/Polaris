#ifndef _POL_INTGENBASE_TCC
#define _POL_INTGENBASE_TCC 1

namespace polaris
{

inline
_Int_genbase::
_Int_genbase()
	: _Int_base()
{
}

inline
_Int_genbase::
_Int_genbase(size_t __n)
	: _Int_base(__n)
{
	this->_M_impl._M_finish = this->_M_impl._M_start + __n;
}

inline size_t
_Int_genbase::
size() const
{
	return this->_M_impl._M_finish - this->_M_impl._M_start;
}

inline size_t
_Int_genbase::
capacity() const
{
	return this->_M_impl._M_end_of_storage - this->_M_impl._M_start;
}

bool
_Int_genbase::
_M_set_element(size_t __pos, _Int_data __x)
{
    if (!__x) return true;

	if (__pos >= capacity())
	{
		this->_M_reallocate(__pos + 1);
		this->_M_impl._M_start[__pos] = __x;
		return false;
	}

	if (__pos >= size())
	{
		this->_M_impl._M_finish = this->_M_impl._M_start + __pos + 1;
		this->_M_impl._M_start[__pos] = __x;
		return false;
	}

	this->_M_impl._M_start[__pos] = __x;
	return true;
}

_Int_reference
_Int_genbase::
_M_get_element(size_t __pos)
{
	if (__pos >= size())
		return _Int_reference();

	return _Int_reference(this, __pos);
}

_Int_data
_Int_genbase::
_M_get_element(size_t __pos) const
{
	if (__pos >= size())
		return _Int_data();

	return this->_M_impl._M_start[__pos];
}

void
_Int_genbase::
_M_reallocate(size_t __n)
{
	size_t __t = 1;
	while (__t < __n) __t <<= 1;

	this->_M_impl._M_start = this->_Int_base
		::_M_reallocate(this->_M_impl._M_start, __t);
	this->_M_impl._M_finish = this->_M_impl._M_start + __n;
	this->_M_impl._M_end_of_storage = this->_M_impl._M_start + __t;
}

}

#endif
