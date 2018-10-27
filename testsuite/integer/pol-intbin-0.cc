#include <iostream>
#include <string>
#include <deque>
#include <sstream>
#include <cstdlib>
#define private public
#define protected public
#include <polaris/byte>
#include <polaris/binary_integer>

using polaris::exbyte;
using polaris::_Int_data;
using polaris::_Int_exdata;
using polaris::_Int_base;
using bbint = polaris::basic_binary_integer;
using byte = polaris::unsigned_byte;
using std::cout;
using std::endl;

class _Bitfield
{
    _Int_base* _M_ptr;

public:
    _Bitfield() : _M_ptr() {}
    _Bitfield(_Int_base* __ptr) : _M_ptr(__ptr) {}

    friend std::ostream&
    operator << (std::ostream& __out, const _Bitfield& __x)
    {
        _Int_data* __b = __x._M_ptr->_M_impl._M_start;
        _Int_data* __e = __x._M_ptr->_M_impl._M_finish;
        std::deque<std::string> __d;

        while (__b < __e)
        {
            _Int_data __t = *__b++;

            for (size_t __i = 0; __i < sizeof(_Int_data); ++__i)
            {
                std::stringstream __oss;
                __oss << exbyte(byte(__t));
                __d.push_front(__oss.str());
                __t >>= 8;
            }
        }

        for (const std::string& __s : __d)
            __out << __s << ' ';

        return __out;
    }
};

int main()
{
    /*
    bbint x{9223372036854775808ull};
    bbint y{9223372036854775809ull};
    _Bitfield bx(reinterpret_cast<_Int_base*>(&x));
    _Bitfield by(reinterpret_cast<_Int_base*>(&y));
    cout << bx << endl;
    cout << by << endl;
    x += y;
    cout << bx << endl;
    cout << x.size() << ' ' << x.capacity() << endl;
    x -= y;
    cout << bx << endl;
    cout << x.size() << ' ' << x.capacity() << endl;
    */
    srand((unsigned)time(nullptr));
    std::cout << malloc_usable_size() << '\n';

    /*{
        bbint x{128u};
        bbint y{255u};
        //x._M_basic_minus(y);
        bbint z{y.flip()};
        std::cout << _Bitfield{&z} << '\n';
        x._M_basic_calc(y.flip()+bbint(1u), std::plus<_Int_exdata>{});
        std::cout << _Bitfield{&x} << '\n';
    }*/

    return 0;
}
