#include <polaris/exception>

int main() try
{
    pol::throw_ex(pol::exception{std::runtime_error{"dove"}});
}
catch (...) { std::terminate(); }
