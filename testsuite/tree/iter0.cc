#include <iostream>
#define private public
#define protected public
#include <pol/tree>

using base = pol::tree_node_base;
using node = pol::tree_node<char>;
using iter = pol::tree_base_iterator;

int main()
{
    node* na = new node('a');
    node* nb = new node('b');
    node* nc = new node('c');
    node* nd = new node('d');
    node* ne = new node('e');
    node* nf = new node('f');
    node* ng = new node('g');
    base* a = na;
    base* b = nb;
    base* c = nc;
    base* d = nd;
    base* e = ne;
    base* f = nf;
    base* g = ng;
    a->push_back(b);
    a->push_back(c);
    a->push_back(d);
    b->push_back(e);
    b->push_back(f);
    d->push_back(g);
    iter i;
    i._M_root = a;
    i._M_st.push(a);
    std::cerr<<((node*)i._M_st.top())->data()<<'\n';
    ++i;
    std::cerr<<((node*)i._M_st.top())->data()<<'\n';
    ++i;
    std::cerr<<((node*)i._M_st.top())->data()<<'\n';
    ++i;
    std::cerr<<((node*)i._M_st.top())->data()<<'\n';
    ++i;
    std::cerr<<((node*)i._M_st.top())->data()<<'\n';
    ++i;
    std::cerr<<((node*)i._M_st.top())->data()<<'\n';
    ++i;
    std::cerr<<((node*)i._M_st.top())->data()<<'\n';
    ++i;
    --i;
    std::cerr<<((node*)i._M_st.top())->data()<<'\n';
    --i;
    std::cerr<<((node*)i._M_st.top())->data()<<'\n';
    --i;
    std::cerr<<((node*)i._M_st.top())->data()<<'\n';
    --i;
    std::cerr<<((node*)i._M_st.top())->data()<<'\n';
    --i;
    std::cerr<<((node*)i._M_st.top())->data()<<'\n';
    --i;
    std::cerr<<((node*)i._M_st.top())->data()<<'\n';
    --i;
    std::cerr<<((node*)i._M_st.top())->data()<<'\n';
    --i;
    --i;
    std::cerr<<((node*)i._M_st.top())->data()<<'\n';
    delete na;
    delete nb;
    delete nc;
    delete nd;
    delete ne;
    delete nf;
    delete ng;
    return 0;
}