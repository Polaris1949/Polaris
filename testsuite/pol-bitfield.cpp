#include <polaris/bitfield>
#include <iostream>
using namespace std;
using namespace pol;

struct _Exbyte
{
    union _Byte
    {
        unsigned char __n;

        struct _Bit
        {
            bool b0 : 1;
            bool b1 : 1;
            bool b2 : 1;
            bool b3 : 1;
            bool b4 : 1;
            bool b5 : 1;
            bool b6 : 1;
            bool b7 : 1;

            bool operator[] (size_t __pos) const noexcept
            {
                switch (__pos)
                {
                    case 0: return b0;
                    case 1: return b1;
                    case 2: return b2;
                    case 3: return b3;
                    case 4: return b4;
                    case 5: return b5;
                    case 6: return b6;
                    case 7: return b7;
                    default: return false;
                }
            }
        };

        _Bit __b;

        bool operator[] (size_t __pos) const noexcept
        {
            return __b[__pos];
        }
    };
};

int main()
{
    _Exbyte x;
    x.__n = 10;
    cout << x[1] << endl;
    cout << sizeof(x) << endl;

    return 0;
}
