#include<bits/stdc++.h>
using namespace std;

const long long int sz = 1e6+5;
priority_queue< pair<long long int,long long int> , vector< pair <long long int,long long int> > , greater < pair< long long int, long long int> > > pq;
vector< pair<long long int, long long int> > graph[sz];
vector< long long int> edges;
vector< long long int> visit;
const long long int MAX = 1e13;

void prim(long long int src)
{
    edges[src] = 0;
    pq.push(make_pair(edges[src],src));

    while(!pq.empty())
    {
        long long int t = pq.top().second;
        pq.pop();
        auto itr = graph[t].begin();
        visit[t] = 1;
        for(;itr!=graph[t].end();itr++)
        {
            if(visit[itr->first]==0 && itr->second < edges[itr->first])
            {
                edges[itr->first] = itr->second;
                pq.push(make_pair(edges[itr->first],itr->first));
            }
        }
    }
}

///////////////////////////////////////////////////////////////////////

int main()
{
    long long int n,m,k,i,x,y,w,checkme,ver;
    scanf("%lld %lld %lld",&n,&m,&k);
    edges.resize(n);
    visit.resize(n);

    checkme = MAX;

    for(i=0;i<m;i++)
    {
        scanf("%lld %lld %lld",&x,&y,&w);
        x--;
        y--;

        if(w<checkme)
        {
            checkme = w;
            ver = x;
        }

        graph[x].push_back(make_pair(y,w));
        graph[y].push_back(make_pair(x,w));
    }

    for(i=0;i<n;i++)
    {
        edges[i] = MAX;
        visit[i] = 0;
    }

    prim(ver);

    long long int flag = 0;
    long long int sum1 = 0;
    long long int cy = 0;

    for(i=0;i<n;i++)
    {
        if(edges[i] == MAX)
        {
             printf("-1");
             return 0;
            
        }
        sum1 = sum1 + edges[i];
    }
//    cout << sum1 << endl;
    sort(edges.begin(), edges.end());

    for(i=n-1;i>=0;i--)
    {
    //    cout << "i:" << i << " edge:" << edges[i] << endl;
        if(sum1>k)
        {
            if(edges[i] == 1LL){
                printf("-1");
                return 0;
            }
            cy++;
            sum1 = sum1 - edges[i] + 1LL;
        }
        else
            break;
    }
    // cout << sum1 << endl;
    if(sum1 > k)
        printf("-1");
    else
        printf("%lld",cy);
    return 0;
}



