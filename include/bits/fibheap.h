#ifndef _POL_FIBHEAP_H
#define _POL_FIBHEAP_H 1

namespace polaris
{

template<typename _Tp>
class fib_heap_node
{
public:
    typedef _Tp key_type;
    typedef _Tp value_type;
    typedef fib_heap_node<_Tp> node_type;

private:
    key_type _M_key;
    node_type* _M_parent;
//    std::list<node_type*>* _M_child;
    node_type* _M_child;
    node_type* _M_prev;
    node_type* _M_next;
    unsigned _M_degree : 31;
    bool _M_mark : 1;

public:
    fib_heap_node();
    fib_heap_node(key_type&& __key);
    ~fib_heap_node() noexcept;

    void insert(node_type* __node);
    void insert(key_type&& __key);
    template<typename _FIter>
    void insert(_FIter __first, _FIter __last);

private:
    void _M_construct();
    void _M_destroy() noexcept;
};

template<typename _Tp>
class fib_heap
{
public:
    typedef _Tp value_type;
    typedef fib_heap_node<_Tp> node_type;

private:
    unsigned _M_number;
    unsigned _M_degree;
    node_type* _M_root;
    node_type** _M_degmem;

public:
    fib_heap();
    ~fib_heap() noexcept;

    void insert(node_type* __node);
};

}

#endif
