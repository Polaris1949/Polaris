#include <iostream>
#include <pol/binary_integer>

using bbint = pol::basic_binary_integer;

void print_elem(pol::_Int_data n)
{
	std::string s;
	size_t i=0;
	while (i++<sizeof(n)*8)
	{
		s=(n&1?'1':'0')+s;
		n>>=1;
	}
	std::cout<<s<<std::endl;
}

void print_bitfield(pol::_Int_data* b, pol::_Int_data* e)
{
	while (b<e)
		print_elem(*b++);
}

int main()
{
    bbint x{19260817u};
    print_bitfield(x.begin(), x.end());
    bbint y{666666u};
    print_bitfield(y.begin(), y.end());
    x^=y;
    print_bitfield(x.begin(), x.end());
    x.flip();
    print_bitfield(x.begin(), x.end());
}