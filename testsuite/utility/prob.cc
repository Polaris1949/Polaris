#include <cstdlib>
#include <ctime>
#include <iostream>
#include <polaris/utility>

int main()
{
	srand((unsigned)time(nullptr));
	unsigned prob, n, cnt{};
	bool pt;
	std::cout << "Enter an amount: ";
	std::cin >> n;
	std::cout << "Enter a probability (%): ";
	std::cin >> prob;
	std::cout << "Print test? (0/1): ";
	std::cin >> pt;

	for (unsigned i{}; i<n; ++i)
	{
		bool f{pol::prob_choice(prob)};
		if (pt) std::cout << "Test " << i << ": " << (f ? 'Y' : 'N') << '\n';
		if (f) ++cnt;
	}

	std::cout << "------------Report------------\n";
	std::cout << "Amount: " << n << '\n';
	std::cout << "Probability: " << prob << "%\n";
	std::cout << "Sum: " << cnt << '\n';
	std::cout << "Frequency: " << (double(cnt)/n*100) <<"%\n";
}
