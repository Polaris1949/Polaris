#include <pol/terminal>
#include <unistd.h>
#include <iostream>

int main()
{
    pol::terminal::resize_screen(52, 150);
	std::cout << "dove\n";
	sleep(2);
	pol::terminal::resize_screen(24, 80);
}
