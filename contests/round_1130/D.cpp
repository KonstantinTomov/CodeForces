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

ll reses[200200];
ll von[200200];
ll voff[200200];
vector<ll> v[200200];
ll k;
bool used[200200];

void dfs(ll pos){
    used[pos]=1;
    von[pos]+=1;
    for(ll i : v[pos]){
        if(used[i])continue;
        dfs(i);
        von[pos]+=voff[i];
        voff[pos]+=max(voff[i],von[i]);
    }
}

void solve(){
    cin>>k;

    ll n,touse=-1;
    ll ct;
    ct=-1;
    for(ll i=0;i<k;++i){
        cin>>n;
        for(ll j=0;j<=n;++j){
            v[j].clear();
            used[j]=0;
            von[j]=0;
            voff[j]=0;
        }

        for(ll j=1,a,b;j<n;++j){
            cin>>a>>b;
            v[a].push_back(b);
            v[b].push_back(a);
        }

        dfs(1);
        if(n>=2 && ct==-1){
            ct=i;
            if(von[1]>voff[1]){
                touse=v[1][0];
            }
            else {
                touse=1;
            }
        }
        else {
            if(von[1]>voff[1]){
                reses[i]=1;
            }
            else {
                reses[i]=v[1][0];
            }
        }
    }

    if(ct==-1){
        for(ll i=2;i<=k;++i){
            cout<<i<<" "<<1<<" "<<1<<" "<<1<<endl;
        }
        return ;
    }

    for(ll i=0;i<k;++i){
        if(i==ct)continue;
        cout<<ct+1<<" "<<touse<<" "<<i+1<<" "<<reses[i]<<endl;
    }
    return ;
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

*/