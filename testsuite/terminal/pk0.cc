#include <pol/terminal>
#include <iostream>
#include <unistd.h>

int main()
{
    pol::terminal::clear_screen();
    pol::terminal::hide_cursor();
    pol::terminal::locate(11, 39);
    std::cout << "PK";
    pol::terminal::locate(12, 35);
    std::cout << "Loading";
	std::cout.flush();
    for (int i=0; i<10; ++i)
    {
        pol::terminal::locate(12, 42);
        pol::terminal::erase_line(0);
		std::cout.flush();
		usleep(200000);
        for (int j=0; j<3; ++j)
        {
            std::cout<<'.';
			std::cout.flush();
            usleep(200000);
        }
    }
	std::cout<<'\n';
	std::cout.flush();
    pol::terminal::show_cursor();
    pol::terminal::normal();
    return 0;
}
