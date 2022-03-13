#include<ctime>
#include<vector>
#include<random>
#include"integer.h"
int p[1<<20],minv=0;
int vis[1<<20];
std::mt19937_64 rng(time(0));
int stk[1<<20],top;
unsigned random(unsigned x,unsigned y)
{
	unsigned long long ret=rng();
	return ret%(y-x+1)+x;
}
std::vector<int>findPermutation(int n)
{
	std::vector<int>ret(n,-1);
	register int i;
	for(i=0;i<n;i++)p[i]=i;
	for(i=1;i<n;i++)
	{
		int x=random(0,i);
		int t=p[i];p[i]=p[x],p[x]=t;
	}
	for(i=0;i<n;i++)operate(i);
	int cp=n,ct=0;
	while(1)
	{
		ct++;
		//fprintf(stderr,"-> %d\n",ct);
		int cur=-1;
		for(i=0;i<n;i++)
		{
			int it=__builtin_popcount(ct),is=__builtin_popcount(ct-1);
			if(ret[p[i]]==-1)
			{
				int d=operate(p[i]);
				if(d==cp+1)
				{
					cp++;
					continue;
				}
				if(cur==-1)
				{
					cur=n-(cp-d)-(it-is);
					//fprintf(stderr,"ans[%d]=%d (cp=%d,d=%d)\n",p[i],cur,cp,d);
					ret[p[i]]=cur,vis[cur]=1;
				}
				else
				{
					cur=cur-(cp-d)-1;
					//fprintf(stderr,"ans[%d]=%d (cp=%d,d=%d)\n",p[i],cur,cp,d);
					ret[p[i]]=cur,vis[cur]=1;
				}
				cp=d;
			}
			else stk[++top]=p[i];
		}
		if(top==n)break;
		while(vis[minv])minv++;
		for(;top;top--)
			if(ret[stk[top]]>=minv)cp=operate(stk[top]);
	}
	return ret;
}