#ifndef _POL_RADIXINT_H
#define _POL_RADIXINT_H 1

#include <iosfwd>
#include <deque>

namespace polaris
{

class radix_integer
{
public:
	typedef unsigned_char              byte_type;
	typedef std::deque<unsigned_char>  container_type;
	typedef size_t                     size_type;

private:
	unsigned_char _M_radix;
	std::deque<unsigned_char> _M_data;

	friend class radix_integer_io_facet;

public:
	template<typename _T>
	static container_type
	to_container(_T __n, byte_type __r = static_cast<byte_type>(100));

	template<typename _T>
	static size_type
	integer_length(_T __n);

public:
	radix_integer();

	template<typename _T>
	radix_integer(_T __n, byte_type __r = static_cast<byte_type>(100));

	explicit
	radix_integer(const container_type& __x,
		byte_type __r = static_cast<byte_type>(100));

	radix_integer(const radix_integer& __x);

	radix_integer(radix_integer&& __x);

	~radix_integer() __noexcept__;

	void
	swap(radix_integer& __x);

	const container_type&
	data() const;

	radix_integer
	operator + (const radix_integer& __x) const;

	radix_integer
	operator - (const radix_integer& __x) const;

	radix_integer
	operator * (const radix_integer& __x) const;

	radix_integer
	operator / (const radix_integer& __x) const;

	radix_integer
	operator % (const radix_integer& __x) const;

	friend std::istream&
	operator >> (std::istream& __in, radix_integer& __x);

	friend std::ostream&
	operator << (std::ostream& __out, const radix_integer& __x);
};

class radix_integer_io_facet
{

};

}

#endif
