#include <polaris/memory>
#include <iostream>

union
{
    unsigned char a[2];
    unsigned short b;
} sto;

int main()
{
    pol::bit_ptr p0{sto.a, 0x0u};
    pol::bit_ptr p1{sto.a, 0x1u};
    pol::bit_ptr p2{sto.a, 0x2u};
    pol::bit_ptr p3{sto.a, 0x3u};
    pol::bit_ptr p4{sto.a, 0x4u};
    pol::bit_ptr p5{sto.a, 0x5u};
    pol::bit_ptr p6{sto.a, 0x6u};
    pol::bit_ptr p7{sto.a, 0x7u};
    pol::bit_ptr p8{sto.a, 0x8u};
    pol::bit_ptr p9{sto.a, 0x9u};
    pol::bit_ptr pa{sto.a, 0xau};
    pol::bit_ptr pb{sto.a, 0xbu};
    pol::bit_ptr pc{sto.a, 0xcu};
    pol::bit_ptr pd{sto.a, 0xdu};
    pol::bit_ptr pe{sto.a, 0xeu};
    pol::bit_ptr pf{sto.a, 0xfu};
    p1 = true; p8 = true; pa = true;
    std::cout << sto.b << '\n';
}
