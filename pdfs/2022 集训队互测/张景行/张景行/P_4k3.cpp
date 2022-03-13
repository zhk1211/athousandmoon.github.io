#include"bigint.cpp"
#include<bits/stdc++.h>
using namespace std;
//dengyaotriangle!

bigint n,phi;
int ps;
vector<bigint> res;

bigint qpw(bigint x,int pw){
    bigint res=1;
    while(pw){
        if(pw&1)res=res*x;
        x=x*x;pw>>=1;
    }
    return res;
}


bigint qpwm(bigint x,bigint pw,bigint n){
    bigint res=1;
    int r=pw.digit();
    for(int i=0;i<r;i++){
        if((pw.data[i>>6]>>(i&63))&1)res=res*x%n;
        x=x*x%n;
    }
    return res;
}
mt19937_64 rng(chrono::steady_clock().now().time_since_epoch().count());
bigint rand(bigint thres){
    bigint ret;
    do{
        ret.data.resize(thres.data.size());
        for(int i=0;i<(int)ret.data.size();i++){
            ret.data[i]=rng();
        }
        int h=thres.digit()-(thres.data.size()-1)*64;
        if(h!=64)ret.data.back()&=((unsigned long long)1<<h)-1;
        while(!ret.data.empty()&&!ret.data.back())ret.data.pop_back();
    }while(ret>=thres||ret==0);
    return ret;
}
bigint gcd(bigint a,bigint b){
    int sft=0;
    while(a!=0){
        if(a>b)swap(a,b);
        else{
            bool fa=a.data[0]&1,fb=b.data[0]&1;
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
void factor(bigint n){
    if(n==1)return;
    while(~n.data[0]&1){
        res.push_back(2);n>>=1;
    }
    if(n==1)return;
    const int thres=25;
    for(int i=0;i<thres;i++){
        bigint a=rand(n);
        bigint g0=gcd(a,n);
        if(g0!=1){ 
            factor(g0);factor(n/g0);
            return;
        }
        a=qpwm(a,phi,n);
        bigint g=gcd(a-1,n);
        if(g!=1&&g!=n){
            factor(g);
            factor(n/g);
            return;
        }
    }
    res.push_back(n);
}
int main(){
    cin>>n>>phi;
    while(~phi.data[0]&1)phi>>=1,ps++;
    factor(n);
    sort(res.begin(),res.end());
    cout<<res.size()<<'\n';
    for(auto &x:res)cout<<x<<'\n';
    return 0;
}