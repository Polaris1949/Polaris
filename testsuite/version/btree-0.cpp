#include <iostream>

struct foo
{
    static int cnt;
    int id;
    foo() : id{++cnt} { std::cout << "foo::foo() [" << id << "]\n"; }
    foo(const foo& x) : id(x.id)
    { std::cout << "foo::foo(const foo&) [" << id << "]\n"; }
    ~foo() noexcept { std::cout << "foo::~foo() [" << id << "]\n"; }
};

int foo::cnt{};

struct bar
{
    foo x;
    bar() { std::cout << "bar::bar()\n"; }
    ~bar() noexcept { std::cout << "bar::~bar()\n"; }

    bar& construct(const foo& y)
    {
        std::cout << "bar::construct()\n";
        new (&x) foo{y};
        return *this;
    }

    bar& destroy()
    {
        std::cout << "bar::destroy()\n";
        x.~foo(); return *this;
    }
};

int main()
{
    bar a;
    a.construct(foo{});
    // a.destroy();
}
