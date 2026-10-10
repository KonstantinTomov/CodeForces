//this is bugged..

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

pair<pair<ll,ll>,pair<ll,ll>> bin[800800];
ll nums[200200];
ll n,k;

void build(ll pos,ll l,ll r){
    if(l==r){
        if(nums[l]!=0)bin[pos] = {{l,nums[l]},{l,nums[l]}};
        else bin[pos]={{1e9,0},{-1,0}};
        
    //cout<<"## "<<l<<" "<<r<<endl;
    //cout<<bin[pos].first.first<<" "<<bin[pos].first.second<<" "<<bin[pos].second.first<<" "<<bin[pos].second.second<<endl;
        return ;
    }

    ll mid=(l+r)/2;
    build(pos*2,l,mid);
    build(pos*2+1,mid+1,r);
    bin[pos].first = min(bin[pos*2].first,bin[pos*2+1].first);
    bin[pos].second = max(bin[pos*2].second,bin[pos*2+1].second);

    //cout<<"## "<<l<<" "<<r<<endl;
    //cout<<bin[pos].first.first<<" "<<bin[pos].first.second<<" "<<bin[pos].second.first<<" "<<bin[pos].second.second<<endl;
}

void ad(ll pos,ll l,ll r, ll x){
    if(l==r){
        bin[pos].first.second+=1;
        bin[pos].second.second+=1;
        bin[pos].first.first=l;
        bin[pos].second.first=l;
        return ;
    }
    
    ll mid=(l+r)/2;
    if(x<=mid)ad(pos*2,l,mid,x);
    else ad(pos*2+1,mid+1,r,x);
    bin[pos].first = min(bin[pos*2].first,bin[pos*2+1].first);
    bin[pos].second = max(bin[pos*2].second,bin[pos*2+1].second);
}

void rem(ll pos,ll l,ll r,ll x){
    if(l==r){
        bin[pos].first.second-=1;
        bin[pos].second.second-=1;
        if(bin[pos].first.second==0)bin[pos]={{1e9,0},{-1,0}};
        return ;
    }
    
    ll mid=(l+r)/2;
    if(x<=mid)rem(pos*2,l,mid,x);
    else rem(pos*2+1,mid+1,r,x);
    bin[pos].first = min(bin[pos*2].first,bin[pos*2+1].first);
    bin[pos].second = max(bin[pos*2].second,bin[pos*2+1].second);
}

pair<ll,ll> q(ll pos,ll l,ll r,ll ql,ll qr){
    if(r<ql || l>qr){
        return {1e9,-1};
    }
    if(l>=ql && r<=qr){
        return {bin[pos].first.first,bin[pos].second.first};
    }

    ll mid=(l+r)/2;
    pair<ll,ll> res1,res2;
    res1 = q(pos*2,l,mid,ql,qr);
    res2 = q(pos*2+1,mid+1,r,ql,qr);
    return {min(res1.first,res2.first),max(res1.second,res2.second)};
}

bool testworks(ll s){
    k+=s;
    
    cout<<"----"<<s<<endl;

    build(1,1,n);

    pair<ll,ll> res;
    ll remd = 0;
    while(true){
        res = q(1,1,n,1,k);
        cout<<res.first<<" - "<<res.second<<endl;
        if(res.first<=k){
            ++k;
            rem(1,1,n,res.first);
            ++remd;
        }
        else {
            res = q(1,1,n,1,k*2);
            
        cout<<res.first<<" - "<<res.second<<endl;
            if(res.second!=-1 && s){
                rem(1,1,n,res.second);
                ad(1,1,n,res.second/2 + res.second%2);
                ad(1,1,n,res.second/2 + res.second%2);
                --remd;
                --s;
            }
            else {
                break;
            }
        }
    }

    if(remd==n)return true;
}

void solve(){
    cin>>n>>k;
    for(ll i=0;i<=n;++i){
        nums[i]=0;
    }
    for(ll i=0,x;i<n;++i){
        cin>>x;
        ++nums[x];
    }

    ll l=0,r=n;
    ll res=-1;
    ll mid;

    while(l<=r){
        mid=(l+r)/2;

        if(testworks(mid)){
            res = mid;
            r=mid-1;
        }
        else {
            l=mid+1;
        }
    }
    cout<<n+res<<endl;
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
8
4 0
4 4 1 4
3 0
3 2 2
6 3
6 3 6 4 6 5
6 2
6 6 5 6 6 6
5 0
3 5 3 1 3
6 1
6 4 6 5 4 6
7 1
7 2 7 7 3 7 7
8 0
8 8 2 8 8 1 8 8


*/