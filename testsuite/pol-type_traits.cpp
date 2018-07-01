#include <polaris/type_traits>
#include <iostream>
using namespace std;
using namespace polaris;

int x, y;

void f()
{
}
struct b;
struct a
{
	bool operator==(const b&);
};

struct b : public a
{
};

struct c : public a
{
};

struct d : public b, c
{
	bool operator!() const;
};

int main()
{
	//cout<<is_functor<decltype(f)>::value<<endl;
	//cout<<is_equality_comparable<decltype(f)>::value<<endl;
	//cout<<is_equality_comparable_with<a, b>::value<<endl;
	//cout<<is_same<int, int>::value<<endl;
	//d t;
	//a* p=&t;
	//cout<<__ttc::c_is_derived_from<d, a>::value<<endl;
	//cout<<is_convertible_to<a, b>::value<<endl;
	//cout<<is_callable<decltype(f)>::value<<endl;
	cout<<ho_logical_not<d>::value<<endl;
	return 0;
}
