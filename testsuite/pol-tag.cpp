#include <iostream>
#include <typeinfo>
#include <polaris/tag>

struct int_tag
{
	friend std::ostream& operator << (std::ostream& out, const int_tag&)
	{
		out<<"int_tag";
		return out;
	}
};

int main()
{
	auto x=polaris::make_tvalue<int_tag>(1);
	std::cout<<x.data()<<std::endl;
	std::cout<<typeid(decltype(x)::tag_type<0>).name()<<std::endl;
	std::cout<<x.size()<<std::endl;
	std::cout<<x.tag<0>()<<std::endl;
}
