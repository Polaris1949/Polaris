#ifndef _POL_INTALLOC_H
#define _POL_INTALLOC_H 1

#include <memory>

namespace polaris
{

/** @class  integer_allocator
 *  @brief  Integer allocator abstract base class
**/
class integer_allocator
{
public:
    typedef size_t  size_type;  ///< Size type
    typedef void*   pointer;    ///< Pointer type

protected:
    // 2.15 allocator constructors and destructor
    /** @brief  Construct a @c integer_allocator
    **/
    integer_allocator();

    /** @brief  Destroy a @c integer_allocator
    **/
    virtual ~integer_allocator();

public:
    // 2.16 allocator member functions
    /** @brief  Allocate memory
     *  @param  __n  Size of memory.
     *  @return  A pointer.
    **/
    virtual pointer allocate(size_type __n) = 0;

    /** @brief  Reallocate memory
     *  @param  __p  Pointer.
     *  @param  __n  Size of memory.
     *  @return  A new pointer.
    **/
    virtual pointer reallocate(pointer __p, size_type __n) = 0;

    /** @brief  Deallocate memory
     *  @param  __p  Pointer.
    **/
    virtual void deallocate(pointer __p) = 0;
};

/** @class  _Int_allocator
 *  @headerfile  integer
 *  @brief  Integer default allocator class
**/
struct _Int_allocator : public integer_allocator
{
    allocator<void> _M_alloc;

public:
    _Int_allocator() noexcept;

    ~_Int_allocator() noexcept;

    pointer allocate(size_type __n);

    pointer reallocate(pointer __p, size_type __n);

    void deallocate(pointer __p);
};

}

#endif
