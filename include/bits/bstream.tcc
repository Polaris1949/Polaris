// Byte stream class implementation -*- C++ -*-

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

/** @file     bits/bstream.tcc
 *  @brief    Byte stream class implementation
 *  @author   Polaris Zhao
 *  @version  3.0
 *
 *  This is an internal header file, included by other library headers.
 *  Do not attempt to use it directly. Please #include @c <byte_stream>.
**/

#ifndef _POL_BSTREAM_TCC
#define _POL_BSTREAM_TCC 1

namespace polaris
{

template<typename _Tp>
byte_stream<_Tp>::
byte_stream(_Tp&& __stream)
	: _M_stream(std::move(__stream))
{
}

template<typename _Tp>
void
byte_stream<_Tp>::
open(const std::string& __s, std::ios_base::openmode __mode)
{
	_M_stream.open(__s, std::ios_base::binary | __mode);
}

template<typename _Tp>
void
byte_stream<_Tp>::
close()
{
	_M_stream.close();
}

template<typename _Tp>
bool
byte_stream<_Tp>::
is_open() const
{
	return _M_stream.is_open();
}

template<typename _Tp>
template<typename _Up>
byte_stream<_Tp>&
byte_stream<_Tp>::
operator >> (_Up& __x)
{
	std::string __buf;
	__buf.resize(sizeof(__x));
	_M_stream.read(const_cast<char*>(__buf.c_str()), __buf.size());
	memcpy(reinterpret_cast<char*>(&__x), __buf.c_str(), __buf.size());
	return *this;
}


template<typename _Tp>
template<typename _Up>
byte_stream<_Tp>&
byte_stream<_Tp>::
operator << (const _Up& __x)
{
	_M_stream.write(reinterpret_cast<const char*>(&__x), sizeof(__x));
	return *this;
}

template<typename _Tp>
byte_stream<_Tp>&
byte_stream<_Tp>::
operator >> (char* __x)
{
	_M_stream.getline(__x, 2147483647, '\0');
	return *this;
}

template<typename _Tp>
byte_stream<_Tp>&
byte_stream<_Tp>::
operator << (const char* __x)
{
	_M_stream.write(__x, strlen(__x));
	return *this;
}

template<typename _Tp>
template<size_t _BNum>
byte_stream<_Tp>&
byte_stream<_Tp>::
operator >> (ignore_byte<_BNum>& __x)
{
	std::string __buf;
	__buf.resize(_BNum);
	_M_stream.read(const_cast<char*>(__buf.c_str()), __buf.size());
	return *this;
}

template<typename _Tp>
template<size_t _BNum>
byte_stream<_Tp>&
byte_stream<_Tp>::
operator << (const ignore_byte<_BNum>& __x)
{
	std::string __buf;
	__buf.resize(_BNum);
	_M_stream.write(__buf.c_str(), __buf.size());
	return *this;
}

}

#endif
