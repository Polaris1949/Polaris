#include <iostream>
#include <polaris/ufset>
using namespace std;
using namespace polaris;

ufset<int> u;

size_t hf(const int& x)
{
	return (size_t)x;
}

int uhf(const size_t& x)
{
	return (int)x;
}

int main()
{
	u.hash_func()=&hf;
	u.unhash_func()=&uhf;
	return 0;
}
