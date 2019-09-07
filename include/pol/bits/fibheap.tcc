#ifndef _POL_FIBHEAP_TCC
#define _POL_FIBHEAP_TCC 1

namespace polaris
{

template<typename _Tp>
fib_heap_node<_Tp>::
fib_heap_node()
    : _M_key{}, _M_parent{}, _M_child{}, _M_prev{}, _M_next{},
        _M_degree{}, _M_mark{}
{ this->_M_construct(); }

template<typename _Tp>
fib_heap_node<_Tp>::
fib_heap_node(key_type&& __key)
    : _M_key{std::move(__key)}, _M_parent{}, _M_child{}, _M_prev{}, _M_next{},
        _M_degree{}, _M_mark{}
{ this->_M_construct(); }

template<typename _Tp>
fib_heap_node<_Tp>::
~fib_heap_node() noexcept
{ this->_M_destroy(); }

template<typename _Tp>
void
fib_heap_node<_Tp>::
insert(node_type* __node)
{
    this->_M_prev = __node->_M_prev;
    __node->_M_prev->_M_next = this;
    this->_M_next = __node;
    __node->_M_prev = this;
}

template<typename _Tp>
void
fib_heap_node<_Tp>::
erase()
{
    this->_M_prev->_M_next = this->_M_next;
    this->_M_next->_M_prev = this->_M_prev;
}

template<typename _Tp>
void
fib_heap_node<_Tp>::
_M_construct()
{
    this->_M_prev = this->_M_next = this;
}

template<typename _Tp>
void
fib_heap_node<_Tp>::
_M_destroy() noexcept
{
    node_type* __cur = this->_M_child->_M_next;

    while (__cur != this->_M_child)
    {
        node_type* __tmp = __cur;
        __cur = __cur->_M_next;
        delete __tmp;
    }
}

template<typename _Tp>
fib_heap<_Tp>::
fib_heap()
    : _M_number{}, _M_degree{}, _M_root{}, _M_degmem{}
{}

template<typename _Tp>
fib_heap<_Tp>::
~fib_heap() noexcept
{ delete this->_M_root; }

template<typename _Tp>
void
fib_heap<_Tp>::
insert(node_type* __node)
{
    if (!this->_M_number)
        this->_M_root = __node;
    else
    {
        __node->insert(this->_M_root);
        __node->_M_parent = nullptr;

        if (__node->_M_key < this->_M_root->_M_key)
            this->_M_root = __node;
    }

    ++this->_M_number;
}

template<typename _Tp>
void
fib_heap<_Tp>::
insert(key_type&& __key)
{
    fib_heap_node* __node = new fib_heap_node{__key};
    this->insert(__node);
}

template<typename _Tp>
template<typename _FIter>
void
fib_heap<_Tp>::
insert(_FIter __first, _FIter __last)
{
    for (; __first != __last; ++__first)
    {

    }
}

}

#endif
