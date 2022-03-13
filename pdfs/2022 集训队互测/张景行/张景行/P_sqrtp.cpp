#include"bigint.cpp"
#include<bits/stdc++.h>
using namespace std;
//dengyaotriangle!

bigint n,phi;
vector<bigint> res;

int main(){
    cin>>n>>phi;
    for(int i=2;(bigint)i*i*i<=n;i++){
        int rem=0;
        for(int j=n.data.size()-1;j>=0;j--){
            rem=((long long)(rem)<<32)%i;
            rem=((long long)(rem)<<32)%i;
            rem=(rem+n.data[j]%i)%i;
        }
        if(rem==0){
            phi/=i-1;
            n/=i;res.push_back(i);
            while(n%i==0){
                n/=i;
                phi/=i;
                res.push_back(i);
            }
        }
    }
    if(n!=1){
        bigint b=n+1-phi;
        bigint delta=b*b-n*4;
        bigint r;
        for(int i=700;i>=0;i--){
            bigint t=bigint(1)<<i;
            if((r+t)*(r+t)<=delta)r+=t;
        }
        bigint r1=(b-r)/2,r2=(b+r)/2;
        if(r1*r2==n){
            res.push_back(r1);res.push_back(r2);
        }else{
            bigint rz=n-phi;
            if(rz*rz==n){
                res.push_back(rz);res.push_back(rz);
            }else{
                res.push_back(n);
            }
        }
    }
    sort(res.begin(),res.end());
    cout<<res.size()<<'\n';
    for(auto &x:res)cout<<x<<'\n';
    // pq=n (p-1)(q-1)=phi ,p+q=n-phi+1
    return 0;
}