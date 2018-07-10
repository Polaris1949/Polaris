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
    return 0;
}
