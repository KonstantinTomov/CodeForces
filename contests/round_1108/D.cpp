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

ll a[100100];
ll n;
void solve(){
    cin>>n;
    
    for(ll i=1;i<=n;++i){
        cin>>a[i];
    }

    ll ontop=0,p2=1,mp2,res=1e9;
    for(ll j=0;j<=20;++j){

        mp2=1e9;
        for(ll i=1;i<=n;++i){
            if(a[i]%p2){
                ontop+=p2-a[i]%p2;
                a[i]=a[i]+(p2-a[i]%p2);
            }
            
            mp2=min(mp2,__builtin_ffsll(a[i])-1ll);
        }
        if(ontop>res)break;

        ll cur=mp2;
        for(ll i=1;i<=n;++i){
            ll mmm = 1e9;
            for(ll h=0,xxx;h<10;++h){
                xxx=__builtin_popcountll(a[i]+h*p2);
                xxx+=63-__builtin_clzll(a[i]+h*p2)-mp2;
                if(xxx+h*p2<mmm)mmm=xxx+h*p2;
            }
            cur+=mmm;
        }
        cur+=ontop;
        
        if(cur<res){
            res=cur;
        }
        p2*=2;
    }
    cout<<res<<endl;
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
6 8 2 4 1
3 4 1 2 
2 2   1
1 1   
__builtin_popcount(x) + ceil(log2(x))



3 4 1 2 1
2 2   1
1 1

2 3 3 3
2 4 4 4 + 3
1 2 2 2 + 1
1 2 2 2 + 7

1 1 0
6
3
2
1

*/