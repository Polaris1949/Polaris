#ifndef _POL_INTEXCEPT_TCC
#define _POL_INTEXCEPT_TCC 1

namespace polaris
{

_Int_exception::
_Int_exception()
	: _M_code(_Code::_UE)
{
}

_Int_exception::
_Int_exception(_Code __code)
	: _M_code(__code)
{
}

_Int_exception::
~_Int_exception() noexcept
{
}

std::string
_Int_exception::
_M_code_str() const
{
	switch (_M_code)
	{
		default:
			return {"unknown_error"};
			
		case _Code::_CE:
			return {"conversion_error"};
			
		case _Code::_IAE:
			return {"invalid_argument_error"};
			
		case _Code::_DBZ:
			return {"division_by_zero"};
			
		case _Code::_UIN:
			return {"unsigned_is_negative"};
	}
}

std::runtime_error
_Int_exception::
_M_msg(const std::string& __arg) const
{
	return std::runtime_error(_M_code_str() + ":   " + __arg);
}

_Int_exception
unknown_error()
{
	return {_Int_exception::_Code::_UE};
}

_Int_exception
conversion_error()
{
	return {_Int_exception::_Code::_CE};
}

_Int_exception
invalid_argument_error()
{
	return {_Int_exception::_Code::_IAE};
}

_Int_exception
division_by_zero()
{
	return {_Int_exception::_Code::_DBZ};
}

_Int_exception
unsigned_is_negative()
{
	return {_Int_exception::_Code::_UIN};
}

}

#endif
