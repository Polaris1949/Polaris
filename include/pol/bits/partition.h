#ifndef _POL_PARTITION_H
#define _POL_PARTITION_H 1

namespace polaris
{

template<typename _Tp, typename _Func>
class partition
{
public:
    using size_type = size_t;
    using value_type = _Tp;
    using container_type = std::vector<_Tp>;
    using reference = typename container_type::reference;
    using const_reference = typename container_type::const_reference;

private:
    std::vector<_Tp> _M_data;
    std::vector<_Tp> _M_calc;
    std::vector<_Tp> _M_mark;
    size_type _M_bsize;
    _Func _M_func;

public:
    partition();

    ~partition() noexcept;

    size_type
    size() const;

    size_type
    bucket_size() const;

    size_type
    bucket_count() const;

    container_type&
    data();

    void
    bucket_resize(size_type __size);

    size_type
    bucket_index(size_type __pos) const;

    size_type
    bucket_begin(size_type __pos) const;

    size_type
    bucket_end(size_type __pos) const;

    bool
    is_bucket_range(size_type __begin, size_type __end) const;

    value_type
    find(size_type __pos) const;

    value_type
    find(size_type __begin, size_type __end) const;

    void
    modify(size_type __pos, value_type __x);

    void
    modify(size_type __begin, size_type __end, value_type __x);
};

}

#endif
