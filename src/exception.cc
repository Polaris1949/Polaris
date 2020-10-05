#include <pol/exception>
#include <pol/format>

namespace pol
{

std::string
__gen_what(const std::string& __type, const std::string& __loc, const std::string& __msg)
{
    return format("polaris library exception\ntype: {}\n loc: {}\n msg: {}\n", __type, __loc, __msg);
}

exception::
exception(const std::string& __type, const std::string& __loc, const std::string& __msg)
    : _M_what(__gen_what(__type, __loc, __msg))
{ }

const char*
exception::
what() const noexcept
{ return this->_M_what.data(); }

#if 0
raw_exception::
raw_exception(const std::string& __type, const std::string& __loc, const std::string& __msg)
    : _M_type(__type), _M_loc(__loc), _M_msg(__msg), _M_what()
{ }

void
raw_exception::
_M_check_what()
{
	if (this->_M_what.empty())
		this->_M_what = __gen_what(__type, __loc, __msg);
}

const char*
raw_exception::
what() const noexcept
{ this->_M_check_what(); return this->_M_what.data(); }

const char*
raw_exception::
type() const noexcept
{ return this->_M_type.data(); }

const char*
raw_exception::
location() const noexcept
{ return this->_M_loc.data(); }

const char*
raw_exception::
message() const noexcept
{ return this->_M_msg.data(); }

std::exception_ptr
exception::
eptr() const noexcept
{ return this->_M_eptr; }

const char*
exception::
name() const noexcept
{ return this->_M_name.data(); }

const char*
exception::
what() const noexcept
{
    try
    {
        if (this->_M_eptr)
            std::rethrow_exception(this->_M_eptr);
    }
    catch (const std::exception& __e)
    {
        return __e.what();
    }

    __builtin_unreachable();
}

std_exception::
std_exception(pol::exception&& __ex)
    : _M_what{std::string{__ex.name()} + ": " + __ex.what()}
{ }

const char*
std_exception::
what() const noexcept
{ return this->_M_what.data(); }

void throw_ex(exception&& __e)
{ throw std_exception{std::move(__e)}; }
#endif

}
