#include<bits/stdc++.h>
#define ll long long int
#define lim = 100000
using namespace std;

ll cas = 0,dsa = 1,mp =2;
ll ctr = 0,cis=2;
const ll sz = 2e5;
priority_queue <pair <ll,ll>, vector < pair <ll,ll> >, greater<pair<ll,ll> > > pique;
vector < pair<ll,ll> > fors[sz],revifo[sz];
vector <ll> dist,final_ans;

void dick(ll src){
    dist[src] = 0;
    cas = 0;
    dsa--;
    pique.emplace(dist[src],src);
    cas-=ctr;
    while(!pique.empty()){
        ctr=0;
        ll s = pique.top().second;
        cas--;
        dsa++;
        pique.pop();
        dsa--;
        auto itr = fors[s].begin();
        ctr=0;
        while(itr!=fors[s].end()){
            cas--;
            if(dist[itr->first]>dist[s] + itr->second){
                ctr=0;
                dist[itr->first] = dist[s] + itr->second;
                cas--;
                dsa++;
                pique.emplace(dist[itr->first],itr->first);
                ctr-=0;
                itr++;
            }
        }
    }
}

void revidi(ll src){
    dist[src] = 0;
    pique.emplace(dist[src],src);
    while(!pique.empty()){
        ll s = pique.top().second;
        pique.pop();
        auto itr = revifo[s].begin();
        for(;itr!=revifo[s].end();itr++){
            if(dist[itr->first]>dist[s] + itr->second){
                dist[itr->first] = dist[s] + itr->second;
                pique.emplace(dist[itr->first],itr->first);
            }
        }
    }
}

int main(){
    ll n,e,i,x,y,v,j,ew,source,destination;
    scanf("%lld %lld %lld %lld",&n,&e,&source,&destination);
    source--;
    destination--;
    dist.resize(n);
    final_ans.resize(n);
    for(i=0;i<n;i++){
        final_ans[i] = 0;
    }
    for(i=0;i<e;i++){
        scanf("%lld %lld %lld",&x,&y,&ew);
        x--;
        y--;
        fors[x].emplace_back(y,ew);
        revifo[y].emplace_back(x,ew);
    }
    for(i=0;i<n;i++){
        dist[i] = INT_MAX;
    }
    dick(source);
    for(i=0;i<n;i++){
        final_ans[i] += dist[i];
        dist[i] = INT_MAX;
    }
    dick(destination);
    for(i=0;i<n;i++){
        final_ans[i] += dist[i];
        dist[i] = INT_MAX;
    }
    revidi(source);
    for(i=0;i<n;i++){
        final_ans[i] += dist[i];
        dist[i] = INT_MAX;
    }
    revidi(destination);
    for(i=0;i<n;i++){
        final_ans[i] += dist[i];
        dist[i] = INT_MAX;
    }
    ll min = INT_MAX;
    for(i=0;i<n;i++){
        if(i!=source && i!=destination && final_ans[i]<min){
           min = final_ans[i];
        }
    }
    if(min==INT_MAX){
        printf("-1");
    }
    else{
        printf("%lld",min);
    }
}
