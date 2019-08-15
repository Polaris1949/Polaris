#include <polaris/memory>
#include <iostream>

union
{
    unsigned char a[2];
    unsigned short b;
} sto;

int main()
{
    pol::bit_ref p0{{sto.a, 0x0u}};
    pol::bit_ref p1{{sto.a, 0x1u}};
    pol::bit_ref p2{{sto.a, 0x2u}};
    pol::bit_ref p3{{sto.a, 0x3u}};
    pol::bit_ref p4{{sto.a, 0x4u}};
    pol::bit_ref p5{{sto.a, 0x5u}};
    pol::bit_ref p6{{sto.a, 0x6u}};
    pol::bit_ref p7{{sto.a, 0x7u}};
    pol::bit_ref p8{{sto.a, 0x8u}};
    pol::bit_ref p9{{sto.a, 0x9u}};
    pol::bit_ref pa{{sto.a, 0xau}};
    pol::bit_ref pb{{sto.a, 0xbu}};
    pol::bit_ref pc{{sto.a, 0xcu}};
    pol::bit_ref pd{{sto.a, 0xdu}};
    pol::bit_ref pe{{sto.a, 0xeu}};
    pol::bit_ref pf{{sto.a, 0xfu}};
    p1 = true; p8 = true; pa = true;
    p0 = p1;
    std::cout << sto.b << '\n';
}
