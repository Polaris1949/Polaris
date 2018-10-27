#include <iostream>
#include <string>
#include <polaris/switch>

struct a_t {bool operator==(const a_t&)const{return true;}} a;
struct b_t {} b;

int main()
{
    std::cout << pol::one_of(a, std::make_tuple(b, a)) << '\n';
}
