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

vector<pair<ll,ll>> v;
ll n;
void solve(){
    v.clear();
    cin>>n;
    ll x,prev,cnt=1;
    cin>>x;

    prev=x;
    for(ll i=2;i<=n;++i){
        cin>>x;
        if(x==prev){
            ++cnt;
        }
        else {
            v.push_back({prev,cnt});
            cnt=1;
            prev=x;
        }
    }
    v.push_back({prev,cnt});
    
    ll zerosum = 1;
    for(pair<ll,ll> p : v){
            zerosum = (zerosum*fastpow(2ll,p.second-1,mod197))%mod197;
        }
    if(v[0].first!=-1){
        cout<<zerosum<<endl;
        return ;
    }
    
    cnt = 1;
    for(ll i=2;i<v.size();++i){
        if(v[i].first-1==v[i-1].first)++cnt;
    }
    cout<<(cnt*zerosum)%mod197<<endl;
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
2 2 2 2 3 3 3 3
+  -  +  -
2  0  2  0
-  +  -  +
-2 0 -2  0 

if cur + next can only be - / skip curr to make +
if cur - next can only be + / skip curr to make -

can always take what is needed many chances to skip C n 2 + C n 0 + C n 4 + ... 

start is + 
*/