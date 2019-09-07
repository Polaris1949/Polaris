#include <pol/bit_observer>

namespace pol
{

bit_ref
basic_bit_observer::
at(size_type __pos)
{
    if (__pos >= char_bit)
        throw std::out_of_range{"basic_bit_observer::at()"};
    return bit_ref{bit_address{&this->_M_impl._M_data, __pos}};
}

bool
basic_bit_observer::
at(size_type __pos) const
{
    switch (__pos)
    {
        case 0: return this->_M_impl._M_obs.b0;
        case 1: return this->_M_impl._M_obs.b1;
        case 2: return this->_M_impl._M_obs.b2;
        case 3: return this->_M_impl._M_obs.b3;
        case 4: return this->_M_impl._M_obs.b4;
        case 5: return this->_M_impl._M_obs.b5;
        case 6: return this->_M_impl._M_obs.b6;
        case 7: return this->_M_impl._M_obs.b7;
        default: throw std::out_of_range{"basic_bit_observer::at()"};
    }
}

bit_ref
basic_bit_observer::
operator[] (size_type __pos) noexcept
{
    return bit_ref{bit_address{&this->_M_impl._M_data, __pos}};
}

bool
basic_bit_observer::
operator[] (size_type __pos) const noexcept
{
    switch (__pos)
    {
        case 0: return this->_M_impl._M_obs.b0;
        case 1: return this->_M_impl._M_obs.b1;
        case 2: return this->_M_impl._M_obs.b2;
        case 3: return this->_M_impl._M_obs.b3;
        case 4: return this->_M_impl._M_obs.b4;
        case 5: return this->_M_impl._M_obs.b5;
        case 6: return this->_M_impl._M_obs.b6;
        case 7: return this->_M_impl._M_obs.b7;
        default: return false;
    }
}

void
basic_bit_observer::
set(size_type __pos)
{
    switch (__pos)
    {
        case 0: this->_M_impl._M_obs.b0 = true; return;
        case 1: this->_M_impl._M_obs.b1 = true; return;
        case 2: this->_M_impl._M_obs.b2 = true; return;
        case 3: this->_M_impl._M_obs.b3 = true; return;
        case 4: this->_M_impl._M_obs.b4 = true; return;
        case 5: this->_M_impl._M_obs.b5 = true; return;
        case 6: this->_M_impl._M_obs.b6 = true; return;
        case 7: this->_M_impl._M_obs.b7 = true; return;
        default: throw std::out_of_range{"basic_bit_observer::set()"};
    }
}

void
basic_bit_observer::
reset(size_type __pos)
{
    switch (__pos)
    {
        case 0: this->_M_impl._M_obs.b0 = false; return;
        case 1: this->_M_impl._M_obs.b1 = false; return;
        case 2: this->_M_impl._M_obs.b2 = false; return;
        case 3: this->_M_impl._M_obs.b3 = false; return;
        case 4: this->_M_impl._M_obs.b4 = false; return;
        case 5: this->_M_impl._M_obs.b5 = false; return;
        case 6: this->_M_impl._M_obs.b6 = false; return;
        case 7: this->_M_impl._M_obs.b7 = false; return;
        default: throw std::out_of_range{"basic_bit_observer::reset()"};
    }
}

void
basic_bit_observer::
flip(size_type __pos)
{
    if (__pos >= 8) throw std::out_of_range{"basic_bit_observer::flip()"};
    if (this->at(__pos)) this->reset(__pos);
    else this->set(__pos);
}

std::istream&
operator >> (std::istream& __in, basic_bit_observer& __x)
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
operator << (std::ostream& __out, const basic_bit_observer& __x)
{
    for (std::size_t __i{}; __i < char_bit; ++__i)
    {
        std::size_t __j{char_bit - 1 - __i};
        __out << char(__x[__j] + '0');
    }

    return __out;
}

}
