#ifndef _POL_TGUARD_TCC
#define _POL_TGUARD_TCC 1

namespace polext
{

thread_guard::
thread_guard(value_type&& __arg)
	: _M_storage(std::move(__arg))
{
}

thread_guard::
~thread_guard()
{
	if (_M_storage.joinable())
		_M_storage.join();
}

thread_guard::
value_type*
operator -> ()
{
	return &_M_storage;
}

}

#endif
