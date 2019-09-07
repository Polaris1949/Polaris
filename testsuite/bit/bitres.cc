#define private public
#define protected public
#include <polaris/bit>
#include <iostream>

int main()
{
    pol::bit_resource<uint32_t>* res = pol::global_bit_resource();
    pol::bit_ptr x = res->allocate(1);
    std::cout << x._M_adr << '\n';
    std::cout << res->_M_chunk.front()._M_count << '\n';
}
