#include <iostream>
#include <polaris/ufset>

pol::tree_ufset<std::size_t, std::size_t> u;

using cont_t = std::map<std::size_t, pol::ufset_iter_node<
	std::size_t, std::size_t>>;

using iter_t = cont_t::iterator;

uintptr_t itou(iter_t i)
{
    return *reinterpret_cast<uintptr_t*>(std::addressof(i));
}

iter_t utoi(uintptr_t u)
{
    return *reinterpret_cast<iter_t*>(std::addressof(u));
}

void check()
{
	auto& d = *(cont_t*)u.data();

	for (auto& e : d)
	{
		std::cerr << "# " << e.first << " <=> {"
			<< utoi(e.second.parent())->first << ", "
			<< e.second.rank() << "}\n";
	}
}

int main()
{
	std::size_t n, m, o, x, y, i;
	std::cin >> n >> m;

	for (i = 0; i < n; ++i)
		u.insert(i);

	check();

	for (i = 0; i < m; ++i)
	{
		std::cin >> o >> x >> y;
		--x; --y;
		if (o == 1) u.merge(x, y);
		else std::cout << (u.is_sibling(x, y) ? 'Y' : 'N') << '\n';
		check();
	}

	return 0;
}
