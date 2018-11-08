#include <polaris/allocator>
#include <iostream>
#include <string>

struct dove
{
    std::string m_name;
    dove() : m_name{"Anonymous"}
    { std::cout << m_name << ": I was born\n"; }
    dove(const std::string& n) : m_name{n}
    { std::cout << m_name << ": I was born\n"; }
    ~dove() { std::cout << m_name << ": I died\n"; }
    void coo() { std::cout << m_name << ": Coo coo\n"; }
    void say(const std::string& m)
    { std::cout << m_name << ": " << m << '\n'; }
};

pol::allocator<void> v;
pol::allocator<dove> d;

int main()
{
    void* p = v.allocate(12);
    v.deallocate(p);
    dove* c = d.construct();
    c->coo();
    c = d.reconstruct(c, "SPFA");
    dove* a = d.construct("Dijkstra");
    a->say("I beat SPFA");
    c->coo();
    d.destroy(c);
    a->say("Haha");
    d.destroy(a);
}
