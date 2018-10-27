#include <polaris/concepts>

class foo {};
class bar : public foo {};

int main()
{
    static_assert(std::is_same_v<pol::
        __qualify_const_t<const foo, bar>, const bar>);
    static_assert(std::is_same_v<pol::
        __qualify_volatile_t<volatile foo, bar>, volatile bar>);
    static_assert(std::is_same_v<pol::
        __qualify_cv_t<const volatile foo, bar>, const volatile bar>);
    static_assert(std::is_same_v<pol::
        __qualify_lvalue_reference_t<foo&, const bar>, const bar&>);
    static_assert(std::is_same_v<pol::
        __qualify_rvalue_reference_t<foo&&, bar>, bar&&>);
    static_assert(std::is_same_v<pol::
        __qualify_reference_t<const foo&, bar&&>, bar&>);
    static_assert(std::is_same_v<pol::
        common_reference_t<int, char>, int>);
    return 0;
}
