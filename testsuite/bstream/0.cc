#include <polaris/binary_stream>
#include <fstream>

int main()
{
    pol::binary_stream<std::ofstream> fout;
    fout.open("dove.coo.txt", std::ios_base::out | std::ios_base::trunc);
    fout << "gugugu" << 19260817 << char(128) << "moha";
    fout << 817 << "gg";
    fout.close();
}
