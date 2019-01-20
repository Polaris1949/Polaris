#include <polaris/type>
#include <iostream>

template<typename _Tp, bool _Req = std::is_fundamental_v<_Tp>>
struct foo : public _Tp {};

template<typename _Tp>
struct foo<_Tp, true> : public pol::fundamental_type<_Tp> {};

struct bar
{
    bar() = default;
    bar(int) {}
    bar& operator += (const bar&)
    { std::cout << "bar\n"; return *this; }
};

int main()
{
    foo<bar> x{1}; x+=x;
    foo<int> y{2}; y+=y; std::cout << y.data() << '\n';
}
