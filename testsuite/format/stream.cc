#include <pol/format>
#include <iostream>

int main()
{
    std::string name;
    std::cin >> name;
    fmt::print(stderr, fmt::fg(fmt::terminal_color::bright_white), "Hello, {}!\n", name);
}
