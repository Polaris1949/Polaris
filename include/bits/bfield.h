#ifndef _POL_BFIELD_H
#define _POL_BFIELD_H 1

#include <vector>

namespace polaris
{

class bitfield
{
public:
	typedef vector<bool> container_type;
	typedef size_t size_type;
	
private:
	vector<bool> _M_impl;
	
public:
	bitfield();
	
	bool operator[] (size_type __pos) const;
	size_type size() const;
	
	void resize(size_type __new_size, bool __x = bool());
};

}

#endif
