#ifndef _POL_TGUARD_H
#define _POL_TGUARD_H 1

#include <thread>

namespace polext
{

class thread_guard
{
public:
	typedef std::thread value_type;
	
private:
	std::thread _M_storage;
	
public:
	thread_guard(value_type&& __arg);
	
	~thread_guard();
	
	value_type*
	operator-> ();
};

}

#endif
