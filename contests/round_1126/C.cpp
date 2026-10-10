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

vector<ll> grey[20];

void buildgrey(){
    grey[0] = {0,1};
    for(ll i=1,p=2;i<20;++i){
        for(ll j=0;j<grey[i-1].size();++j)grey[i].push_back(grey[i-1][j]);
        for(ll j=grey[i-1].size()-1;j>=0;--j)grey[i].push_back(grey[i-1][j]+p);
        p*=2;
    }
}

void solve(){
    ll n;
    cin>>n;
    ll l2 = log2(n);
    ++l2;

    ll k = ((1<<l2)*2)-1;
    cout<<k<<endl;

    //00 01 11 10 00 01 11 10

    for(ll i=1;i<grey[l2-1].size();++i){
        cout<<(grey[l2-1][i-1]^grey[l2][i])<<" ";
    }
    cout<<grey[l2-1][grey[l2-1].size()-1]<<" ";
    for(ll i=1;i<grey[l2-1].size();++i){
        cout<<(grey[l2-1][i-1]^grey[l2-1][i])<<" ";
    }cout<<endl;

    return ;
}



int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    buildgrey();

    ll t;
    cin>>t;
    while(t--){
        solve();
    }
    
    return 0;
}
/*

*/