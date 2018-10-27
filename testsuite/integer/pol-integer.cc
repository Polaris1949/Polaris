#define _POL_DEBUG 1
#define _POL_NEWLIB 0 // Be careful!!!
#include <iostream>
#include <polaris/integer>
using namespace std;
using namespace polaris;

#if _POL_DEBUG
#define dbg_print(X) print_data(X)
void print_data(const integer& x)
{
	cout<<"_M_length:"<<x._M_length<<endl;
	for (size_t i=0; i<x._M_length; ++i)
		cout<<"_M_dataplus["<<i<<"]:"<<(unsigned)x._M_dataplus[i]<<endl;
}
#else
#define dbg_print(X) void()
#endif

int main()
{
	/*
	_Int_base x(9294960000ll);
	cout << x._M_dataplus << endl;
	cout << *(_Int_exdata*)x._M_dataplus << endl;
	cout << x._M_length << endl;
	_Int_base y(4999992705ll);
	cout << y._M_dataplus << endl;
	cout << *(_Int_exdata*)y._M_dataplus << endl;
	cout << y._M_length << endl;
	x._M_basic_minus(y);
	cout << x._M_dataplus << endl;
	cout << *(_Int_exdata*)x._M_dataplus << endl;
	cout << x._M_length << endl;
	x._M_basic_increment();
	cout << x._M_dataplus << endl;
	cout << *(_Int_exdata*)x._M_dataplus << endl;
	cout << x._M_length << endl;
	*/
	integer xi(4294967296ull);
	cout<<"Address:"<<(void*)xi._M_dataplus<<endl;
	cout<<"Sign:"<<xi.sign()<<endl;
	cout<<"Size:"<<xi.size()<<endl;
	dbg_print(xi);
	return 0;
}
