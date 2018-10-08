#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include <polaris/partition>
#include <cmath>

using llong = long long;

struct fsum_t
{
	llong operator() (llong x, llong y) const
	{
		return x + y;
	}
};

llong n, m;
pol::partition<llong, fsum_t> p;

int main()
{
    llong i, x, y, k, f;
    cin >> n >> m;

    {
        std::vector<llong> v;
        v.resize(n);

        for (i=0; i<n; ++i)
            cin >> v[i];

        p.data() = v;
        p.bucket_resize(sqrt(n)+1);
    }

    for (i=0; i<m; ++i)
    {
        cin >> f;

        if (f==1)
        {
            cin >> x >> y >> k;
            p.modify(--x, y, k);
        }
        else
        {
            cin >> x >> y;
            cout << p.find(--x, y) << endl;
        }
    }

    return 0;
}
