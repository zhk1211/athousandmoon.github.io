#include<bits/stdc++.h>
#include"tree.h"
#ifdef huhao
#include"grader.cpp"
#endif
#define fr(i,a,b) for(int i=(a),end_##i=(b);i<=end_##i;i++)
#define fd(i,a,b) for(int i=(a),end_##i=(b);i>=end_##i;i--)
const int N=1010;
std::vector<int> e[N];
int vis[N];
int s[N],t;
int f[N];
int n;
std::vector<int> operator+(std::vector<int> a,int b){ a.push_back(b); return a; }
int a[N],m;
void find(int u)
{
	m=0;
	fr(i,1,n) if(!vis[i]&&i!=u) a[++m]=i;
	if(!m||query(std::vector<int>(a+1,a+m+1))!=query(std::vector<int>(a+1,a+m+1)+u))
	{
		s[++t]=u; vis[u]=1; return ;
	}
	int l=1,r=m;
	while(l<r)
	{
		int mid=(l+r)>>1;
		if((query(std::vector<int>(a+l,a+mid+1))==query(std::vector<int>(a+l,a+mid+1)+u))) r=mid;
		else l=mid+1;
	}
	find(a[l]); find(u);
}
void dfs(int u)
{
	for(auto i:e[u]) dfs(i);
	a[++m]=u;
}
std::vector<int> solve(int _n)
{
	n=_n;
	int x=0,y=0;
	fr(i,2,n) if(!vis[i]&&query({i})==0)
	{
		t=0; find(i); std::reverse(s+1,s+t+1);
		fr(i,1,t-1){ f[s[i]]=s[i+1]; e[s[i+1]].push_back(s[i]); }
		if(s[t]!=1)
		{
			m=0; dfs(1);
			int l=1,r=m;
			while(l<r)
			{
				int mid=(l+r)>>1;
				if((query(std::vector<int>(a+1,a+mid+1))==query(std::vector<int>(a+1,a+mid+1)+s[t]))) r=mid;
				else l=mid+1;
			}
			f[s[t]]=a[l]; e[a[l]].push_back(s[t]);
		}
		if(!x) x=i; else y=i;
	}
	if(x&&y) std::swap(f[x],f[y]);
	std::vector<int> _f;
	fr(i,2,n) _f.push_back(f[i]);
	return _f;
}