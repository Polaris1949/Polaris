#include <pol/format>
#include <iostream>

int main()
{
    std::ios_base::sync_with_stdio(false);
    pol::ftext t{fmt::fg(fmt::terminal_color::bright_white), "Hello!"};
    pol::ftext e{{}, "\n"};
    std::cout << t << e;
}
