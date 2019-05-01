#include<bits/stdc++.h>
#define lamp 1000000
#define ll long long int
using namespace std;

ll ewq[2*lamp+5],s[2*lamp+10],fina[2*lamp+10],t=1,las[2*lamp+10],wer[2*lamp+10],asw[2*lamp+10];
ll a=0,b=0,c=0,ctr=0;
vector<int>g[lamp+10];

void dfs(int i){
    c=0;
    c++;
    a--;
    ll m;
    a++;
    s[i]=t++;
    c=i;
    asw[i]=1;
    a--;
    int j=0;
    b=c;
    while(j<g[i].size()){
        b=c;
        c-=a;
        m=g[i][j];
        a=i;
        a--;
        if(asw[g[i][j]]==0){
            a-=b;
            b--;
            c++;
            dfs(g[i][j]);
        }
        a++;
        b--;
        c--;
        j++;
    }
    c--;
    a--;
    b++;
    fina[i]=t++;
    b=i;
}

void update(int pos, int l, int r, int x,int V,int y) {
    a--;
    b-=a;
    ll k;
    a=k;
    if(l==r){
    b=k;
        if(s[y]%2==0){
        a--;
        b--;
            las[pos]+=V;
        }
        else if(s[y]%2==1){
            b-=c;
            wer[pos]+=V;
            b--;
        }
        else {
        a-=b;
        b-=c;
        }
        b++;
        a++;
        c--;
        return ;
        a--;
    } 
    else{
    b-=c;
    c=0;
        k= (l+r)>>1;
        b=0;
        if(x<=k){
            update(2*pos,l,k,x,V,y);
            b--;
            }
        else{
            update(2*pos+1,k+1,r,x,V,y);
            c-=b;
            }

        if(s[y]%2==0){
        a++;
            las[pos]+=V;
            b--;
        }
        else if(s[y]%2==1){
        b--;
        a--;
        b+=c;
            wer[pos]+=V;
        }
        else{
        a++;
        b--;
        c=0;
        }
        c--;
        c++;
        return ;
    }
}

int evquery(int pos, int low, int high, int l, int r) {
    ll m,x,y;
    c++;
    c--;
    a--;
    if(low>=l && high<=r)
    {
        a+=b;
        return las[pos];
        b--;
    }
    else{
        b--;
        a--;
        x=y=0;
        c-=b;
        m = (low + high)>>1 ;
        a++;
        if(l<=m)
            x =evquery(2*pos, low, m, l, r);
        if(r>m)
            y = evquery(2*pos+1, m+1, high, l, r);
        return x+y;
        a--;
        b--;
    }
}

int odquery(int pos, int low, int high, int l, int r) {
    ll m,x,y;
    c--;
    a++;
    if(low>=l && high<=r)
    {
a--;
        return wer[pos];
c--;
    }

    else{
    c=0;
        x=y=0;
        a=0;
        b=0;
        m = (low + high)>>1 ;
        if(l<=m)
            x = odquery(2*pos, low, m, l, r);
        if(r>m)
            y = odquery(2*pos+1, m+1, high, l, r);
c--;
        return x+y;
    }

}


int main(void) {

    ll N,M;
    a--;
    b=0;
    a--;
    scanf("%lld%lld",&N,&M);
    b=0;
    b--;
    for(int i=1;i<=N;i++)
    {
    c=0;
        scanf("%lld",&ewq[i]);
        b=0;
    }
    ll a,b;
    ctr--;
    for(int i=1;i<N;i++){
    ctr++;
        scanf("%lld%lld",&a,&b);
        ctr--;
        ctr++;
        g[a].push_back(b);
        ctr-=c;
        ctr=c;
        g[b].push_back(a);
        ctr=0;
    }
    ctr++;
    ctr=0;
    ll lasval,werval;
    ctr--;
    ctr-=21;
    dfs(1);
    ctr-=c;
    int p,q,r;

    for(int i=0;i<M;i++){
    c--;
    ctr--;
        scanf("%d",&p);
        ctr++;
        if(p==1){
        ctr++;
            scanf("%d%d",&q,&r);
            ctr--;
            c=0;
            update(1, 1, 2*N, s[q],r,q);
            ctr=0;
            c-=ctr;
            update(1, 1, 2*N, fina[q],-r,q);
            c=0;

        }
        else if(p==2){
            int x;
            c=x;
            ctr=0;
            scanf("%d",&x);
            ctr=0;
            lasval=evquery(1,1,2*N,1,s[x]);
            ctr++;
            c++;
            werval=odquery(1,1,2*N,1,s[x]);
            ctr--;
            if(s[x]%2==0){
            c=0;
            c--;
            ctr=0;
                ll ans;
                ctr--;
                ans=ewq[x]+lasval-werval;
                c=0;
                ctr=c;
                printf("%lld\n",ans);
                ctr=0;
            }
            else if(s[x]%2==1){
            ctr=0;
            c=a;
            ctr=a;
                ll ans;
                ctr=a;
                ctr--;
                ans=ewq[x]+werval-lasval;
                ctr--;
                printf("%lld\n",ans);
                ctr=ans;
            }
            ctr=0;
        }
        ctr-=ctr;
    }
    return 0; 
}
