// http://codeforces.com/contest/268/problem/C

#include <cstdio>
#include <algorithm>
#include <cmath>
#include <vector>
#include <memory.h>
#include <string>
#include <set>
#include <stack>
#include <map>
#include <queue>

using namespace std;

bool used[105];
int n,m;
vector<pair<int,int> > ans;

int sqr(int a)
{
	return a*a;
}

bool good(pair<int,int> a, pair<int,int> b)
{
	int tmp = sqr(a.first - b.first) + sqr(a.second - b.second);
	int sqrr = (int) sqrt(1.0 * tmp);
	if ((sqrr * sqrr) == tmp)
		return 0;
	return 1;
}

void dfs(int v)
{
	if (v == n+1)
	{
		printf("%d\n", ans.size());
		for (int i = 0; i < ans.size(); i++)
			printf("%d %d\n", ans[i].first, ans[i].second);
		exit(0);
	}
	for (int i = 0; i <=m; i++)
	{
		if ((v + i) && !used[i])
		{
			bool ok = 1;
			for (int j = 0; j < ans.size(); j++)
				if (!good(ans[j], make_pair(v,i)))
				{
					ok = 0;
					break;
				}
			if (!ok)
				continue;
			ans.push_back(make_pair(v,i));
			used[i] = 1;
			dfs(v+1);
			used[i] = 0;
			ans.pop_back();
		}
	}
}

int main(void)
{
	memset(used,0,sizeof(used));
	scanf("%d%d",&n,&m);
	if (n > m)
		swap(n,m);
	dfs(0);
	for (int i = 0; i < ans.size(); i++)
		for (int j = i + 1; j < ans.size(); j++)
			if (!good(ans[i],ans[j]))
			{
				printf("Fail on %d %d\n", i, j);
			}
	return 0;
}
