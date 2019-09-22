#define _GLIBCXX_DEBUG 1
#include <iostream>
#define private public
#define protected public
#include <pol/bit>

void debug_chunk(pol::bit_resource<uint32_t>::_Chunk& c)
{
    std::cout << "debug chunk, size = " << c._M_size << std::endl;
    for (auto* it = c.begin(); it != c.end(); ++it)
    {
        std::cout << it->_M_data << ' ' << it->_M_count << '\n';
    }
    std::cout << std::endl;
}

int main()
{
    pol::bit_resource<uint32_t> res;
    pol::bitmem_ptr x = res.allocate(1);
    std::cout << x._M_ptr << '\n';
    debug_chunk(res._M_chunk.front());
}
