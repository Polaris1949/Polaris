#include <polaris/exception>

int fun(int x)
{
    pol::expect(x >= 0, "x >= 0");
    ++x;
    pol::ensure(x > 0, "x > 0");
    return x;
}

int main()
{
    fun(2147483647);
    return 0;
}
