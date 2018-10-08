#include <iostream>
#include <polaris/boolean>
using namespace std;
using namespace polaris;

void f(bool __x)
{
	cout << "f(bool)" << endl;
}

void f(int __x)
{
	cout << "f(int)" << endl;
}

int main()
{
	int x=0;
	boolean b;
	cout << b << endl;
	cout << sizeof(b) << endl;
	if (b)
	{
		cout << b << endl;
	}
}
