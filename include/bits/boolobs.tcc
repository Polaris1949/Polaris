#ifndef _POL_BOOLOBS_TCC
#define _POL_BOOLOBS_TCC 1

#include <stdexcept>
#include <iostream>

namespace polaris
{

bool
basic_bool_observer::
at(size_type __pos) const
{
    switch (__pos)
	{
		case 0: return b0;
		case 1: return b1;
		case 2: return b2;
		case 3: return b3;
		case 4: return b4;
		case 5: return b5;
		case 6: return b6;
		case 7: return b7;
		default: throw std::out_of_range{"basic_bool_observer::at()"};
	}
}

bool
basic_bool_observer::
operator[] (size_type __pos) const noexcept
{
	switch (__pos)
	{
		case 0: return b0;
		case 1: return b1;
		case 2: return b2;
		case 3: return b3;
		case 4: return b4;
		case 5: return b5;
		case 6: return b6;
		case 7: return b7;
		default: return false;
	}
}

void
basic_bool_observer::
set(size_type __pos)
{
    switch (__pos)
	{
		case 0: b0 = true; return;
		case 1: b1 = true; return;
		case 2: b2 = true; return;
		case 3: b3 = true; return;
		case 4: b4 = true; return;
		case 5: b5 = true; return;
		case 6: b6 = true; return;
		case 7: b7 = true; return;
		default: throw std::out_of_range{"basic_bool_observer::set()"};
	}
}

void
basic_bool_observer::
reset(size_type __pos)
{
    switch (__pos)
	{
		case 0: b0 = false; return;
		case 1: b1 = false; return;
		case 2: b2 = false; return;
		case 3: b3 = false; return;
		case 4: b4 = false; return;
		case 5: b5 = false; return;
		case 6: b6 = false; return;
		case 7: b7 = false; return;
		default: throw std::out_of_range{"basic_bool_observer::reset()"};
	}
}

void
basic_bool_observer::
flip(size_type __pos)
{
    if (__pos >= 8) throw std::out_of_range{"basic_bool_observer::flip()"};
    if (this->at(__pos)) this->reset(__pos);
    else this->set(__pos);
}

std::istream&
operator >> (std::istream& __in, basic_bool_observer& __x)
{
	for (std::size_t __i{}; __i < char_bit; ++__i)
	{
        std::size_t __j{char_bit - 1 - __i};
		char __ch;
		__in >> __ch;

		if (!(__ch == '0' || __ch == '1'))
		{
			__in.setstate(std::ios_base::failbit);
			return __in;
		}

        if (__ch - '0') __x.set(__j);
        else __x.reset(__j);
	}

	return __in;
}

std::ostream&
operator << (std::ostream& __out, const basic_bool_observer& __x)
{
    for (std::size_t __i{}; __i < char_bit; ++__i)
	{
        std::size_t __j{char_bit - 1 - __i};
        char __ch{__x[__j] + '0'};
		__out << __ch;
	}

	return __out;
}

}

#endif /* _POL_BOOLOBS_TCC */
