#ifndef _POL_BITSTO_H
#define _POL_BITSTO_H 1

#include <cstddef>

namespace polaris
{

template<typename _Tp>
class basic_bit_storage
{
public:
    using storage_type = _Tp;
    using level_type = unsigned char;

private:
    _Tp _M_data;
    _Tp _M_count;

public:
    basic_bit_storage() = default;
    explicit basic_bit_storage(const storage_type& __data);
    explicit basic_bit_storage(storage_type&& __data);

    bool empty() const;
    bool full() const;
    void clear();
    storage_type* data() const;

    bool set(level_type __n, bool __x);
    bool get(level_type __n) const;

    bool is_locked(level_type __n) const;
    bool lock(level_type __n);
    bool unlock(level_type __n);

    level_type obtain();
    void release(level_type __n);
};

using bit_storage = basic_bit_storage<unsigned int>;

}

#endif /* _POL_BITSTO_H */
