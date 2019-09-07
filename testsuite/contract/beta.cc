#include <polaris/contract>

int main()
{
    pol::__ctr_set_conti(true);
    pol::__ctr_set_level(3);
    pol::expect(false, "runtime error", "dove", 1);
    pol::assert(false, "runtime error", "dove", 0);
    pol::ensure(false, "runtime error", "dove", 3);
}
