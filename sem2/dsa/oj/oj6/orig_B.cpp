#include<bits/stdc++.h>
using namespace std;

int sz = INT_MAX;
priority_queue< pair< long long int,long long int>, vector< pair<long long int,long long int> > ,greater< pair <long long int,long long int> > >pq;
vector< vector < pair<long long int,long long int> > >graph;
pair<long long int,long long int> ester[1000006];
vector< long long int> visit;

void dijkstra()
{
    long long int i;

    while(!pq.empty())
    {
        long long int src = pq.top().second;
        pq.pop();
        if(visit[src]==1)
        {
            continue;
        }

        visit[src] = 1;

        for(i=0;i<graph[src].size();i++)
        {
            if(visit[graph[src][i].first]==0 && ester[src].second + graph[src][i].second < ester[graph[src][i].first].first)
            {
                ester[graph[src][i].first].second = ester[graph[src][i].first].first;
                ester[graph[src][i].first].first = ester[src].second + graph[src][i].second;
                pq.push(make_pair(ester[graph[src][i].first].second,graph[src][i].first));
            }

            else if(visit[graph[src][i].first] == 0 && ester[src].second + graph[src][i].second < ester[graph[src][i].first].second)
            {
                ester[graph[src][i].first].second = ester[src].second + graph[src][i].second;
                pq.push(make_pair(ester[graph[src][i].first].second,graph[src][i].first));

            }
        }
    }
}

int main()
{
    long long int n,m,k,i,x,y,w,sh;

    scanf("%lld %lld %lld",&n,&m,&k);

    graph.resize(n);
    visit.resize(n);
    // ester.resize(n);

    for(int i=0;i<n;i++)
    {
        visit[i] = 0;
        ester[i].first=INT_MAX;	
        ester[i].second=INT_MAX;	
    }
    for(i=0;i<m;i++)
    {
        scanf("%lld %lld %lld",&x,&y,&w);
        graph[x].push_back(make_pair(y,w));
        graph[y].push_back(make_pair(x,w));
    }

    for(i=0;i<k;i++)
    {
        scanf("%lld",&sh);
        pq.push(make_pair(0,sh));
        ester[sh].first=0;
        ester[sh].second=0;
    }

    dijkstra();

// for(int i=0;i<n;i++)
	// cout<<ester[i].first<<" "<<ester[i].second<<endl;
    
    if(ester[0].second==sz)
    {
        printf("-1");
        return 0;
    }

    printf("%lld",ester[0].second);
}