#include <polaris/type_traits>

void fun();

struct a {};

struct b : public a
{
	bool operator==(const a&)const;
};

struct c : public a
{
	bool operator() () const;
};

struct d : public b, c
{
	bool operator!() const;
};

template<typename>
class foo {};

int main()
{
	static_assert(pol::is_functor_v<c>);
	static_assert(!pol::is_functor_v<decltype(fun)>);
	static_assert(pol::is_equality_comparable_v<decltype(fun)>);
	static_assert(pol::is_equality_comparable_with_v<b, a>);
	static_assert(pol::ho_logical_not_v<d>);
	foo<int> x;
	pol::rebind_t<decltype(x), long long> y;
	static_assert(std::is_same_v<decltype(y), foo<long long>>);
}
