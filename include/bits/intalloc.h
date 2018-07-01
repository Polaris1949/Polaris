#ifndef _POL_INTALLOC_H
#define _POL_INTALLOC_H 1

#include <memory>

namespace polaris
{

// @integer_allocator
class integer_allocator
{
public:
	typedef size_t  size_type;
	typedef void*   pointer;
	
protected:
	// 2.15 allocator constructors and destructor
	integer_allocator();
	virtual ~integer_allocator();
	
public:
	// 2.16 allocator member functions
	virtual pointer allocate(size_type __n) = 0;
	virtual pointer reallocate(pointer __p, size_type __n) = 0;
	virtual void deallocate(pointer __p) = 0;
};

// integer default allocator class
struct _Int_allocator : public integer_allocator
{
public:
	_Int_allocator() noexcept;
	
	~_Int_allocator() noexcept;
	
	pointer allocate(size_type __n);
	
	pointer reallocate(pointer __p, size_type __n);
	
	void deallocate(pointer __p);
};

}

#endif
