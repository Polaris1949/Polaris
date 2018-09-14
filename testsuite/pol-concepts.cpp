#include <polaris/concepts>
#include <iostream>
using namespace std;
using namespace polaris;

struct animal {};
struct human : public animal {};
struct dog : public animal {};
struct alien : private animal {};

int main()
{
    // @TODO
    static_assert(Same<int, signed int>);
    static_assert(!Same<char, signed char>);
    static_assert(DerivedFrom<human, animal>);
    static_assert(!DerivedFrom<alien, animal>);
    static_assert(ConvertibleTo<human, animal>);
    static_assert(!ConvertibleTo<alien, animal>);
    static_assert(CommonReference<animal&, dog&>);
    static_assert(!CommonReference<human&, dog&>);
    static_assert(Common<animal, human>);
    static_assert(!Common<alien, dog>);
    static_assert(Integral<int>);
    static_assert(!Integral<int*>);
    static_assert(SignedIntegral<char>);
    static_assert(!SignedIntegral<void*>);
    static_assert(UnsignedIntegral<bool>);
    static_assert(!UnsignedIntegral<char*>);
    static_assert(Boolean<bool>);
    static_assert(!Boolean<dog>);
    return 0;
}
