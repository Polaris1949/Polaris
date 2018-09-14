#ifndef _POL_BITSTO_H
#define _POL_BITSTO_H 1

#include <cstddef>

namespace polaris
{

template<typename _STp>
class basic_bit_storage
{
public:
    using storage_type = _STp;
    using level_type = unsigned char;

private:
    _STp _M_data;

public:
    basic_bit_storage() = default;
    explicit basic_bit_storage(const storage_type& __data);
    explicit basic_bit_storage(storage_type&& __data);

    bool set(level_type __lev, bool __val);
    bool get(level_type __lev) const;
};

using bit_storage = basic_bit_storage<unsigned int>;

}

#endif /* _POL_BITSTO_H */
