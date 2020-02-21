#include <pol/contract>

int main()
{
    constexpr auto x = pol::assert(false, "runtime error", "test");
    constexpr auto y = pol::expect(false, "logic error", "test");
    constexpr auto z = pol::ensure(false, "system error", "test");
}
