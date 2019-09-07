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
    sleep(1);
    terminal::normal();
    terminal::clear_screen();
    terminal::hide_cursor();
    terminal::locate(11, 39);
    cerr << "PK" << endl;
    terminal::locate(12, 35);
    cerr << "Loading";
    for (int i=0; i<2; ++i)
    {
        terminal::locate(12, 42);
        terminal::erase_line(0);
        for (int j=0; j<3; ++j)
        {
            cerr<<'.';
            sleep(1);
        }
    }
    cerr<<endl;
    terminal::show_cursor();
    sleep(1);
    terminal::normal();
    terminal::clear_screen();
    terminal::hide_cursor();
    terminal::locate(11, 39);
    cerr << "PK" << endl;
    terminal::locate(12, 35);
    cerr << "Loading";
    string s="-\\|/";
    for (int i=0; i<4; ++i)
    {
        for (int j=0; j<4; ++j)
        {
            terminal::locate(12, 44);
            cerr<<s[j];
            sleep(1);
        }
    }
    cerr<<endl;
    terminal::show_cursor();
    return 0;
}
