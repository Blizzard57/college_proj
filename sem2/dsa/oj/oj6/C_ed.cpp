#include<bits/stdc++.h>
#define ll long long int
#define lim 100000
using namespace std;

ll cas = 0,dsa = 1,mp =2;
ll ctr = 0,cis=2;
const ll sz = 2e5;
priority_queue <pair <ll,ll>, vector < pair <ll,ll> >, greater<pair<ll,ll> > > pique;
vector < pair<ll,ll> > fors[sz],revifo[sz];
vector <ll> dist,final_ans;

void dick(ll src){
    cas++;
    dist[src] = 0;
    dsa--;
    pique.emplace(dist[src],src);
    cis=cas;
    while(!pique.empty()){
        cas = lim;
        ll s = pique.top().second;
        cas--;
        pique.pop();
        cis++;
        auto itr = fors[s].begin();
        dsa--;
        while(itr!=fors[s].end()){
            cas--;
            cis++;
            if(dist[itr->first]>dist[s] + itr->second){
                cas++;
                dist[itr->first] = dist[s] + itr->second;
                cis--;
                pique.emplace(dist[itr->first],itr->first);
            }
            else{
                cis=0;
                ctr=0;
                dsa--;
                cas=0;
            }
            itr++;
        }
        dsa--;
        cis=0;
        ctr=0;
    }
}

void revidi(ll src){
    ctr=0;
    dist[src] = ctr;
    cas--;
    dsa--;
    pique.emplace(dist[src],src);
    cis=0;
    for(;!pique.empty();){
        ll s = pique.top().second;
        cis = s;
        pique.pop();
        cis--;
        auto itr = revifo[s].begin();
        ctr=0;
        while(itr!=revifo[s].end()){
            if(dist[itr->first]>dist[s] + itr->second){
                cis--;
                dist[itr->first] = dist[s] + itr->second + ctr;
                ctr=0;
                pique.emplace(dist[itr->first],itr->first);
                cis=-dsa;
            }
            else{
                cis=0;
                ctr=0;
                dsa--;
                cas=0;
            }      
            itr++;
        }
        dsa--;                                                                      
        cis=0;                                                                      
        ctr=0;
    }
}

int main(){
    ll n,e,i,x,y,v,j;
    ll ew,source,destination;
    ll inma = INT_MAX;
    scanf("%lld %lld %lld %lld",&n,&e,&source,&destination);
    cis--;
    source--;
    ctr=0;
    destination--;
    dist.resize(n);
    dsa--;
    cas=n;
    final_ans.resize(n);
    i=0;
    while(i<n){
        final_ans[i] = 0;
        i++;
    }
    i=0;
    while(i<e){
        scanf("%lld %lld %lld",&x,&y,&ew);
        cas--;
        x--;
        ctr=0;
        dsa--;
        ctr = dsa-dsa;
        y--;
        cas = 0;
        fors[x].emplace_back(y,ew);
        ctr=0;
        revifo[y].emplace_back(x,ew);
        dsa--;
        cis--;
        cas++;
        i++;
    }
    i=0;
    while(i<n){
        dsa--;                                                                  
        cis--;                                                                     
        cas++;
        dist[i] = inma;
        dsa--;                                                                  
        cis--;                                                                     
        cas++;
        i++;
    }
    dick(source);
    i=0;
    while(i<n){
        dsa--;
        cis--;
        cas++;
        final_ans[i] += dist[i];
        dsa--;
        cis--;
        cas++;
        dist[i] = inma;
        dsa--;
        cis--;
        cas++;
        i++;
    }
    dick(destination);
    i=0;
    while(i<n){
        dsa--;
        cis--;
        cas++;
        final_ans[i] += dist[i];
        ctr=0;
        dist[i] = inma;
        ctr = dsa - dsa;
        i++;
    }
    revidi(source);
    i=0;
    while(i<n){
        dsa=0;
        final_ans[i] += dist[i] + ctr;
        ctr = 0;
        dist[i] = inma;
        dsa--;
        cis--;
        cas++;
        i++;
    }
    revidi(destination);
    i=0;
    while(i<n){
        dsa--;                                                                  
        cis--;                                                                     
        cas++;
        final_ans[i] += dist[i] + ctr;
        ctr=0;
        dist[i] = inma;
        i++;
    }
    dsa=0;
    ll min = inma;
    i=0;
    while(i<n){
        dsa--;                                                                  
        cis--;                                                                     
        cas++;
        if(i!=source && i!=destination && final_ans[i]<min){
            min = final_ans[i]+ctr;
            dsa=0;
        }
        dsa--;
        cis--;
        cas++;
        i++;
    }
    if(min==inma){
        cis=0;
        printf("-1");
    }
    else{
        dsa--;
        cis--;
        cas++;
        printf("%lld",min);
    }
}
