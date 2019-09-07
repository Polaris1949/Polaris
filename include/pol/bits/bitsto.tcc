// Bit storage -*- C++ -*-

// Copyright (C) 1997-2017 Free Software Foundation, Inc.
//
// This file is part of the Polaris C++ Library.  This library is free
// software; you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the
// Free Software Foundation; either version 3, or (at your option)
// any later version.

// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// Under Section 7 of GPL version 3, you are granted additional
// permissions described in the GCC Runtime Library Exception, version
// 3.1, as published by the Free Software Foundation.

// You should have received a copy of the GNU General Public License and
// a copy of the GCC Runtime Library Exception along with this program;
// see the files COPYING3 and COPYING.RUNTIME respectively.  If not, see
// <http://www.gnu.org/licenses/>.

/** @file        bits/bitsto.tcc
 *  @brief       Bit storage
 *  @author      Polaris Zhao
 *  @version     0.8.0
 *
 *  This is an internal header file, included by other library headers.
 *  Do not attempt to use it directly. @headername{bit}
**/

#ifndef _POL_BITSTO_TCC
#define _POL_BITSTO_TCC 1

namespace pol
{

template<typename _Tp>
bool
basic_bit_storage<_Tp>::
empty() const noexcept
{ return this->_M_count == storage_type{0}; }

template<typename _Tp>
bool
basic_bit_storage<_Tp>::
full() const noexcept
{ return this->_M_count == storage_type{-1}; }

template<typename _Tp>
void
basic_bit_storage<_Tp>::
clear() noexcept
{
    for (size_type __i{}; __i < bitof<storage_type>(); ++__i)
        this->unlock(__i);
}

template<typename _Tp>
constexpr size_t
basic_bit_storage<_Tp>::
size() const noexcept
{ return bitof<storage_type>(); }

template<typename _Tp>
_Tp&
basic_bit_storage<_Tp>::
data() noexcept
{ return this->_M_data; }

template<typename _Tp>
const _Tp&
basic_bit_storage<_Tp>::
data() const noexcept
{ return this->_M_data; }

template<typename _Tp>
void
basic_bit_storage<_Tp>::
set(size_type __n, bool __x)
{
    if (__x) this->_M_data |= (storage_type{1} << __n);
    else this->_M_data &= ~(storage_type{1} << __n);
}

template<typename _Tp>
bool
basic_bit_storage<_Tp>::
get(size_type __n) const
{
    return this->_M_data & (storage_type{1} << __n);
}

template<typename _Tp>
bool
basic_bit_storage<_Tp>::
is_locked(size_type __n) const
{
    return this->_M_count & (storage_type{1} << __n);
}

template<typename _Tp>
bool
basic_bit_storage<_Tp>::
lock(size_type __n)
{
    if (this->is_locked(__n))
        return false;
    this->_M_count |= (storage_type{1} << __n);
    return true;
}

template<typename _Tp>
bool
basic_bit_storage<_Tp>::
unlock(size_type __n)
{
    if (!this->is_locked(__n))
        return false;
    this->_M_count &= ~(storage_type{true} << __n);
    return true;
}

template<typename _Tp>
void
basic_bit_storage<_Tp>::
lockl(size_type __n)
{
    for (size_t __i{}; __i < __n; ++__i)
        this->lock(__i);
}

template<typename _Tp>
void
basic_bit_storage<_Tp>::
lockr(size_type __n)
{
    for (size_t __i{}; __i < __n; ++__i)
        this->lock(this->size() - 1 - __i);
}

template<typename _Tp>
size_t
basic_bit_storage<_Tp>::
alloc_p()
{
    for (size_t __i{}; __i < bitof<storage_type>(); ++__i)
        if (this->lock(__i)) return __i;
    throw std::runtime_error{"basic_bit_storage::alloc_p(): "
        "no available resource"};
}

template<typename _Tp>
void
basic_bit_storage<_Tp>::
dealloc_p(size_type __n)
{
    if (this->unlock(__n)) return;
    throw std::runtime_error{"basic_bit_storage::dealloc_p(): "
        "no such active resource"};
}

template<typename _Tp>
void*
basic_bit_storage<_Tp>::
begin() noexcept
{ return &this->data(); }

template<typename _Tp>
const void*
basic_bit_storage<_Tp>::
begin() const noexcept
{ return &this->data(); }

template<typename _Tp>
void*
basic_bit_storage<_Tp>::
end() noexcept
{ return &this->data() + this->size(); }

template<typename _Tp>
const void*
basic_bit_storage<_Tp>::
end() const noexcept
{ return &this->data() + this->size(); }

template<typename _Tp>
bool
basic_bit_storage<_Tp>::
in_range(bit_ptr __p) const noexcept
{
    void* __a{__p->byte_address()};
    return __a >= this->begin() && __a < this->end();
}

template<typename _Tp>
bitmem_ptr
basic_bit_storage<_Tp>::
allocate(size_type __n)
{
    size_t __a{};
    size_t __len{1};
    size_t __pos;
    while ((__pos = __a + __len - 1u) < this->size())
    {
        if (!this->lock(__pos))
        {
            for (size_t __j{__a}; __j < __a + __len; ++__j)
                this->unlock(__j);
            __a += __len;
            __len = 1;
        }
        else
        {
            if (__len >= __n)
                return {{&this->data(), __a}, __len};
            ++__len;
        }
    }
    return nullptr;
}

template<typename _Tp>
size_t
basic_bit_storage<_Tp>::
free_countl() const noexcept
{ return std::countl_zero(this->_M_count); }

template<typename _Tp>
size_t
basic_bit_storage<_Tp>::
free_countr() const noexcept
{ return std::countr_zero(this->_M_count); }

template<typename _Tp>
size_t
basic_bit_storage<_Tp>::
busy_count() const noexcept
{ return std::popcount(this->_M_count); }

template<typename _Tp>
bit_ref
basic_bit_storage<_Tp>::
at(size_type __n)
{
    expect(__n < bitof<storage_type>(), "out of range", "bad bit size");
    return bit_ref{bit_address{&this->_M_data, __n}};
}

template<typename _Tp>
bool
basic_bit_storage<_Tp>::
at(size_type __n) const
{
    expect(__n < bitof<storage_type>(), "out of range", "bad bit size");
    return this->get(__n);
}

template<typename _Tp>
bit_ref
basic_bit_storage<_Tp>::
operator[] (size_type __n)
{ return bit_ref{bit_address{&this->_M_data, __n}}; }

template<typename _Tp>
bool
basic_bit_storage<_Tp>::
operator[] (size_type __n) const
{ return this->get(__n); }

}

#endif /* _POL_BITSTO_TCC */
