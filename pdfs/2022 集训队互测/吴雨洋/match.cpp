#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<map>
#include<set>
#include<queue>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
const int MAXN=2005;
const int MOD=998244353,i2=(MOD+1)/2;
inline void ADD(int& x,int y){x+=y;if(x>=MOD)x-=MOD;}
inline void DEC(int& x,int y){x-=y;if(x<0)x+=MOD;}
inline int add(int x,int y){return x+y<MOD?x+y:x+y-MOD;}
inline int dec(int x,int y){return x<y?x-y+MOD:x-y;}
ll q_pow(ll a,ll b,ll p=MOD){
	ll ret=1;
	for(;b;a=a*a%p,b>>=1)if(b&1)ret=ret*a%p;
	return ret;
}
ll q_inv(ll x,ll p=MOD){return q_pow(x,p-2,p);}
int fac[MAXN],ifac[MAXN],pw[MAXN],ipw[MAXN];
void build(int n){
	fac[0]=1;for(int i=1;i<=n;++i)fac[i]=1ll*fac[i-1]*i%MOD;
	ifac[n]=q_inv(fac[n]);for(int i=n-1;i>=0;--i)ifac[i]=1ll*ifac[i+1]*(i+1)%MOD;
	pw[0]=1;for(int i=1;i<=n;++i)pw[i]=pw[i-1]*2%MOD;
	ipw[0]=1;for(int i=1;i<=n;++i)ipw[i]=1ull*ipw[i-1]*i2%MOD;
}

int T,N,a[MAXN],ans1=1,ans2=1,ans;vector<int> V[MAXN];
const int MX=32;
struct bit{
	ull a[MX];
	bit(){for(int i=0;i<MX;++i)a[i]=0;}
	void clear(){for(int i=0;i<MX;++i)a[i]=0;}
	bool operator[](int i){return a[i/64]&(1ull<<(i%64));}
	void flip(int i){a[i/64]^=1ull<<(i%64);}
	void operator^=(const bit& B){for(int i=0;i<MX;++i)a[i]^=B.a[i];}
}G[MAXN];
bool vis[MAXN];
void Set(const vector<int>& v,bool t){
	static bit tmp1,tmp2;
	if(G[v[0]][v[0]]){
		if(t)ans2=MOD-ans2;
		for(int i=1;i<v.size();++i)G[v[i]].flip(v[i]);
	}
	vis[v[0]]=1;
	tmp1.clear();
	for(int i=1;i<v.size();++i)tmp1.flip(v[i]);
	for(int i=0;i<N;++i)if(!vis[i]&&G[v[0]][i]){
		if(t)G[i].flip(i);
		G[i]^=tmp1;
	}
	tmp2.clear();for(int i=0;i<N;++i)if(!vis[i]&&G[v[0]][i])tmp2.flip(i);
	for(int i=1;i<v.size();++i)G[v[i]]^=tmp2;
	for(int i=0;i<N;++i)if(tmp1[i]&&tmp2[i])G[i].flip(i);
}

vector<int> vec;
int main(){
	freopen("match.in","r",stdin);
	freopen("match.out","w",stdout);
	build(2000);
	scanf("%d",&T);
	while(T--){
		scanf("%d",&N);
		for(int i=0;i<N;++i)scanf("%d",&a[i]),V[a[i]].push_back(i);
		ans1=ans2=1;
		for(int i=1;i<=N;++i){
			int qwq=0;
			for(int j=0;j<=V[i].size()/2;++j)ADD(qwq,1ull*ifac[j]*ifac[V[i].size()-2*j]%MOD*ipw[j]%MOD);
			qwq=1ull*qwq*fac[V[i].size()]%MOD;
			ans1=1ull*ans1*qwq%MOD;
		}
		for(int i=0;i<N;++i)for(int j=i+1;j<N;++j)if(a[i]>a[j])G[i].flip(j),G[j].flip(i);
		for(int i=1;i<=N;++i)if(V[i].size()){
			Set(V[i],0);
		}
		for(int i=0;i<N;++i)if(!vis[i]){
			vec.clear();
			ans2=ans2*2%MOD,vis[i]=1;
			for(int j=0;j<N;++j)if(!vis[j]&&G[i][j])vec.push_back(j);
			if(!vec.size()){
				if(G[i][i]){ans2=0;break;}
				else continue;
			}else{
				Set(vec,G[i][i]);
			}
		}
		ans=1ull*i2*add(ans1,ans2)%MOD;
		printf("%d\n",ans);
		for(int i=1;i<=N;++i)V[i].clear();
		for(int i=0;i<N;++i)G[i].clear(),vis[i]=0;
	}
	return 0;
}