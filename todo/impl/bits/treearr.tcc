#ifndef _POL_TREEARR_TCC
#define _POL_TREEARR_TCC 1

namespace polaris
{

inline std::size_t
tree_array_base::
_S_lowbit(size_type __x)
{ return (__x + 1) & (~__x); }

template<typename _Tp>
template<typename _Seq>
tree_array<_Tp, tree_array_mode::mpir>::
tree_array(const _Seq& __data)
{ this->init(__data); }

template<typename _Tp>
template<typename _Seq>
void
tree_array<_Tp, tree_array_mode::mpir>::
init(const _Seq& __data)
{
    this->clear();
    this->resize(__data.size());

    for (size_type __i{}; __i < __data.size(); ++__i)
        this->modify(__i, __data[__i]);
}

template<typename _Tp>
bool
tree_array<_Tp, tree_array_mode::mpir>::
empty() const
{ return this->_M_tree.empty(); }

template<typename _Tp>
void
tree_array<_Tp, tree_array_mode::mpir>::
clear()
{ this->_M_tree.clear(); }

template<typename _Tp>
inline std::size_t
tree_array<_Tp, tree_array_mode::mpir>::
size() const
{ return this->_M_tree.size(); }

template<typename _Tp>
inline void
tree_array<_Tp, tree_array_mode::mpir>::
resize(size_type __s)
{ this->_M_tree.resize(__s); }

template<typename _Tp>
const _Tp&
tree_array<_Tp, tree_array_mode::mpir>::
at(size_type __pos) const
{ return this->_M_tree.at(__pos); }

template<typename _Tp>
const _Tp&
tree_array<_Tp, tree_array_mode::mpir>::
operator[] (size_type __pos) const
{ return this->_M_tree[__pos]; }

template<typename _Tp>
void
tree_array<_Tp, tree_array_mode::mpir>::
modify(size_type __x, const value_type& __k)
{
    for (size_type __i{__x}; __i < this->size(); __i += _S_lowbit(__i))
        this->_M_tree[__i] += __k;
}

template<typename _Tp>
inline _Tp
tree_array<_Tp, tree_array_mode::mpir>::
inquire(size_type __x, size_type __y)
{ return this->_M_prefix(__y) - this->_M_prefix(__x); }

template<typename _Tp>
_Tp
tree_array<_Tp, tree_array_mode::mpir>::
_M_prefix(size_type __x)
{
    value_type __res{};
    size_type __i{__x - 1};
    size_type __j{__x};

    while (__i < __j)
    {
        __res += this->_M_tree[__i];
        __j = __i;
        __i -= _S_lowbit(__i);
    }

    return __res;
}

template<typename _Tp>
template<typename _Seq>
tree_array<_Tp, tree_array_mode::mrip>::
tree_array(const _Seq& __data)
{ this->init(__data); }

template<typename _Tp>
template<typename _Seq>
void
tree_array<_Tp, tree_array_mode::mrip>::
init(const _Seq& __data)
{
    this->clear();
    this->resize(__data.size());

    for (size_type __i{}; __i < __data.size(); ++__i)
        this->modify(__i, __i + 1, __data[__i]);
}

template<typename _Tp>
inline bool
tree_array<_Tp, tree_array_mode::mrip>::
empty() const
{ return this->_M_delta.empty(); }

template<typename _Tp>
inline void
tree_array<_Tp, tree_array_mode::mrip>::
clear()
{ this->_M_delta.clear(); }

template<typename _Tp>
inline std::size_t
tree_array<_Tp, tree_array_mode::mrip>::
size() const
{ return this->_M_delta.size(); }

template<typename _Tp>
inline void
tree_array<_Tp, tree_array_mode::mrip>::
resize(size_type __s)
{ this->_M_delta.resize(__s); }

template<typename _Tp>
const _Tp&
tree_array<_Tp, tree_array_mode::mrip>::
at(size_type __pos) const
{ return this->_M_delta.at(__pos); }

template<typename _Tp>
const _Tp&
tree_array<_Tp, tree_array_mode::mrip>::
operator[] (size_type __pos) const
{ return this->_M_delta[__pos]; }

template<typename _Tp>
void
tree_array<_Tp, tree_array_mode::mrip>::
modify(size_type __x, size_type __y, const value_type& __k)
{
    for (size_type __i{__x}; __i < this->size(); __i += _S_lowbit(__i))
        this->_M_delta[__i] += __k;
    for (size_type __i{__y}; __i < this->size(); __i += _S_lowbit(__i))
        this->_M_delta[__i] -= __k;
}

template<typename _Tp>
_Tp
tree_array<_Tp, tree_array_mode::mrip>::
inquire(size_type __x)
{
    value_type __res{};
    size_type __i{__x};
    size_type __j{__x + 1};

    while (__i < __j)
    {
        __res += this->_M_delta[__i];
        __j = __i;
        __i -= _S_lowbit(__i);
    }

    return __res;
}

}

#endif /* _POL_TREEARR_TCC */
