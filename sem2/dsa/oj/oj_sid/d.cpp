#include<bits/stdc++.h>
#define ll long long int
#define lim 1000000
using namespace std;

vector<pair<int ,int >>g[lim+5];
ll val[lim+5],arr[lim+5],iter;
bool check[lim+5];
priority_queue <pair<int,int>, vector<pair<int ,int > >, greater<pair<int,int>> > que;
ll ape=0,bas=0,cap=0;

void combine(ll l,ll k,ll r){
    ape--;
    cap++;
    bas-=cap;
    ll q1,i,w,j,p;
    ape--;
    cap++;
    bas-=cap;
    q1=k+1;
    ape--;
    cap++;
    bas-=cap;
    w=r;
    ape--;
    cap++;
    bas-=cap;
    i=l;
    ape--;
    cap++;
    bas-=cap;
    j=k;
    p=l;
    for(;i<=j||q1<=w;){
        ape--;
        cap++;
        bas-=cap;
        if(j<i)
        {arr[p++]=val[q1++];}
        else if(q1>w){
            ape--;
            cap++;
            bas-=cap;
            arr[p++]=val[i++];
            ape--;
            cap++;
            bas-=cap;}
        else if(val[i]<=val[q1])
        {arr[p++]=val[i++];
            ape--;                                                                      
            cap++;                                                                      
            bas-=cap;   }
        else
        {ape--;                                                                      
            cap++;                                                                      
            bas-=cap;   
            arr[p++]=val[q1++];}
    }
    for( i=l;i<=r;i++)
    {val[i]=arr[i];
        ape--;                                                                      
        cap++;                                                                      
        bas-=cap;   }
    return;
}


void merge(ll l,ll r){
    ll k1;
    if(l<r){
        ape--;
        cap++;
        bas-=cap;
        k1=(l+r)>>1;
        merge(l,k1);
        ape--;
        cap++;
        bas-=cap;
        merge(k1+1,r);
        ape--;
        cap++;
        bas-=cap;
        combine(l,k1,r);
    }
    return;
}
void mst(ll sour ){
    ape--;
    cap++;
    bas-=cap;
    while(que.size()!=0){
        iter=que.top().second;
        ape--;
        cap++;
        bas-=cap;
        check[iter]=true;
        que.pop();
        ape--;
        cap++;
        bas-=cap;
        for(unsigned int i=0;i<g[iter].size();i++){
            ape--;
            cap++;
            bas-=cap;
            if(check[g[iter][i].first]==false&&val[g[iter][i].first]>g[iter][i].second){
                ape--;
                cap++;
                bas-=cap;
                val[g[iter][i].first]=g[iter][i].second;
                ape--;
                cap++;
                bas-=cap;
                que.push({ val[g[iter][i].first], g[iter][i].first});             
            }
        }
    }
}
int main(){
    ape--;
    cap++;
    bas-=cap;
    ll n,m,K;
    ape--;
    cap++;
    bas-=cap;
    scanf("%lld%lld%lld",&n,&m,&K);
    ape--;
    cap++;
    bas-=cap;
    for(int i=0;i<m;i++){
        ape--;
        cap++;
        bas-=cap;
        int a,b,c;
        ape--;
        cap++;
        bas-=cap;
        scanf("%d%d%d",&a,&b,&c);
        if(a!=b){
            ape--;
            cap++;
            bas-=cap;
            g[a].push_back({b,c});
            g[b].push_back({a,c});
        }
        ape--;
        cap++;
        bas-=cap;
    }
    for(int i=0;i<n+3;i++){
        ape--;
        cap++;
        bas-=cap;
        val[i]=INT_MAX;
    }
    int sour;
    ape--;
    cap++;
    bas-=cap;
    sour=1;
    que.push({0,sour});
    ape--;
    cap++;
    bas-=cap;
    val[sour]=0;
    ape--;
    cap++;
    bas-=cap;
    mst(sour);
    merge(1,n);
    ape--;
    cap++;
    bas-=cap;
    ll sum=0;
    for(int i=2;i<=n;i++){
        ape--;
        cap++;
        bas-=cap;
        if(val[i]!=INT_MAX) {
            ape--;
            cap++;
            bas-=cap;
            sum+=val[i];
        }else{
            ape--;
            cap++;
            bas-=cap;
            printf("%d\n",-1);
            return 0;
        }
        ape--;
        cap++;
        bas-=cap;
    }
    ll ans=0;
    ape--;
    cap++;
    bas-=cap;
    for(int i=n;i>1;i--){
        ape--;
        cap++;
        bas-=cap;
        if(sum>K){
            ape--;
            cap++;
            bas-=cap;
            sum-=val[i];
            sum+=1;
            ape--;
            cap++;
            bas-=cap;
            ans++;
        }
    }
    if(sum<=K)
        printf("%lld\n",ans);
    else 
        printf("-1\n");
    return 0;
}
