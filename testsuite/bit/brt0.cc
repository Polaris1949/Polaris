#include <iostream>
#include <list>
#define GOOD 1

struct chunk
{
    uint32_t* data;
    size_t size;
    
    chunk(size_t __n)
        : data{new uint32_t[__n / sizeof(uint32_t)]},
            size{__n / sizeof(uint32_t)}
    { }

#if GOOD
    chunk(chunk&& __c)
        : data(__c.data), size(__c.size)
    { __c.data = nullptr; }
#endif

    ~chunk() noexcept
    { if (this->data) delete[] this->data; }
};

int main()
{
    std::list<chunk> l;
    l.push_back(std::move(chunk{4}));
    std::cout << l.front().size << std::endl;
}
