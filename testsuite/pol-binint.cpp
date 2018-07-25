#define _POL_NEWLIB 1
#define _POL_DEBUG 1
#define _POL_DEPRECATED 1
#include <iostream>
#include <polaris/binary_integer>
#include <polaris/tag>
using namespace std;
using namespace polaris;

using llong=long long;

basic_binary_integer x((llong)2147483648*2147483647);
basic_binary_integer y((int)666666);
_Int_reference r((_Int_base*)&x, 0);

void print_elem(_Int_data n)
{
	string s;
	size_t i=0;
	while (i++<sizeof(n)*8)
	{
		s=(n&1?'1':'0')+s;
		n>>=1;
	}
	cout<<s<<endl;
}

void print_bitfield(_Int_data* b, _Int_data* e)
{
	while (b<e)
		print_elem(*b++);
}

struct tc
{
	size_t _M_data;

	template<typename _Tp, typename... _Rest>
	size_t operator!() // only t.operator!<...>();
	{
		return _M_data = !_M_data;
	}

	template<typename _Tp, typename... _Rest>
	size_t operator+=(const tc& __x) // only t.operator+<...>();
	{
		return _M_data += __x._M_data;
	}
};
/*
template<typename... _Args>
class type_wrap
{
public:
	typedef std::tuple<_Args...> type_pack;
	constexpr static size_t type_pack_size = std::tuple_size<type_pack>::value;
	template<size_t __i> using type = typename std::tuple_element<__i, \
		type_pack>::type;

	constexpr size_t
	size() const
	{
		return type_pack_size;
	}
};
*/
int main()
{
	tc x{0};
	tc y{3};
	//type_wrap<int> tw;
//	cout<<tw.size()<<endl;
	auto tpx=make_tpop_wrap(make_tvalue<int>(x));
	auto tpy=make_tpop_wrap(make_tvalue<int>(y));
	//auto tpa=make_tpop_wrap(make_tvalue(8));
	cout<<(!tpx)<<endl;
	cout<<(!tpx)<<endl;
	cout<<(!tpx)<<endl;
	cout<<(tpx+=tpy)<<endl;

	//cout<<(tpa+=2)<<endl;
	/*cout<<x.size()<<endl;
	cout<<x.capacity()<<endl;
	cout<<*x.data()<<endl;
	cout<<*(x.data()+1)<<endl;
	cout<<*x.data()<<endl;
	cout<<r<<endl;
	r={(_Int_base*)&y, 0};
	cout<<r<<endl;
	cout<<"----"<<endl;*/
	/*
	print_bitfield(x.data(), x.data()+x.size());
	cout<<endl;
	x.flip();
	print_bitfield(x.data(), x.data()+x.size());
	cout<<endl;
	x^=y;
	print_bitfield(x.data(), x.data()+x.size());
	cout<<endl;
	*/
	// Implement operator+ first, then +=.
	// Other operators -, *, / and % likewise.
	return 0;
}
