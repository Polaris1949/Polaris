#include <polext/expr_tree.h>
#include <iostream>
using namespace std;
using namespace polext;

int main()
{
	expression_tree_node x;
	operator_handler o;
	cout<<x.is_operator(&o)<<endl;
	return 0;
}
