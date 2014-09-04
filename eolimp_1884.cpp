// http://www.e-olimp.com.ua/en/problems/1884

#include <cstdio>
#include <string>
#include <algorithm>
#include <cmath>
#include <vector>
#include <memory.h>
#include <set>
#include <queue>
#include <map>
#include <stack>

using namespace std;

struct Node{
	int x;
	int cnt;
	Node *left, *right;
	Node(){cnt = 0;};
	Node(int y) : x(y) , left(NULL), right(NULL), cnt(0) {};
	Node(Node * x, Node *y) {
		left = x;
		right = y;
		cnt  = 0;
		if (left)
			left->cnt++;
		if (right)
			right->cnt++;
	};
};

typedef Node * pNode;

const int maxn = 100005;
const int maxm = 100005;

int a[maxn];

int n;
int cur_version = 0;

pNode version[maxm];

pNode build(int l, int r)
{
	pNode t = new Node();
	if (l == r)
	{
		t->x = a[l];
		t->left = t->right = NULL;
		t->cnt = 0;
		return t;
	}
	int m = (l + r) >> 1;
	t->left = build(l, m);
	if (t->left)
		t->left->cnt++;
	t->right = build(m+1, r);
	if (t->right)
		t->right->cnt++;
	return t;
}

void del(pNode &t)
{
	if (!t)
		return;
	t->cnt--;
	if (!t->cnt)
	{
		del(t->left);
		del(t->right);
		delete t;
	}
}

int Get(const pNode t, int l, int r, int v)
{
	if (l == r)
	{
		return t->x;
	}
	int m = (l + r) >> 1;
	if (v <= m)
	{
		return Get(t->left, l, m, v);
	} else
	{
		return Get(t->right, m+1, r, v);
	}
}

pNode Set(pNode &t, int l, int r, int v, int val)
{
	if (l == r)
	{
		return new Node(val);
	}
	int m = (l + r) >> 1;
	if (v <= m)
	{
		return new Node(Set(t->left, l, m, v, val), t->right);
	} else
	{
		return new Node(t->left, Set(t->right, m+1, r, v, val));
	}
}

int get(const pNode t, int v)
{
	return Get(t,0,n-1,v);
}

pNode set_(pNode t, int v, int val)
{
	return Set(t, 0, n-1, v, val);
}

int getParent(int v, int cur)
{
	pNode curNode = version[cur], tmp;
	int parent = get(curNode, v);
	if (parent != v)
	{
		int tmp_parent = getParent(parent,cur);
		if (tmp_parent != parent)
		{
			curNode = version[cur];
			tmp = set_(curNode, v, tmp_parent);
			tmp->cnt++;
			version[cur] = tmp;
			del(curNode);
		}
		return tmp_parent;
	}
	return parent;
}

void Union(int v, int u, int cur, int next)
{
	if (v == u)
	{
		version[next] = version[cur];
		return ;
	}
	v = getParent(v,cur);
	u = getParent(u,cur);
	if (v == u)
	{
		version[next] = version[cur];
		return ;
	}
	version[next] = set_(version[cur], u, v);
	version[next]->cnt++;
}

void revert(int x)
{
	cur_version = max(cur_version - x, 0);
}

int main(void)
{
	scanf("%d",&n);
	int q;
	scanf("%d",&q);
	for (int i = 0; i < n; i++)
		a[i] = i;
	version[cur_version] = build(0,n-1);
	version[cur_version]->cnt++;
	int id = 1;
	for (int i = 1; i <= q; i++)
	{
		int t;
		char c;
		scanf("%c",&c);
		scanf("%c",&c);
		if (c == '+')
		{
			int x,y,z;
			scanf("%d%d%d",&z, &x,&y);
			x--,y--;
			Union(x,y,z,i);
		}
		if (c == '?')
		{
			int x,y,z;
			scanf("%d%d%d",&z, &x,&y);
			x--,y--;
			if ((x == y) || (getParent(x,z) == getParent(y,z)))
			{
				printf("YES\n"); 
			} else
			{
				printf("NO\n");
			}
		}
	}
	return 0;
}
