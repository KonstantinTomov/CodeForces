#include<bits/stdc++.h>
using namespace std;

#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx2")

typedef unsigned long long ull;
typedef long long ll;
typedef unsigned int ui;

const ll mod197 = 1e9 + 7;

vector<ll> fact;

ll fastpow(ll number,ll power,ll mod){
    ll answer = 1;
    
    while(power){
        if(power%2){
            answer = (answer * number) % mod;
        }
        number = (number * number) % mod;
        power /= 2;
    }

    return answer;
}

void init_fact(ll n, ll mod){
    fact = vector<ll>(n+1);

    fact[0]=1;
    for(ll i=1;i<=n;++i){
        fact[i] = (fact[i-1]*i)%mod;
    }
}

ll C(ll from,ll take, ll mod){
    ll res = fact[from];
    res = (res*fastpow(fact[take],mod-2,mod))%mod;
    res = (res*fastpow(fact[from-take],mod-2,mod))%mod;
    return res;
}

ll n;
void solve(){
    cin>>n;
    if(n==1){
        cout<<"1"<<endl;
        return ;
    }
    if(n==2){
        cout<<"-1"<<endl;
        return ;
    }
    cout<<"1 2 ";
    ll sum=3;
    n-=2;
    for(ll i=1;i<n;++i){
        cout<<sum<<" ";
        sum*=2;
    }cout<<sum<<endl;


}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll t;
    cin>>t;
    while(t--){
        solve();
    }
    
    return 0;
}
/*
1
1 9 2 6
12 3 10 20 15
2  3 2  2   3
2    5  2   5
3       5

210 010 101 201 011

1 2 3 6 12 
*/