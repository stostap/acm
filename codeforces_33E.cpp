// http://codeforces.com/contest/33/problem/E

#include <cstdio>
#include <string>
#include <vector>
#include <algorithm>
#include <memory.h>
#include <cmath>
#include <set>
#include <stack>
#include <map>

using namespace std;

const int MAXN = 105;
const int MAXT = 45000;

int m,n,k;
vector<string> list;
vector<int> t;
vector<int> sb,fb;
vector<int> freeMinutes;
vector<student> task;
vector<result> res;

int dp[MAXN][MAXT];
int par[MAXN][MAXT];

struct student
{
	int id;
	string name;
	int t;
	int t_used;
	int price;
	int deadline;
	student (){};
	student (int id, string name, int t, int price, int t_used) : id(id), name(name), t(t), price(price), deadline(-1), t_used(t_used) {};

	bool operator< (const student a) const
	{
		if (deadline < a.deadline)
			return 1;
		if ((deadline == a.deadline) && (id < a.id))
			return 1;
		return 0;
	}

};

struct result
{
	int ts, tf;
	int id;
	result(){};
	result(int ts, int tf, int id) : ts(ts), tf(tf), id(id) {};
};

bool isFree(int minute)
{
	minute %= (24 * 60);
	for (int i = 0; i < 4; i++)
		if ((sb[i] <= minute) && (minute <= fb[i]))
			return 0;
	return 1;
}

void Print(int t)
{
	t = freeMinutes[t];
	int d = t / (24 * 60) + 1;
	int h = (t % (24 * 60)) / 60;
	int m = (t % (24 * 60)) % 60;
	printf(" %d %02d:%02d", d, h, m);
}

int main(void)
{
	scanf("%d%d%d",&m,&n,&k);
	for (int i = 0; i < m; i++)
	{

		char s[40];
		scanf("%s",&s);
		list.push_back((string)s);
	}
	for (int i = 0; i < m; i++)
	{
		int x;
		scanf("%d",&x);
		t.push_back(x);
	}
	for (int i = 0; i < 4; i++)
	{
		int h1,h2,m1,m2;
		scanf("%d:%d-%d:%d", &h1, &m1, &h2, &m2);
		sb.push_back(h1 * 60 + m1);
		fb.push_back(h2 * 60 + m2);
	}
	for (int i = 0; i < n; i++)
	{
		char s[40];
		int d, h, mi, c;
		scanf("%s %d %d:%d %d", &s, &d, &h, &mi, &c);
		string name = (string) s;
		for (int j = 0; j < m; j++)
			if (list[j] == name)
			{
				task.push_back(student(i + 1, name, (d - 1) * 24 * 60 + 60 * h + mi, c, t[j]));
				break;
			}
	}
	int next = 0;
	for (int i = 0; i < k * 24 * 60; i++)
	{
		if (isFree(i))
			freeMinutes.push_back(i);
	}
	for (int i = 0; i < task.size(); i++)
	{
		int pos = lower_bound(freeMinutes.begin(), freeMinutes.end(), task[i].t) - freeMinutes.begin();
		pos--;
		if (pos >= 0)
			task[i].deadline = freeMinutes[pos];
	}
	sort(task.begin(), task.end());
	memset(dp,-1,sizeof(dp));
	memset(par, -1, sizeof(par));
	for (int i = 0; i < freeMinutes.size(); i++)
		dp[0][i] = 0;
	for (int i = 0; i < task.size(); i++)
	{
		for (int j = 0; j < freeMinutes.size(); j++)
		{
			if (dp[i][j] > dp[i+1][j])
			{
				dp[i+1][j] = dp[i][j];
				par[i+1][j] = j;
			}
			if (j + task[i].t_used - 1 < freeMinutes.size())
			if (freeMinutes[j + task[i].t_used - 1] <= task[i].deadline)
			{
				if (dp[i][j] + task[i].price > dp[i+1][j+task[i].t_used])
				{
					dp[i+1][j+task[i].t_used] = dp[i][j] + task[i].price;
					par[i+1][j+task[i].t_used] = j;
				}
			}
		}
	}
	int fin_time = -1;
	int sum = 0;
	for (int i = 0; i < k * 24 * 60; i++)
	{
		if (dp[task.size()][i] > sum)
		{
			sum = dp[task.size()][i];
			fin_time = i;
		}
	}
	if (fin_time == -1)
	{
		printf("0\n0\n");
		return 0;
	}
	int cur = task.size();
	while (cur > 0)
	{
		if (par[cur][fin_time] != fin_time)
		{
			res.push_back(result(par[cur][fin_time], fin_time-1, task[cur-1].id));
			fin_time = par[cur][fin_time];
		}
		cur--;
	}
	printf("%d\n", sum);
	printf("%d\n", res.size());
	for (int i = (int)res.size() - 1; i >= 0; i--)
	{
		printf("%d", res[i].id);
		Print(res[i].ts);
		Print(res[i].tf);
		printf("\n");
	}
	return 0;
}
