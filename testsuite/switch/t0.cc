#include <pol/switch>
#include <iostream>

struct a_t
{
    bool operator==(const a_t&)const{return true;}
    a_t operator+(const a_t&)const{return {};}
};

struct b_t {};

int main()
{
    std::cout << pol::is_equality_comparable_with_v<a_t, b_t> << '\n';
    std::cout << pol::is_plusable_with_v<a_t, b_t> << '\n';
}
