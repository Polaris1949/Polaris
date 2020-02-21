#include <pol/bit_memory>

int x = 1;
constexpr void* p = (void*)&x;

template<typename _Tp, _Tp __x>
struct show;

int main()
{
    constexpr pol::bit_address a{p, 1};
    static_assert(a.empty());
    show<int*, (int*)a.byte_address()> _0;
    show<size_t, a.bit_level()> _1;
}
