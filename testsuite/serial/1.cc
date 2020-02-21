#include <iostream>

using type = char(&)[8];
char x[8]="hello";

type fun()
{
    return x;
}

int main()
{
    std::cout << fun() << '\n';
}