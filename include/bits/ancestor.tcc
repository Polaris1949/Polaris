#ifndef _POL_ANCESTOR_TCC
#define _POL_ANCESTOR_TCC 1

namespace polaris
{

template<typename _Tp>
ancestor<_Tp>::
ancestor()
	: _M_tree(nullptr), _M_anc()
{
}

template<typename _Tp>
ancestor<_Tp>::
ancestor(binary_tree<value_type>* __t)
	: _M_tree(__t), _M_anc()
{
}

}

#endif
