#include <iostream>

int lowbit(int x)
{ return x&(-x); }

int lowbit0(int x)
{ return (x+1)&(~x); }

int main()
{
    for (int i=-100; i<100; ++i)
    {
        int x=lowbit(i+1);
        int y=lowbit0(i);
        std::cout << x << ' ' << y << '\n';
        if (x!=y) throw std::logic_error{"QAQAQ!"};
    }
}
