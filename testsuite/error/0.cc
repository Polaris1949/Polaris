#include <polaris/error>

int main() try
{
    pol::__eh_exception(std::move(pol::exception{std::runtime_error{"dove"}}));
}
catch (...) { std::terminate(); }
