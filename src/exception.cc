#include <pol/exception>

namespace pol
{

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

}
