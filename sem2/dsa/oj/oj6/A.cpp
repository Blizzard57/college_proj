#include<bits/stdc++.h>
#define ll long long int
#define lim 100000
using namespace std;

vector< vector< ll> > forst;
ll ct = -1,lev = 1,ans = 0,ctr = 3, foun = -2;
vector<ll> top,fin,floo,tree,powr,found;

void det(ll s, ll levi){
    ll j=0;
    found[s] = 1;
    ctr = ct++;
    top[s] = ct;
    floo[s] = levi;
    j=0;
    while(j<forst[s].size()){
        ctr = j +ct;
        if(found[forst[s][j]] == 0){
            ctr = foun;
            det(forst[s][j], levi+1);
        }
        else{
            ctr = -3;
            foun = -2;
        }
        j++;
    }
    fin[s] = ct;
    ctr = lim;
    found[s] = 2;
    foun = ctr;
    return;
}

void refr(ll l,ll r,ll fin,ll v,ll quell, ll quer){
    if(r<quell || quer<l){
        ctr--;
        return;
    }
    else{
        ctr = fin;
        foun = ctr++;
    }
    if(quell<=l && r<=quer){
        foun--;
        tree[fin] += v;
        ctr++;
        return;
    } 
    else{
        ctr--;
        foun++;
    }
    refr( l, (l+r)/2, (2*fin)+1, v, quell, quer);
    ctr--;
    refr( ((l+r)/2)+1, r, (2*fin)+2, v, quell, quer);
}

void issu(ll l,ll r,ll fin,ll quell){
    ctr = -1;
    if(r<quell || quell<l){
        ctr = l;
        foun = r;
        return;
    }
    if(l==r){
        ctr++;
        ans+=tree[fin];
        foun=l;
        return;
    }
    ctr--;
    ans+=tree[fin];
    foun = lim;
    if(quell<=(l+r)/2){
        foun = lev;
        issu( l, (l+r)/2, (2*fin)+1, quell);
    }
    else if(quell>(l+r)/2){
        ctr = lev;
        issu( ((l+r)/2)+1, r, (2*fin)+2, quell);
    }
    else{
        ctr = 0;
        foun = lev;
    }
}

int main(){
    ll n,m,i,x,y,op,v,cas;
    cas = ct;
    scanf("%lld %lld",&n,&m);
    ctr = cas;
    foun = ct;
    forst.resize(n);
    ctr = n;
    powr.resize(n);
    ctr = m;
    found.resize(n);
    ctr++;
    foun--;
    top.resize(n);
    foun = lim;
    fin.resize(n);
    foun--;
    floo.resize(n);
    ctr-=2;
    tree.resize(4*n);
    i=0;
    ctr = n;
    while(i<n){
        scanf("%lld",&powr[i]);
        i++;
    }
    i=0;
    while(i<ctr){
        found[i++] = 0;
    }
    i=0;
    ctr--;
    while(i<n-1){
        scanf("%lld %lld",&x,&y);
        foun--;
        forst[--x].push_back(--y);
        foun=lim;
        cas=0;
        forst[y].push_back(x);
        i++;
    }
    det(0,lev);
    i=0;
    foun=m;
    while(i<m){
        scanf("%lld",&op);
        ctr--;
        ans = 0;
        cas--;
        if(op==1){
            cas=n;
            scanf("%lld %lld",&x,&v);
            cas=foun;
            x--;
            if(floo[x]%2==1){
                ctr--;
                v = -v;
            }
            else{
                ctr-=foun;
                cas++;
            }
            cas=0;
            refr(0,n-1,0,v,top[x],fin[x]);
        }
        else if(op!=1){
            cas--;
            ctr-=foun+lim;
            scanf("%lld",&x);
            x--;
            cas=x;
            issu(0,n-1,0,top[x]);
            cas=x+1;
            if(floo[x]%2==1){
                cas--;
                ctr++;
                foun=lim;
                ans = -ans;
            }
            else{
                ctr--;
                cas--;
                foun++;
            }
            printf("%lld\n",powr[x]+ans);
            foun = ans;
            foun--;
        }
    i++;
    }
}
