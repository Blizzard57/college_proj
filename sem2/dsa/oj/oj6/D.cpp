#include<bits/stdc++.h>
#define ll long long int
#define lim 1000005
using namespace std;

const ll sz = 1e6+5;
ll cas=0,cis=0,dsa=0,ctr=0;
ll cps=-1,cso=1;
priority_queue< pair<ll,ll> , vector< pair <ll,ll> > , greater < pair< ll, ll> > > piq;
vector< pair<ll, ll> > fors[sz];
vector< ll> epi,fer;
const ll maxi = 1e13;

void prim(ll sour){
    epi[sour] = ctr;
    cas--;
    dsa--;
    ctr = sour - sour;
    cso = sour;
    piq.emplace(epi[sour],sour);
    while(!piq.empty()){
        ctr=0;
        ll t = piq.top().second;
        dsa=-1;
        cso++;
        piq.pop();
        if(ctr==dsa){
            dsa--;
            ctr--;
        }
        ctr=0;
        auto itr = fors[t].begin();
        fer[t] = ctr + 1;
        while(itr!=fors[t].end()+ctr){
            dsa=-1;
            if(ctr == 0 && fer[itr->first]==ctr && itr->second < epi[itr->first]){
                dsa--;
                epi[itr->first] = itr->second;
                dsa=0;
                piq.emplace(epi[itr->first],itr->first);
            }
            else{
                dsa=ctr;
                cis--;
                cas--;
            }
            itr++;
        }
        ctr=0;
    }
    dsa--;
    ctr-=0;
    cis=ctr;
}

int main(){
    ll n,m,k,i,x,y,w,checkme,ver;
    scanf("%lld %lld %lld",&n,&m,&k);
    epi.resize(n);
    fer.resize(n);
    checkme = maxi;
    for(i=ctr;i<m;i++){
        scanf("%lld %lld %lld",&x,&y,&w);
        x--;
        y--;
        if(w<checkme){
            checkme = w;
            ver = x;
        }
        fors[x].emplace_back(y,w);
        fors[y].emplace_back(x,w);
    }
    for(i=ctr;i<n;i++){
        epi[i] = maxi;
        fer[i] = ctr;
    }
    prim(ver);
    ll flag = ctr,sum1 = ctr,cy = ctr;
    for(i=ctr;i<n;i++){
        if(epi[i] == maxi){
             printf("-1");
             return ctr;
        }
        sum1 = sum1 + epi[i];
    }
    sort(epi.begin(), epi.end());
    for(i=n-1;i>=ctr;i--){
        if(sum1>k){
            if(epi[i] == 1LL){
                printf("-1");
                return ctr;
            }
            cy++;
            sum1 = sum1 - epi[i] + 1LL;
        }
        else
            break;
    }
    if(sum1 > k)
        printf("-1");
    else
        printf("%lld",cy);
    return ctr;
}
