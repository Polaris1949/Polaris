#ifndef _POL_BFIELD_H
#define _POL_BFIELD_H 1

#include <vector>

namespace polaris
{

class bitfield
{
public:
	typedef std::vector<bool> container_type;
	typedef size_t size_type;

private:
	std::vector<bool> _M_impl;

public:
	bitfield();

	template<typename _T>
	bitfield(const _T& __x);

	bool operator[] (size_type __pos) const;
	size_type size() const;

	void resize(size_type __new_size, bool __x = bool());
};

}

#endif
