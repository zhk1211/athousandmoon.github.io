#include <cstdio>
#include <cstring>

const int P=164511353,O=41;
inline int mul(const int &a,const int &b){return 1ll*a*b%P;}
inline int sub(int a,const int &b){a-=b;return (a<0)?a+P:a;}
inline int add(int a,const int &b){a+=b;return(a>=P)?a-P:a;}
int qsm(int a,int b,int p=P){
	int ans=1;
	while(b){
		if(b&1)ans=1ll*a*ans%p;
		a=1ll*a*a%p;
		b>>=1;
	}
	return ans;
}
int n,K,res,m,S[1001][1001];
int k[7],p[7],top;
int cnt[21][O],tem[O],H[1001],tp;
int A[22],Add[22][22],Mul[22][22],f[2097152];
int stk[1001],it;
void upd(int ind,int l){
	int *a=cnt[ind];
	if(tp==1){
		for(int i=1;i<=top;++i){
			int v;
			if(l<0)v=qsm(qsm(p[i],P-2),-l);
			else v=qsm(p[i],l);
			memset(tem,0,sizeof tem);
			for(int j=0;j<O;++j){
				tem[(j*p[i])%O]=add(tem[(j*p[i])%O],a[j]);
				tem[j]=sub(tem[j],mul(a[j],v));
			}
			memcpy(a,tem,sizeof tem);
		}
	}
	else{
		memset(tem,0,sizeof tem);
		for(int j=1;j<=K;++j)
			if(A[j]){
				int v;
				if(l<0)v=qsm(qsm(K/j,P-2),-l);
				else v=qsm(K/j,l);
				v=mul(v,A[j]);
				for(int k=0;k<O;++k)
					tem[(k*j)%O]=add(tem[(k*j)%O],mul(a[k],v));
			}
		memcpy(a,tem,sizeof tem);
	}
}
void solve(int l,int r,int el,int er,int top){
	int nl=-l,nr=n-1-r;
	++top;
	memcpy(cnt[top],cnt[top-1],sizeof cnt[top]);
	if(nl<=nr){
		if(el>er)for(int i=nl;i<=nr;++i)upd(top,i);
		else{
			for(int i=nl;i<el;++i)upd(top,i);
			for(int i=nr;i>er;--i)upd(top,i);
		}
	}
	if(l==r){
		for(int i=0;i<O;++i)
			H[l]=add(H[l],mul(cnt[top][i],(1ll<<(1ll*((res*i)%O)))%P));
		H[l]=mul(H[l],qsm(qsm(K,n),l));
		return;
	}
	solve(l,(l+r)>>1,nl,nr,top);
	solve(((l+r)>>1)+1,r,nl,nr,top);
}
bool check(int i){
	for(int j=0;j<K;++j)
		if(i&(1<<j)){
			for(int k=0;k<K;++k)
				if(!(i&(1<<Mul[k][j])))return 0;
			for(int k=0;k<K;++k)
				if((i&(1<<k))&&!(i&(1<<Add[k][j])))return 0;
		}
	return 1;
}
int main(){
	scanf("%d%d%d",&n,&K,&m);
	S[0][0]=1;
	for(int i=1;i<=m;++i)
		for(int j=1;j<=i;++j)
			S[i][j]=add(S[i-1][j-1],mul(j,S[i-1][j]));
	scanf("%d",&tp);
	if(tp==1){
		res=K;
		int tem=K;
		for(int i=2;i<=tem;++i)
			if(tem%i==0){
				++top;
				res/=i;
				p[top]=i;k[top]=1;
				while(tem%i==0)k[top]*=i,tem/=i;
			}
		res=qsm(res,n,O);
	}
	else{
		for(int i=0;i<K;++i)
			for(int j=0;j<K;++j)
				scanf("%d",&Add[i][j]);
		for(int i=0;i<K;++i)
			for(int j=0;j<K;++j)
				scanf("%d",&Mul[i][j]);
		for(int i=(1<<K)-1;~i;--i){
			if(!(i&1))continue;
			if(check(i)){
				if(i==(1<<K)-1)f[i]=1;
				for(int j=1;j<=it;++j)
					if((i&stk[j])==i)f[i]=sub(f[i],f[stk[j]]);
				stk[++it]=i;
				A[__builtin_popcount(i)]=add(A[__builtin_popcount(i)],f[i]);
			}
		}
		res=1;
	}
	cnt[0][1]=1;
	solve(0,m,1,0,0);
	for(int i=0;i<=m;++i)
		for(int j=0;j<i;++j)
			H[i]=sub(H[i],mul(H[j],S[i][j]));
	int ans=0;
	for(int i=0;i<=m;++i)
		ans=add(ans,mul(H[i],mul(S[m][i],qsm((P+1)>>1,i))));
	printf("%d\n",ans);
}