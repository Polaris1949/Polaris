#include <polaris/concepts>

class foo {};
class bar : public foo {};

int main()
{
    static_assert(std::is_same_v<pol::common_reference_t<int, char>, int>);
    // static_assert(std::is_same_v<pol::common_reference_t<foo&, bar&>, foo&>);
    return 0;
}
