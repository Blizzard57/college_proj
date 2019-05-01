#include<bits/stdc++.h>
using namespace std;

const long long int sz = 2e5;
priority_queue <pair <long long int,long long int>, vector < pair <long long int,long long int> >, greater<pair<long long int,long long int> > > pq;
vector < pair<long long int,long long int> > graph[sz];
vector< pair<long long int,long long int> > revgraph[sz];
vector <long long int> dist;
vector <long long int> final_ans;

void dijkstra(long long int src)
{
    dist[src] = 0;
    pq.push(make_pair(dist[src],src));

    while(!pq.empty()){
        
        long long int s = pq.top().second;
        pq.pop();
        auto itr = graph[s].begin();
        
        for(;itr!=graph[s].end();itr++)
        {
            if(dist[itr->first]>dist[s] + itr->second)
            {
                dist[itr->first] = dist[s] + itr->second;
                pq.push(make_pair(dist[itr->first],itr->first));
            }
        }
    }
}


void revdijkstra(long long int src)
{
    dist[src] = 0;
    pq.push(make_pair(dist[src],src));

    while(!pq.empty()){
        
        long long int s = pq.top().second;
        pq.pop();
        auto itr = revgraph[s].begin();
        
        for(;itr!=revgraph[s].end();itr++)
        {
            if(dist[itr->first]>dist[s] + itr->second)
            {
                dist[itr->first] = dist[s] + itr->second;
                pq.push(make_pair(dist[itr->first],itr->first));
            }
        }
    }
}

int main()
{
    long long int n,e,i,x,y,v,j,ew,source,destination;

    scanf("%lld %lld %lld %lld",&n,&e,&source,&destination);

    source--;
    destination--;
    dist.resize(n);
    final_ans.resize(n);

    for(i=0;i<n;i++)
    {
        final_ans[i] = 0;
    }

    for(i=0;i<e;i++)
    {
        scanf("%lld %lld %lld",&x,&y,&ew);
        x--;
        y--;
        graph[x].push_back(make_pair(y,ew));
        revgraph[y].push_back(make_pair(x,ew));
    }

    for(i=0;i<n;i++)
    {
        dist[i] = INT_MAX;
    }
    
    dijkstra(source);
    for(i=0;i<n;i++)
    {
        final_ans[i] += dist[i];
        dist[i] = INT_MAX;
    }
    dijkstra(destination);
    for(i=0;i<n;i++)
    {
        final_ans[i] += dist[i];
        dist[i] = INT_MAX;
    }
    revdijkstra(source);
    for(i=0;i<n;i++)
    {
   //     printf("%lld ",dist[i]);
        final_ans[i] += dist[i];
        dist[i] = INT_MAX;
    }
    revdijkstra(destination);
    for(i=0;i<n;i++)
    {
   //     printf("%lld ",dist[i]);
        final_ans[i] += dist[i];
        dist[i] = INT_MAX;
    }

    long long int min = INT_MAX;
    
    for(i=0;i<n;i++)
    {
        if(i!=source && i!=destination && final_ans[i]<min)
        {
           min = final_ans[i];
        }
    }

    if(min==INT_MAX)
    {
        printf("-1");
    }
    
    else
    {
        printf("%lld",min);
    }

}



   


