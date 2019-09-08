#include <pol/terminal>
#include <iostream>
#include <unistd.h>
using namespace std;
using namespace polaris;

int main()
{
    cerr << '0' << endl;
    terminal::underline();
    cerr << "1234" << endl;
    //console.coruscate();
    cerr << "TEXT" << endl;
    sleep(1);
    terminal::clear_screen();
    terminal::locate(2,2);
    terminal::color_fg(2);
    terminal::color_bg(4);
    cerr << "OKAY?" << endl;
    terminal::normal();
    terminal::hide_cursor();
    cerr << "HIDE!!!" << endl;
    cerr << endl << endl << endl;
    sleep(1);
    terminal::show_cursor();
    terminal::normal();
    return 0;
}
