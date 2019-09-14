#include <pol/contract>

int main()
{
    pol::__ctr_set_conti(true);
    constexpr auto x = pol::assert(0, "runtime error", "test");
}
