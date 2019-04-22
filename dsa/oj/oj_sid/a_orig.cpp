#include<bits/stdc++.h>
#define lamp 1000000
#define ll long long int
using namespace std;

ll str[2*lamp+5],s[2*lamp+10],finish[2*lamp+10];
vector<int>g[lamp+10];

ll t=1;
ll even[2*lamp+10],odd[2*lamp+10],vi[2*lamp+10];

void dfs(int i){
    ll m;
    s[i]=t++;
    vi[i]=1;

    for(int j=0;j<g[i].size();j++){
        m=g[i][j];
        if(vi[g[i][j]]==0)
        {
            dfs(g[i][j]);
        }

    }
    finish[i]=t++;


}


/*void buildsegmenttree(int pos, int l, int r) {
  if(l==r) {
  seg[pos] = a[l];
  return ;
  } 
  else {
  int m=(l+r)>>1;
  buildsegmenttree(2*pos,l,m);
  buildsegmenttree(2*pos+1,m+1,r);
  seg[pos] = max(seg[2*pos], seg[2*pos+1]);
  return ;
  }
  }
  */
void update(int pos, int l, int r, int x,int V,int y) {
    ll k;
    if(l==r) {
        if(s[y]%2==0){
            even[pos]+=V;
        }
        else if(s[y]%2==1){

            odd[pos]+=V;

        }
        return ;
    } 
    else {
        k= (l+r)>>1;
        if(x<=k)
            update(2*pos,l,k,x,V,y);
        else
            update(2*pos+1,k+1,r,x,V,y);

        if(s[y]%2==0){
            even[pos]+=V;
        }
        else if(s[y]%2==1){

            odd[pos]+=V;

        }
        return ;
    }
}

int evquery(int pos, int low, int high, int l, int r) {
    ll m,x,y;
    if(low>=l && high<=r)
    {

        return even[pos];


    }
    else{
        x=y=0;
        m = (low + high)>>1 ;
        if(l<=m)
            x =evquery(2*pos, low, m, l, r);
        if(r>m)
            y = evquery(2*pos+1, m+1, high, l, r);
        return x+y;
    }

}
int odquery(int pos, int low, int high, int l, int r) {
    ll m,x,y;
    if(low>=l && high<=r)
    {

        return odd[pos];

    }

    else{
        x=y=0;
        m = (low + high)>>1 ;
        if(l<=m)
            x = odquery(2*pos, low, m, l, r);
        if(r>m)
            y = odquery(2*pos+1, m+1, high, l, r);

        return x+y;
    }

}


int main(void) {

    ll N,M;
    scanf("%lld%lld",&N,&M);
    for(int i=1;i<=N;i++)
    {
        scanf("%lld",&str[i]);
    }
    long long   int a,b;
    for(int i=1;i<N;i++){
        scanf("%lld%lld",&a,&b);
        g[a].push_back(b);
        g[b].push_back(a);
    }
    ll evenval,oddval;
    dfs(1);
    int p,q,r;

    for(int i=0;i<M;i++){
        scanf("%d",&p);
        if(p==1){
            scanf("%d%d",&q,&r);
            update(1, 1, 2*N, s[q],r,q);
            update(1, 1, 2*N, finish[q],-r,q);

        }
        else if(p==2){
            int x;
            scanf("%d",&x);
            evenval=evquery(1,1,2*N,1,s[x]);
            oddval=odquery(1,1,2*N,1,s[x]);
            if(s[x]%2==0){
                ll ans;
                ans=str[x]+evenval-oddval;
                printf("%lld\n",ans);

            }
            else if(s[x]%2==1){
                ll ans;
                ans=str[x]+oddval-evenval;
                printf("%lld\n",ans);
            }


        }

    }
    return 0; 
}
