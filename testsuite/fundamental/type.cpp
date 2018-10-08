#include <iostream>
#include <polaris/type>
using namespace std;
using namespace polaris;

struct test_t {};

int main()
{
    type t = type(test_t());
    t.construct(6);
}
