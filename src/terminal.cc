#include <pol/terminal>
#include <iostream>
#include <string>

namespace pol
{

void
terminal::move_up(int __n)
{
	std::string __s{"\e[_A"};
	__s.replace(2, 1, std::to_string(__n));
	std::cout << __s;
}

void
terminal::move_down(int __n)
{
	std::string __s{"\e[_B"};
	__s.replace(2, 1, std::to_string(__n));
	std::cout << __s;
}

void
terminal::move_right(int __n)
{
	std::string __s{"\e[_C"};
	__s.replace(2, 1, std::to_string(__n));
	std::cout << __s;
}

void
terminal::move_left(int __n)
{
	std::string __s{"\e[_D"};
	__s.replace(2, 1, std::to_string(__n));
	std::cout << __s;
}

void
terminal::next_line(int __n)
{
	std::string __s{"\e[_E"};
	__s.replace(2, 1, std::to_string(__n));
	std::cout << __s;
}

void
terminal::prev_line(int __n)
{
	std::string __s{"\e[_F"};
	__s.replace(2, 1, std::to_string(__n));
	std::cout << __s;
}

void
terminal::locate_column(int __p)
{
	std::string __s{"\e[_G"};
	__s.replace(2, 1, std::to_string(__p + 1));
	std::cout << __s;
}

void
terminal::locate(int __x, int __y)
{
	std::string __s{"\e[_;_H"};
    __s.replace(2, 1, std::to_string(__x + 1));
    __s.replace(__s.find('_'), 1, std::to_string(__y + 1));
	std::cout << __s;
}

void
terminal::erase_screen(int __m)
{
	std::string __s{"\e[_J"};
	__s.replace(2, 1, std::to_string(__m));
	std::cout << __s;
}

void
terminal::clear_screen()
{
	std::cout << "\e[2J";
}

void
terminal::erase_line(int __m)
{
	std::string __s{"\e[_K"};
	__s.replace(2, 1, std::to_string(__m));
	std::cout << __s;
}

void
terminal::clear_line()
{
	std::cout << "\e[2K";
}

void
terminal::scroll_up(int __n)
{
	std::string __s{"\e[_S"};
	__s.replace(2, 1, std::to_string(__n));
	std::cout << __s;
}

void
terminal::scroll_down(int __n)
{
	std::string __s{"\e[_T"};
	__s.replace(2, 1, std::to_string(__n));
	std::cout << __s;
}

void
terminal::save_cursor()
{
	std::cout << "\e[s";
}

void
terminal::restore_cursor()
{
	std::cout << "\e[u";
}

void
terminal::reset()
{
	std::cout << "\ec";
}

void
terminal::normal()
{
	std::cout << "\e[0m";
}

void
terminal::bold()
{
	std::cout << "\e[1m";
}

void
terminal::faint()
{
	std::cout << "\e[2m";
}

void
terminal::italic()
{
	std::cout << "\e[3m";
}

void
terminal::underline()
{
	std::cout << "\e[4m";
}

void
terminal::color_reverse()
{
	std::cout << "\e[7m";
}

void
terminal::crossline()
{
	std::cout << "\e[9m";
}

void
terminal::overline()
{
	std::cout << "\e[53m";
}

void
terminal::color_fg(int __x)
{
	if (__x < 8)
	{
		std::string __s{"\e[3_m"};
		__s[3] = char('0' + __x);
		std::cout << __s;
	}
	else
	{
		std::string __s{"\e[9_m"};
		__s[3] = char('0' + (__x - 8));
		std::cout << __s;
	}
}

void
terminal::color_fg_def()
{
	std::cout << "\e[39m";
}

void
terminal::color_bg(int __x)
{
	if (__x < 8)
	{
		std::string __s{"\e[4_m"};
		__s[3] = char('0' + __x);
		std::cout << __s;
	}
	else
	{
		std::string __s{"\e[10_m"};
		__s[4] = char('0' + (__x - 8));
		std::cout << __s;
	}
}

void
terminal::color_bg_def()
{
	std::cout << "\e[49m";
}

void
terminal::show_cursor()
{
	std::cout << "\e[?25h";
}

void
terminal::hide_cursor()
{
	std::cout << "\e[?25l";
}

void
terminal::resize_screen(int __n, int __m)
{
	std::string __s{"\e[8;_;_t"};
    __s.replace(4, 1, std::to_string(__n));
    __s.replace(__s.find('_'), 1, std::to_string(__m));
    std::cout << __s;
}

void
terminal::flush()
{
	std::cout.flush();
}

}