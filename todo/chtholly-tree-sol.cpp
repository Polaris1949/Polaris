#include <cstdio>
#include <algorithm>
#include <map>
#include <vector>

using namespace std;

typedef long long int64;

struct IO_Tp
{
	bool is_digit(const char ch)
	{
		return '0' <= ch && ch <= '9';
	}

	IO_Tp& operator>>(int& res)
	{
		res = 0;
		static char ch;
		while (ch = getchar(), !is_digit(ch))
			;
		do
			(res *= 10) += ch & 15;
		while (ch = getchar(), is_digit(ch));
		return *this;
	}

	IO_Tp& operator>>(int64& res)
	{
		res = 0;
		static char ch;
		while (ch = getchar(), !is_digit(ch))
			;
		do
			(res *= 10) += ch & 15;
		while (ch = getchar(), is_digit(ch));
		return *this;
	}
} IO;

int64 Power(int64 Base, int64 Exp, int64 Mod)
{
	Base %= Mod;
	int64 res(1);
	do
	{
		if (Exp & 1)
			(res *= Base) %= Mod;
		(Base *= Base) %= Mod;
	}
	while (Exp >>= 1);
	return res;
}

int64 seed;
int rnd()
{
	int res(seed);
	seed = (seed * 7 + 13) % 1000000007;
	return res;
}

int N, M, V_Max;
map<int, int64> A;

int main()
{
	IO >> N >> M >> seed >> V_Max;

	for (int i(1); i <= N; ++i)
		A.insert(A.end(), make_pair(i, rnd() % V_Max + 1));
	A.insert(A.end(), make_pair(N + 1, 0));
	while (M--)
	{
		int op((rnd() % 4) + 1);
		int l((rnd() % N) + 1);
		int r((rnd() % N) + 1);
		int x, y;
		if (l > r)
			swap(l, r);
		if (op == 3)
			x = (rnd() % (r - l + 1)) + 1;
		else
			x = (rnd() % V_Max) + 1;
		if (op == 4)
			y = (rnd() % V_Max) + 1;

		auto it_l(--A.upper_bound(l));
		if (it_l->first != l)
			A[l] = it_l->second, ++it_l;
		auto it_r(--A.upper_bound(r + 1));
		if (it_r->first != r + 1)
			A[r + 1] = it_r->second, ++it_r;
		switch (op)
		{
			static vector<pair<int64, int>> v;
			static int64 res;

			case 1:
				while (it_l != it_r)
					(--it_r)->second += x;
				break;

			case 2:
				while (it_l != it_r)
					A.erase(it_l++);
				A[l] = x;
				break;

			case 3:
				v.clear();
				for (int ub; it_l != it_r; )
					ub = (it_r--)->first, v.push_back(make_pair(it_r->second, ub - it_r->first));
				sort(v.begin(), v.end());
				for (int i(0), cnt(0); ; ++i)
                {
                    cnt += v[i].second;
                    printf(">> %d %d ", i, x-cnt);
					if (x <= cnt)
					{
						printf("%lld\n", v[i].first);
						break;
					}
                    printf("\n");
                }
				break;

			case 4:
				res = 0;
				for (int ub; it_l != it_r; )
					ub = (it_r--)->first, (res += Power(it_r->second, x, y) * (ub - it_r->first)) %= y;
				printf("%lld\n", res);
				break;
		}
	}

	return 0;
}
