#include <polaris/memory>
#include <iostream>

union
{
    unsigned char a[2];
    unsigned short b;
} sto;

int main()
{
    pol::bit_ptr p0{sto.a, 0x0};
    pol::bit_ptr p1{sto.a, 0x1};
    pol::bit_ptr p2{sto.a, 0x2};
    pol::bit_ptr p3{sto.a, 0x3};
    pol::bit_ptr p4{sto.a, 0x4};
    pol::bit_ptr p5{sto.a, 0x5};
    pol::bit_ptr p6{sto.a, 0x6};
    pol::bit_ptr p7{sto.a, 0x7};
    pol::bit_ptr p8{sto.a, 0x8};
    pol::bit_ptr p9{sto.a, 0x9};
    pol::bit_ptr pa{sto.a, 0xa};
    pol::bit_ptr pb{sto.a, 0xb};
    pol::bit_ptr pc{sto.a, 0xc};
    pol::bit_ptr pd{sto.a, 0xd};
    pol::bit_ptr pe{sto.a, 0xe};
    pol::bit_ptr pf{sto.a, 0xf};
    p1 = true; p8 = true; pa = true;
    std::cout << sto.b << '\n';
}
