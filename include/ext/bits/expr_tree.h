#ifndef _POLEXT_EXPR_TREE_H
#define _POLEXT_EXPR_TREE_H 1

#include <string>
#include <vector>

namespace polext
{

class operator_handler
{
public:
	typedef std::string string_type;
	
private:
	string_type _M_op;
};

class object_handler
{
public:
	typedef std::string string_type;
	
private:
	string_type _M_type;
	string_type _M_value;
};

class invoke_handler
{
public:
	typedef std::string string_type;
	
private:
	string_type _M_func;
	std::vector<object_handler> _M_arg;
};

class expression_tree_node
{
public:
	typedef std::string string_type;
	
public:
	bool is_operator(void* __data)
	{
		if (_M_flag == 0)
		{
			return ((operator_handler*&)__data = (operator_handler*)_M_data);
		}
		
		return false;
	}
	
private:
	expression_tree_node* _M_left;
	expression_tree_node* _M_right;
	
	unsigned char _M_flag = 0;
	void* _M_data;
};

class expression_tree
{
};

}

#endif
