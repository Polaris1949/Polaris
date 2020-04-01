#include <pol/serial_stream>
#include <algorithm>
#include <fstream>
#include <iostream>

struct rev_string
{
    std::string s;
};

struct student
{
    rev_string name;
    int mark;
};

pol::serial_ostream&
operator << (pol::serial_ostream& out, const rev_string& x)
{
    std::string r;
    std::reverse_copy(x.s.begin(), x.s.end(), std::back_inserter(r));
    out << r;
    return out;
}

pol::serial_ostream&
operator << (pol::serial_ostream& out, const student& x)
{
    out << x.name << x.mark;
    return out;
}

int main() try
{
    std::ofstream fout("a.txt");
    pol::serial_ostream ose(fout);
    student x = {"ZhaoYi", 100};
    ose << x;
}
catch (...) { std::terminate(); }
