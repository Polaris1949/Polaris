#include <pol/log>

int main() try
{
    pol::log(pol::log_priority::error, "TEST", 0xcdcdfffe, pol::log_srcloc(), "DEBUG");
} catch (...) {std::terminate();}