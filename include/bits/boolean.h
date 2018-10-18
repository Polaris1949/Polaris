// A fundamental type for holding a boolean value -*- C++ -*-

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

/** @file        bits/boolean.h
 *  @headerfile  boolean
 *  @brief       A fundamental type for holding a boolean value
 *  @author      Polaris Zhao
 *  @version     3.0
 *
 *  This is an internal header file, included by other library headers.
 *  Do not attempt to use it directly.
**/

#ifndef _POL_BOOLEAN_H
#define _POL_BOOLEAN_H 1

#include <iosfwd>

namespace polaris
{

/** @class  boolean
 *  @brief  A class for holding a boolean value
 *  @note   You should only use it as @c std::vector<boolean>.
**/
class boolean
{
public:
    using value_type = bool;

private:
	bool _M_data;

public:
	/** @brief  Construct a default @c boolean
	 *  @attention  The value of the object is undefined.
	**/
	boolean() noexcept = default;

	/** @brief  Construct a @c boolean from a @c bool
	 *  @param  __arg  A @c bool value.
	 *  @note  It is an implicit conversion constructor.
	**/
	boolean(bool __arg) noexcept;

	/** @brief  Copy construct a @c boolean from another
	 *  @param  __arg  Another @c boolean.
	 *  @attention  The value is undefined if @c __arg is undefined.
	**/
	boolean(const boolean& __arg) noexcept = default;

	/** @brief  Move construct a @c boolean from another
	 *  @param  __arg  Another @c boolean.
	 *  @attention  The value is undefined if @c __arg is undefined.
	**/
	boolean(boolean&& __arg) noexcept = default;

	/** @brief  Destroy the @c boolean
	**/
	~boolean() noexcept = default;

	/** @brief  Copy assign another @c boolean
	 *  @param  __arg  Another @c boolean.
	 *  @return  The object itself.
	 *  @attention  The value is undefined if @c __arg is undefined.
	**/
	boolean&
	operator = (const boolean& __arg) noexcept = default;

	/** @brief  Move assign another @c boolean
	 *  @param  __arg  Another @c boolean.
	 *  @return  The object itself.
	 *  @attention  The value is undefined if @c __arg is undefined.
	**/
	boolean&
	operator = (boolean&& __arg) noexcept = default;

	/** @brief  Compare two @c boolean using @c ==
	 *  @param  __arg  Another @c boolean.
	 *  @return  A @c bool containing the result.
	 *  @retval  true   Two @c boolean are equal.
	 *  @retval  false  Otherwise.
	 *  @attention  The comparsion is undefined if @c __arg is undefined.
	**/
	bool
	operator == (const boolean& __arg) const noexcept;

	/** @brief  Compare two @c boolean using @c !=
	 *  @param  __arg  Another @c boolean.
	 *  @return  A @c bool containing the result.
	 *  @retval  true   Two @c boolean are not equal.
	 *  @retval  false  Otherwise.
	 *  @attention  The comparsion is undefined if @c __arg is undefined.
	**/
	bool
	operator != (const boolean& __arg) const noexcept;

	/** @brief  Covert the @c boolean to a @c bool
	 *  @return  The value contained by the object.
	 *  @note  It is an explicit conversion operator.
	 *  @attention  The value is undefined if the object is undefined.
	**/
	explicit
	operator bool() const noexcept;

	/** @brief  Input a @c boolean
	 *  @param  __in  An input stream object.
	 *  @param  __arg  A @c boolean.
	 *  @return  The stream object.
	 *  @exception  Depend on the input.
	**/
	friend std::istream&
	operator >> (std::istream& __in, boolean& __arg);

	/** @brief  Output a @c boolean
	 *  @param  __out  An output stream object.
	 *  @param  __arg  A @c boolean.
	 *  @return  The stream object.
	 *  @attention  The output is undefined if the @c boolean is undefined.
	**/
	friend std::ostream&
	operator << (std::ostream& __out, const boolean& __arg);
};

}

#endif /* _POL_BOOLEAN_H */
