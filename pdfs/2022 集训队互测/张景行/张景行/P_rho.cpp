#include"bigint.cpp"
#include<bits/stdc++.h>
using namespace std;
//dengyaotriangle!

typedef unsigned long long u64;
u64 n,phi;
vector<u64> res;

mt19937_64 rng(chrono::steady_clock().now().time_since_epoch().count());
u64 rand(u64 thres){
    return rng()%(thres-1)+1;
}
u64 qpwm(u64 x,u64 pw,u64 n){
    u64 res=1;
    while(pw){
        if(pw&1)res=res*(unsigned __int128)x%n;
        x=x*(unsigned __int128)x%n;pw>>=1;
    }
    return res;
}

u64 gcd(u64 a,u64 b){
    int sft=0;
    while(a!=0){
        if(a>b)swap(a,b);
        else{
            bool fa=a&1,fb=b&1;
            if(fa&&fb)b-=a;
            else if(fa)b>>=1;
            else if(fb)a>>=1;
            else{
                a>>=1;b>>=1;sft++;
            }
        }
    }
    return b<<sft;
}
bool miller(u64 n){
    if(n==1)return 0;
    if(n==2)return 1;
    if(~n&1)return 0;
    u64 pw=n-1;
    int c=0;
    while(~pw&1)pw>>=1,c++;
    const int t=15;
    for(int i=0;i<t;i++){
        u64 x=qpwm(rand(n),pw,n);
        if(x==0)return 0;
        if(x==1)continue;
        bool ok=0;
        for(int i=0;i<c;i++){
            if(x==n-1){
                ok=1;break;
            }
            x=x*(unsigned __int128)x%n;
        }
        if(!ok)return 0;
    }
    return 1;
}
int cnt=0;
void factor(u64 n){
    if(n==1)return;
    while(~n&1)res.push_back(2),n>>=1;
    if(n==1)return;
    if(miller(n)){
        res.push_back(n);return;
    }
    while(1){
        u64 a=rand(n),s=rand(n);
        u64 b=a;
        while(1){
            cnt++;
            a=(a*(unsigned __int128)a+s)%n;
            b=(b*(unsigned __int128)b+s)%n;
            b=(b*(unsigned __int128)b+s)%n;
            u64 p=(a>b?a-b:b-a);
            if(p==0)break;
            u64 g=gcd(p,n);
            if(g!=1){
                factor(n/g);factor(g);
                return;
            }
        }
    }
}
int main(){
    bigint _n,_phi;
    cin>>_n>>_phi;
    n=u64(_n);phi=u64(_phi);
    factor(n);
    sort(res.begin(),res.end());
    cerr<<cnt;
    cout<<res.size()<<'\n';
    for(auto &x:res)cout<<bigint(x)<<'\n';
    return 0;
}