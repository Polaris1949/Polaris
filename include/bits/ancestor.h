#ifndef _POL_ANCESTOR_H
#define _POL_ANCESTOR_H 1

namespace polaris
{

template<typename _Tp>
class ancestor
{
public:
	typedef _Tp value_type;
	
private:
	binary_tree<_Tp>* _M_tree;
	std::unordered_map<_Tp*, _Tp*> _M_anc;
	
public:
	ancestor();
	
	ancestor(binary_tree<value_type>* __t);
};

}

#endif
