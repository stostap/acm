// http://codeforces.com/contest/356/problem/A

#include <cstdio>
#include <cmath>
#include <vector>
#include <algorithm>
#include <string>
#include <memory.h>
#include <set>
#include <map>

using namespace std;

const int MAXN = 300005;

vector<int> t(4 * MAXN, 0);
vector<pair<pair<int,int>, int> > v;

void push(int v)
{
	if (t[v])
	{
		t[2*v] = t[v];
		t[2*v+1] = t[v];
		t[v] = 0;
	}
}

void upd(int v, int tl, int tr, int l, int r, int val)
{
	if (l > r)
		return ;
	if ((l == tl) && (r == tr))
		t[v] = val;
	else
	{
		push(v);
		int tm = (tl + tr) / 2;
		upd(2 * v, tl, tm, l, min(r, tm), val);
		upd(2 * v + 1, tm + 1, tr, max(l, tm + 1), r, val);
	}
}

int get(int v, int tl, int tr, int pos)
{
	if (tl == tr)
		return t[v]; 
	push(v);
	int tm = (tl + tr) / 2;
	if (pos <= tm)
		return get(2 * v, tl, tm, pos); 
	else
		return get(2 * v + 1, tm + 1, tr, pos);
}

int main(void)
{
	int n,m;
	scanf("%d%d",&n,&m);
	for (int i = 0; i < m; i++)
	{
		int x,y,z;
		scanf("%d%d%d",&x,&y,&z);
		x--,y--,z--;
		v.push_back(make_pair(make_pair(x,y),z));
	}
	for (int i = (int) v.size() - 1; i >=0; i--)
	{
		int x,y,z;
		x = v[i].first.first;
		y = v[i].first.second;
		z = v[i].second;
		if (z == x)
		{
			upd(1, 0, n-1, z+1, y, z+1);
		} else
			if (z == y)
			{
				upd(1,0, n-1, x, z-1, z+1);
			} else
			{
				upd(1,0, n-1, x, z-1, z+1);
				upd(1,0, n-1, z+1, y, z+1);
			}
	}
	printf("%d", get(1,0,n-1,0));
	for (int i = 1; i < n; i++)
		printf(" %d", get(1,0,n-1, i));
	printf("\n");
	return 0;

}
