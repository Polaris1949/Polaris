#include <polaris/console>
#include <iostream>
#include <unistd.h>
using namespace std;
using namespace polaris;

int main()
{
    cerr << '0' << endl;
    console.underline();
    cerr << "1234" << endl;
    console.coruscate();
    cerr << "TEXT" << endl;
    sleep(1);
    console.clear_screen();
    console.locate(2,2);
    console.foreground_color(2);
    console.background_color(4);
    cerr << "OKAY?" << endl;
    console.purge();
    console.hide_cursor();
    cerr << "HIDE!!!" << endl;
    cerr << endl << endl << endl;
    sleep(1);
    console.show_cursor();
    sleep(1);
    console.purge();
    console.clear_screen();
    console.hide_cursor();
    console.locate(11, 39);
    cerr << "PK" << endl;
    console.locate(12, 35);
    cerr << "Loading";
    for (int i=0; i<2; ++i)
    {
        console.locate(12, 42);
        console.clear_line_after();
        for (int j=0; j<3; ++j)
        {
            cerr<<'.';
            sleep(1);
        }
    }
    cerr<<endl;
    console.show_cursor();
    sleep(1);
    console.purge();
    console.clear_screen();
    console.hide_cursor();
    console.locate(11, 39);
    cerr << "PK" << endl;
    console.locate(12, 35);
    cerr << "Loading";
    string s="-\\|/";
    for (int i=0; i<4; ++i)
    {
        for (int j=0; j<4; ++j)
        {
            console.locate(12, 44);
            cerr<<s[j];
            sleep(1);
        }
    }
    cerr<<endl;
    console.show_cursor();
    return 0;
}
