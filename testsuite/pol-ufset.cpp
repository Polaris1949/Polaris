#include <iostream>
#include <polaris/ufset>

pol::ufset u;

int main()
{
	std::size_t n, m, o, x, y;
	std::cin >> n >> m;
	u.init(n);

	for (std::size_t i{}; i < m; ++i)
	{
		std::cin >> o >> x >> y;
		--x; --y;
		if (o == 1) u.merge(x, y);
		else std::cout << (u.is_brother(x, y) ? 'Y' : 'N') << '\n';
	}

	return 0;
}
