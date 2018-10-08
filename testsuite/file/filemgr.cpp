#include <iostream>
#include <string>
#include <polaris/filemgr>
using namespace std;
using namespace polaris;

filemgr f;

int main()
{
	int x;
	file_handle fin=f.open("pol-filemgr.txt");
	fin >> x;
	return 0;
}
