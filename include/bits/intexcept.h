#ifndef _POL_INTEXCEPT_H
#define _POL_INTEXCEPT_H 1

#include <string>

namespace polaris
{

struct _Int_exception
{
	typedef unsigned char       _Code_base;
	
	enum class _Code : _Code_base
	{
		_UE, _CE, _IAE, _DBZ, _UIN
	};
	
	_Code _M_code;
	
	_Int_exception();
	_Int_exception(_Code __code);
	virtual ~_Int_exception() noexcept;
	
	std::string _M_code_str() const;
	std::runtime_error _M_msg(const std::string& __arg) const;
};

_Int_exception unknown_error();
_Int_exception conversion_error();
_Int_exception invalid_argument_error();
_Int_exception division_by_zero();
_Int_exception unsigned_is_negative();

}

#endif
