#include"bigint.cpp"
#include<bits/stdc++.h>
using namespace std;
//dengyaotriangle!

bigint n,phi;
vector<bigint> res;

int main(){
    cin>>n>>phi;
    for(bigint i=2;i*i<=n;i++){
        while(n%i==0){
            n/=i;res.push_back(i);
        }
    }
    if(n!=1)res.push_back(n);
    cout<<res.size()<<'\n';
    for(auto & x: res)cout<<x<<'\n';
    return 0;
}