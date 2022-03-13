#include"bigint.cpp"

#include<bits/stdc++.h>
using namespace std;
//dengyaotriangle!

mt19937_64 rng(chrono::steady_clock().now().time_since_epoch().count());
template<typename t> t rndi(t l,t r){return uniform_int_distribution<t>(l,r)(rng);}

unsigned long long rand(int typ){
    switch(typ){
        case 0:return rng();
        case 1:return rndi<unsigned long long>(1,8);
        case 2:return -rndi<unsigned long long>(0,7);
        case 3:return rndi<long long>(-8,7);
    }
}
int main(){
    return 0;
}