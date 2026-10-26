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

ll nums[110];
ll n,k;
bool used[110];

void solve(){
    cin>>n>>k;
    k=n-k+1;

    for(ll i=0;i<110;++i)used[i]=0;

    for(ll i=0;i<n;++i){
        cin>>nums[i];
        if(i<k){
            used[nums[i]]=1;
        }
    }

    ll res=-1,res1=-1,res2=-1;
    for(ll i=0;i<=n;++i){
        if(!used[i]){
            res=i;
            break;
        }
    }

    for(ll i=k;i<n;++i){
        for(ll j=0;j<k;++j){
            used[nums[i]]=1;
            used[nums[j]]=0;
            for(ll h=0;h<=n;++h){
                if(!used[h]){
                    if(h>res){
                        res=h;
                        res1=j;
                        res2=i;
                    }
                    break;
                }
            }
            used[nums[i]]=0;
            used[nums[j]]=1;
        }
    }

    if(res1!=-1)cout<<min(res1,res2)+1<<" "<<max(res1,res2)+1<<endl;
    else cout<<"-1"<<endl;
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