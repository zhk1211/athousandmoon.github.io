#include"bigint.cpp"
#include<bits/stdc++.h>
using namespace std;
//dengyaotriangle!

bigint n,phi;
vector<bigint> res;

int main(){
    cin>>n>>phi;
    bigint b=n+1-phi;
    bigint delta=b*b-n*4;
    bigint res;
    for(int i=700;i>=0;i--){
        bigint t=bigint(1)<<i;
        if((res+t)*(res+t)<=delta)res+=t;
    }
    cout<<2<<'\n'<<(b-res)/2<<'\n'<<(b+res)/2;
    // pq=n (p-1)(q-1)=phi ,p+q=n-phi+1
    return 0;
}