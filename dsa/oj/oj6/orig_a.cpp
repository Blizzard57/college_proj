#include<bits/stdc++.h>
using namespace std;

vector<long long int> strength;
vector< vector< long long int> > graph;
vector<long long int> visit;
long long int ct = -1;
long long int lev = 1;
long long int ans = 0;
vector<long long int> start;
vector<long long int> endme;
vector<long long int> level;
vector< long long int> seg;

void dfs(long long int s, long long int levi)
{
    long long int j;
    visit[s] = 1;
    ct++;
    start[s] = ct;
    level[s] = levi;

    for(j=0; j<graph[s].size(); j++)
    {
        if(visit[graph[s][j]] == 0)
        {
            dfs(graph[s][j], levi+1);
        }
    }

    endme[s] = ct;
    visit[s] = 2;
    return;
}

void update(long long int l,long long int r,long long int ind,long long int v,long long int ql, long long int qr)
{
    if(r<ql || qr<l)
    {
        return;
    }

    if(ql<=l && r<=qr)
    {
        seg[ind] += v;
        return;
    }
    
    update( l, (l+r)/2, (2*ind)+1, v, ql, qr);
    update( ((l+r)/2)+1, r, (2*ind)+2, v, ql, qr);
}

void query(long long int l,long long int r,long long int ind,long long int ql)
{

    if(r<ql || ql<l)
    {
        return;
    }

    if(l==r)
    {
        ans += seg[ind];
        return;
    }

    ans+=seg[ind];

    if(ql<=(l+r)/2)
    {
    query( l, (l+r)/2, (2*ind)+1, ql);
    }
    else
    {
    query( ((l+r)/2)+1, r, (2*ind)+2, ql);
    }
}

int main()
{
    long long int n,m,i,x,y,op,v;
    scanf("%lld %lld",&n,&m);

    graph.resize(n);
    strength.resize(n);
    visit.resize(n);
    start.resize(n);
    endme.resize(n);
    level.resize(n);
    seg.resize(4*n);

    for(i=0;i<n;i++)
    {
        scanf("%lld",&strength[i]);
    }

    for(i=0;i<n;i++)
    {
        visit[i] = 0;
    }

    for(i=0;i<n-1;i++)
    {
        scanf("%lld %lld",&x,&y);
        x--;
        y--;
        graph[x].push_back(y);
        graph[y].push_back(x);
    }

    dfs(0,lev);

    for(i=0;i<m;i++)
    {
        scanf("%lld",&op);
        ans = 0;

        if(op == 1)
        {
            scanf("%lld %lld",&x,&v);
            x--;

            if(level[x]%2==1)
            {
                v = -v;
            }

            update(0,n-1,0,v,start[x],endme[x]);

        }

        else
        {
            scanf("%lld",&x);
            x--;
            query(0,n-1,0,start[x]);

            if(level[x]%2==1)
            {
                ans = -ans;
            }

            printf("%lld\n",strength[x]+ans);
        }
    }
}




