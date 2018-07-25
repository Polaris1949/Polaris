#include <polaris/bitfield>
#include <iostream>
#include <type_traits>
using namespace std;
using namespace pol;

int pow2[8]={1,2,4,8,16,32,64,128};

template<typename _Tp>
bool num_from_char(_Tp& __x, char __c)
{
    static_assert(is_integral_v<_Tp>);
    if (!isdigit(__c)) return false;
    __x = static_cast<_Tp>(__c - '0');
    return true;
}

union exbyte
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

    friend istream& operator >> (istream& __in, _Exbyte& __x)
    {
        int s{};
        for (int i=7; i>=0; --i)
        {
            char ch;
            __in >> ch;
            if (!(ch=='0'||ch=='1'))
            {
                __in.setstate(ios_base::failbit);
                return __in;
            }
            s+=int(ch-'0')*pow2[i];
        }
        __x.__n = s;
        return __in;
    }

    friend ostream& operator << (ostream& __out, const _Exbyte& __x)
    {
        for (int i=7; i>=0; --i)
            __out<<__x[i];
        return __out;
    }
};

int main()
{
    _Exbyte x;
    x.__n = 10;
    cout << x[1] << endl;
    cout << sizeof(x) << endl;
    cout << x << endl;
    cin >> x;
    cout << (int)x.__n << endl;
    return 0;
}
