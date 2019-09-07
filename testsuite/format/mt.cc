#include <pol/format>
#include <iostream>
#include <thread>
#include <mutex>

std::mutex mout;
std::string s[100][100];

void fun(int n)
{
	for (int i = 0; i < 100; ++i)
	{
		{
			std::lock_guard<std::mutex> lock{mout};
			s[n][i] = pol::format("{}", i);
			std::cout << pol::format("!{} #{}", n, i) << '\n';
		}
	}
}

int main()
{
	std::thread t[100];
	for (int i=0; i<100; ++i)
	{
		t[i]=std::move(std::thread{fun, i});
	}
	for (int i=0; i<100; ++i)
	{
		t[i].join();
	}
	for (int n = 0; n < 100; ++n)
	{
		for (int i = 0; i < 100; ++i)
		{
			if (std::stoi(s[n][i])!=i)
			{
				std::cout << pol::format("!{} #{} bad = {}", n, i, s[n][i]) << '\n';
			}
		}
	}
}