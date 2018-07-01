#include <cstdlib>
#include <ctime>
#include <vector>
#include <iostream>
#include <string>
#include <polaris/utility>

int main()
{
	srand((unsigned)time(nullptr));
	unsigned prob=50;
	std::cout<<(std::string("Prob:")+std::to_string(prob)\
		+'%').c_str()<<std::endl;
	size_t cnt=0;
	for (size_t i=0;i<10;++i)
	{
		
		bool f=pol::prob_choice(prob);
		std::cout<<f<<std::endl;
		if (f) ++cnt;
	}
	std::cout<<"Sum:"<<cnt<<std::endl;
	return 0;
}
