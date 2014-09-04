// http://acm.timus.ru/problem.aspx?space=1&num=1028

#include <cstdio>
#include <vector>
#include <memory.h>
#include <cmath>
#include <string>
#include <algorithm>
using namespace std;

vector<int> t;
int n;
const int MAXN = 32005;
vector<pair<int,int> > v;
int a[MAXN];

void init()
{
	t.assign(MAXN,0);
}

int sum (int r)
{
	int res = 0;
	for (; r >= 0; r = (r & (r +1) )- 1)
		res += t[r];
	return res;
}

void upd(int r, int delta)
{
	for (; r < MAXN; r = (r | (r+1)))
		t[r] += delta;
}

int main(void)
{
	scanf("%d",&n);
	init();
	for (int i = 0 ; i < n; i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		v.push_back(make_pair(x,y));
	}
	sort(v.begin(),v.end());
	for (int i = 0; i < v.size(); i++)
	{
		int tmp = sum(v[i].second);
		a[tmp] ++;
		upd(v[i].second,1);
	}
	for (int i = 0 ;  i< n; i++)
		printf("%d\n",a[i]);
	return 0;
}
