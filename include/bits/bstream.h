// Byte stream class -*- C++ -*-

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

/** @file     bits/bstream.h
 *  @brief    Byte stream class
 *  @author   Polaris Zhao
 *  @version  3.0
 *
 *  This is an internal header file, included by other library headers.
 *  Do not attempt to use it directly. Please #include @c <byte_stream>.
**/

#ifndef _POL_BSTREAM_H
#define _POL_BSTREAM_H 1

namespace polaris
{

// Forward declaration.
template<typename>
class byte_stream;

template<size_t>
struct ignore_byte;

/** @class  ignore_byte
 *  @brief  Utility struct to ignore bytes in a @c byte_stream
 *  @tparam  _Num  Number of bytes to ignore.
**/
template<size_t _Num>
struct ignore_byte
{
	typedef ignore_byte<_Num> type;
	static constexpr size_t value = _Num;
};

/** @class  byte_stream
 *  @brief  A @c class for I/O stream byte operations.
 *  @tparam  _Tp  Type of the contained stream object.
 *  @attention  You should @b NOT use this on standard streams, i.e.
                @c std::cin, @c std::cout, @c std::cerr and @c std::clog.
**/
template<typename _Tp>
class byte_stream
{
public:
	/** @brief  Type of the contained stream object. **/
	typedef _Tp stream_type;

private:
	_Tp _M_stream;

public:
	/** @brief  Construct a deafult @c byte_stream
	 *  @attention  The contained object is undefined.
	**/
	byte_stream() = default;

	/** @brief  Move construct a @c byte_stream from another stream
	 *  @param  __stream  The stream object.
	 *  @attention  You should @b NOT use @c __stream after this.
	 *              So you should @b NOT use this on standard streams.
	**/
	byte_stream(_Tp&& __stream);

	/** @brief  Move construct a @c byte_stream from another @c byte_stream
	 *  @param  __stream  The stream object.
	 *  @attention  You should @b NOT use @c __stream after this.
	 *              So you should @b NOT use this on standard streams.
	**/
	byte_stream(byte_stream&& __stream) = default;

	/** @brief  Destroy the @c byte_stream
	**/
	~byte_stream() noexcept = default;

	/** @brief  Open a @c byte_stream
	 *  @param  __s  A filename.
	 *  @param  __mode  An open mode.
	**/
	void open(const std::string& __s, std::ios_base::openmode __mode);

 	/** @brief  Close a @c byte_stream
	**/
	void close();

	/** @brief  Check a @c byte_stream is whether open or not
	 *  @return  A @c bool value contained the result.
	 *  @retval  true  The @c byte_stream is open.
	 *  @retval  false  The @c byte_stream is closed.
	**/
	bool is_open() const;

	/** @brief  Read a value from a @c byte_stream
	 *  @tparam  _Up  Type of a value.
	 *  @param  __x  A value.
	 *  @return  The object itself.
	**/
	template<typename _Up>
	byte_stream& operator >> (_Up& __x);

	/** @brief  Write a value to a @c byte_stream
	 *  @tparam  _Up  Type of a value.
	 *  @param  __x  A value.
	 *  @return  The object itself.
	**/
	template<typename _Up>
	byte_stream& operator << (const _Up& __x);

	/** @brief  Read a c-string from a @c byte_stream
	 *  @param  __x  A c-string.
	 *  @return  The object itself.
	**/
	byte_stream& operator >> (char* __x);

	/** @brief  Write a c-string to a @c byte_stream
	 *  @param  __x  A c-string.
	 *  @return  The object itself.
	**/
	byte_stream& operator << (const char* __x);

	/** @brief  Read bytes and ignore them
	 *  @tparam  _BNum  Number of ignored bytes.
	 *  @param  __x  A @c ignore_byte value.
	 *  @return  The object itself.
	**/
	template<size_t _BNum>
	byte_stream& operator >> (ignore_byte<_BNum>& __x);

	/** @brief  Write bytes and ignore them
	 *  @tparam  _BNum  Number of ignored bytes.
	 *  @param  __x  A @c ignore_byte value.
	 *  @return  The object itself.
	**/
	template<size_t _BNum>
	byte_stream& operator << (const ignore_byte<_BNum>& __x);
};

}

#endif
