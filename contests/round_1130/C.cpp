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

vector<ll> v;
ll n,k;

bool checker(ll x){
    ll prev=-1;
    ll cnt=0;

    for(ll i=0;i<n;++i){
        if(i!=n-1 && v[i+1]-v[i]<=x){
            continue;
        }
        if(i!=0 && v[i]-v[i-1]<=x){
            continue;
        }
        if(prev!=-1 && abs(v[i]-prev)<=x){
            continue;
        }

        if(cnt==k)return false;
        ++cnt;
        prev=v[i]+x;
    }
    return true;
}

void solve(){
    cin>>n>>k;
    v.clear();
    for(ll i=0,x;i<n;++i){
        cin>>x;
        v.push_back(x);
    }

    ll l=1,r=1e9,mid;
    ll res=-1;

    while(l<=r){
        mid=(l+r)/2;

        if(checker(mid)){
            res=mid;
            r=mid-1;
        }
        else {
            l=mid+1;
        }
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


1 2 3 4 5 6 7
  x     x   x
*/