// http://acm.timus.ru/problem.aspx?space=1&num=1109&locale=en

#include <cstdio>
#include <string>
#include <memory.h>
#include <vector>
#include <queue>
#include <algorithm>
#include <cmath>

using namespace std;

const int MAXN = 1005;
const int MAXVAL = 100000000;
int n,m,k;

int dist[MAXN];
int g1[MAXN], g2[MAXN];

vector<int> g[MAXN];

bool bfs()
{
	vector<int> q;
	int st = 0;
	int sf = 0;
	for (int i = 1; i <= n; i++)
		if (g1[i] == 0)
		{
			q.push_back(i);
			sf++;
			dist[i] = 0;
		}
		else
			dist[i] = MAXVAL;
	dist[0] = 100000000;
	while (st < sf)
	{
		int v = q[st++];
		if (dist[v] < dist[0])
		{
			for (int i = 0; i < g[v].size(); i++)
			{
				if (dist[g2[g[v][i]]] == MAXVAL)
				{
					dist[g2[g[v][i]]] = dist[v] + 1;
					q.push_back(g2[g[v][i]]);
					sf++;
				}
			}
		}
	}
	return dist[0] != MAXVAL;
}

bool dfs(int v)
{
	if (v)
	{
		for (int i = 0; i < g[v].size(); i++)
		{
			if (dist[g2[g[v][i]]] == (dist[v] + 1))
			{
				if (dfs(g2[g[v][i]]))
				{
					g1[v] = g[v][i];
					g2[g[v][i]] = v;
					return true;
				}
			}
		}
		dist[v] = MAXVAL;
		return false;
	}
	return true;
}



int main(void)
{
	for (int i = 0; i < n + 1; i++)
		dist[i] = MAXVAL;
	scanf("%d%d%d", &n, &m, &k);
	for (int i = 0 ; i <k; i++)
	{
		int x,y;
		scanf("%d%d", &x, &y);
		g[x].push_back(y);
	}
	for (int i = 0; i <= n; i++)
		g1[i] = 0;
	for (int i = 0; i <= m; i++)
		g2[i] = 0;
	while (bfs() == true)
	{
		for (int i = 1; i <= n; i++)
			if (g1[i] == 0)
				dfs(i);
	}
	int cnt = 0;
	for (int i = 1; i <= n; i++)
		if (g1[i] != 0)
			cnt++;
		else
			cnt++;
	for (int i = 1; i <= m;i++)
		if (g2[i] == 0)
			cnt++;
	printf("%d\n", cnt);
	return 0;
}
