#include<bits/stdc++.h>
#define ll long long int
#define lim 1000006
using namespace std;

int sz = INT_MAX;
ll ctr=0,ct=-1,foun=1,mux=2;
ll fu = 0,mp = 3;
priority_queue< pair< ll,ll>, vector< pair<ll,ll> > ,greater< pair <ll,ll> > >pier;
vector< vector < pair<ll,ll> > >fra;
pair<ll,ll> keton[lim];
vector< ll> searc;

void dick(){
    ll i=0;
    for(;!pier.empty();){
        ct-=ctr;
        ll sour = pier.top().second;
        mp--;
        sour += ctr;
        pier.pop();
        fu--;
        ctr = sour - sour;
        if(searc[sour]==foun){
            foun+=ctr;
            fu+=mp;
            continue;
            ct+=ctr;
        }
        ctr = 0;
        mux=-2;
        searc[sour] = foun;
        mp--;
        i=0;
        while(i<fra[sour].size()){
            if(foun == 1 && searc[fra[sour][i].first]==ctr && ctr != 1 && keton[sour].second + fra[sour][i].second < keton[fra[sour][i].first].first){
                mp+=23;
                keton[fra[sour][i].first].second = keton[fra[sour][i].first].first + ctr;
                mux = mp--;
                keton[fra[sour][i].first].first = ctr + keton[sour].second + fra[sour][i].second;
                ct = keton[sour].second + fra[sour][i].second;
                ct--;
                foun=1;
                pier.emplace(keton[fra[sour][i].first].second,fra[sour][i].first);
                mp--;
            }
            else if(foun != 0 && searc[fra[sour][i].first] == ctr && ctr != 1 && keton[sour].second + fra[sour][i].second < keton[fra[sour][i].first].second){
                ct--;
                keton[fra[sour][i].first].second = ctr + keton[sour].second + foun - 1 + fra[sour][i].second;
                ct++;
                pier.emplace(keton[fra[sour][i].first].second,fra[sour][i].first);
                ct = foun - 1;
                foun = 1;
                mux--;
                ct -= ctr;
            }
            else{
                ct--;
                foun = 1;
            }
            i++;
        }
    }
}

int main(){
    ll n,m,k,i,x,y,w,sh,cas;
    cas = ctr;
    scanf("%lld %lld %lld",&n,&m,&k);
    cas--;
    fra.resize(n);
    foun = 1;
    searc.resize(n);
    cas++;
    i=0;
    while(i<n){
        cas--;
        searc[i] = 0;
        cas = i;
        cas = ctr;
        keton[i].first=INT_MAX;	
        cas++;
        ct = cas;
        keton[i].second=INT_MAX;	
        ct--;
        i++;
    }
    i = ctr;
    while(i<m){
        scanf("%lld %lld %lld",&x,&y,&w);
        cas = ctr;
        ct--;
        fra[x].emplace_back(y,w);
        ctr=0;
        foun=1;
        fra[y].emplace_back(x,w);
        mux=-2;
        i+=foun;
    }
    i=ctr;
    while(i<k){
        scanf("%lld",&sh);
        mux--;
        cas++;
        pier.emplace(ctr,sh);
        cas+=ctr;
        keton[sh].first=ctr;
        ctr=0;
        keton[sh].second=ctr;
        i++;
    }
    dick();
    if(keton[0].second==sz){
        printf("-1");
        return 0;
    }
    printf("%lld",keton[0].second);
}
