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

ll towh[400400];
ll sums[400400];
ll howm[400400];
ll n,m,k;
void solve(){
    cin>>n>>m>>k;
    vector<pair<pair<ll,ll>,ll>> v;
    v.push_back({{1,0},0});

    ll mxsize = 0;
    for(ll i=0,a,b;i<n;++i){
        cin>>a>>b;
        
        if(a!=1){
            v[v.size()-1].first.second=a-1;
        }
        else {
            v.pop_back();
        }
        v.push_back({{a,b},1});
        v.push_back({{b+1,0},0});
    }
    v[v.size()-1].first.second=4e15;

    sums[0]=(v[0].first.second-v[0].first.first+1)*v[0].second;
    for(ll i=1;i<v.size();++i){
        sums[i]=(v[i].first.second-v[i].first.first+1)*v[i].second+sums[i-1];    
    }

    ll pp=0;
    ll val=0;
    for(ll i=0,x;i<v.size();++i){
        x=v[i].first.first+m-1;
        while(x>v[pp].first.second){
            ++pp;
        }
        towh[i]=pp;
        howm[i] = sums[pp-1]- (i==0 ? 0 : sums[i-1]) + (x-v[pp].first.first+1)*v[pp].second;
    }

    /*
    for(ll i=0;i<v.size();++i){
        cout<<"----"<<i<<endl;
        cout<<v[i].first.first<<" "<<v[i].first.second<<" "<<v[i].second<<endl;
        cout<<howm[i]<<" "<<towh[i]<<" "<<sums[i]<<endl;
    }
    */

    for(ll i=1,a,b;i<v.size();++i){
        if(k<min(howm[i],howm[i-1]) || k>max(howm[i],howm[i-1]))continue;

        if(k==howm[i]){
            cout<<v[i].first.first<<endl;
            return ;
        }
        if(k==howm[i-1]){
            cout<<v[i-1].first.first<<endl;
            return ;
        }
        
        a=towh[i];
        b=howm[i];
        
        //cout<<"---"<<i<<" "<<a<<" "<<b<<endl;

        if(howm[i-1]>howm[i]){ // i-1 is ones
            while(true){
                if(v[a].second==1){
                    --a;
                    continue;
                }

                if(b+(min(v[a].first.second,v[i].first.first+m-1)-v[a].first.first+1)>=k){
                    //k-b how much i need 
                    //v[a].first.second-(k-b) where i need to end
                    //v[a].first.second-(k-b)-m+1 where i need to begin
                    cout<<min(v[a].first.second,v[i].first.first+m-1)-(k-b)-m+1<<endl;
                    return ;
                }
                else {
                    b+=(min(v[a].first.second,v[i].first.first+m-1)-v[a].first.first+1);
                    --a;
                }
            }
        }
        else { // i-1 is 0s
            while(true){
                if(v[a].second==0){
                    --a;
                    continue;
                }

                if(b-(min(v[a].first.second,v[i].first.first+m-1)-v[a].first.first+1)<=k){
                    //b-k how much i need 
                    //v[a].first.second-(b-k) where i need to end
                    //v[a].first.second-(b-k)-m+1 where i need to begin
                    cout<<min(v[a].first.second,v[i].first.first+m-1)-(b-k)-m+1<<endl;
                    return ;
                }
                else {
                    b-=(min(v[a].first.second,v[i].first.first+m-1)-v[a].first.first+1);
                    --a;
                }
            }
        }
    }
    cout<<"-1"<<endl;
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
7
1 6 5
1 6
1 5 5
7 11
2 4 3
1 2
5 6
3 5 4
1 3
5 6
8 8
1 3 2
10 12
3 6 0
1 1
4 5
10 12
1 1000000000 1
1000000000000000 1000000000000000
*/