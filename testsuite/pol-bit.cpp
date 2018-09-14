#include <iostream>
#include <polaris/bit>

struct helper_t {} helper;

template<typename _Tp, typename _Up>
void operator & (const _Tp&, const _Up&)
{
    std::cerr << "operator &: " << typeid(_Tp).name() << ' '
        << typeid(_Up).name() << '\n';
}

int main()
{
    pol::bit x{true};
}
