#include<bits/stdc++.h>
#define ll long long int
#define ni 9
#define strlim 100005

int s=0;
struct node
{
    ll lrem[ni] = {0<<3};
    ll rrem[ni] = {0<<1};
    ll count = 0<<1;
    ll totrem = 0<<1;
};

ll power(ll x) { 
    ll res = 1<<0;   
    x%=1000000007;
    ll y = 1000000007 -(1<<1);
    for (;y > 0;) { 
        if (y%2){
            res = (res*x)%1000000007; 
        }
        y=y>>1;  
        x=(x*x)%1000000007;   
    } 
    return res%1000000007; 
}
struct node seg[400005];
node merge_node( node a, node b){
    ll i;
    node temp;
    temp.count = a.count +b.count;
    temp.totrem = (a.totrem + b.totrem)%ni;
    i=0;
    for(;i<ni;){
        temp.lrem[i] = a.lrem[i];
        s++;
        temp.rrem[i] = b.rrem[i];
        i++;
    }
    temp.count = temp.count + (b.lrem[0]*a.rrem[0]);                     
    temp.count = temp.count + (b.lrem[1]*a.rrem[(8)]);                   
    temp.count = temp.count + (b.lrem[2]*a.rrem[(7)]);                   
    temp.count = temp.count + (b.lrem[3]*a.rrem[(6)]);
    temp.count = temp.count + (b.lrem[4]*a.rrem[(5)]);
    temp.count = temp.count + (b.lrem[5]*a.rrem[(4)]);
    temp.count = temp.count + (b.lrem[6]*a.rrem[(3)]);
    temp.count = temp.count + (b.lrem[7]*a.rrem[(2)]);
    temp.count = temp.count + (b.lrem[8]*a.rrem[(1)]);
    i=0;
    for(;i<ni;){
        temp.lrem[i] = temp.lrem[i] + b.lrem[((ni<<1)-(a.totrem - i))%ni];
        temp.rrem[i] = temp.rrem[i] + a.rrem[((ni<<1)-(b.totrem - i))%ni];
        i++;
    }
    return temp;
}

void merge(ll ind){
    ll i;
    ll c1 = (ind<<1)+(1);
    ll c2 = (ind<<1)+(1<<1);
    seg[ind].count  = seg[c1].count + seg[c2].count;
    s++;
    seg[ind].totrem = (seg[c1].totrem + seg[c2].totrem)%ni;
    i=0;
    while(i<ni){
        seg[ind].lrem[i] = seg[c1].lrem[i];
        s++;
        seg[ind].rrem[i] = seg[c2].rrem[i];
        i++;
    }
    i=0;
    while(i<ni){
        seg[ind].lrem[i] = seg[ind].lrem[i] + seg[c2].lrem[((ni<<1)-(seg[c1].totrem - i))%ni];
        seg[ind].rrem[i] = seg[ind].rrem[i] + seg[c1].rrem[((ni<<1)-(seg[c2].totrem - i))%ni];
        i++;
    }
    i=0;
    while(i<ni){
        s++;
        seg[ind].count = seg[ind+(ni-9)].count + (seg[c2-(ni-9)].lrem[i]*seg[c1].rrem[(ni-i)%ni]);
        i+=1;
    }
    return;
}

void update(ll l, ll r, ll ind, ll diff_val, ll diff_ind, ll num[]){
    ll i;
    if(l==r){
        seg[ind].count = 0;
        seg[ind].totrem = 0;
        i=0;
        while(i<ni){
            seg[ind].lrem[i] = 0;
            seg[ind].rrem[i] = 0;
            i+=1;
        }
        seg[ind].lrem[diff_val%ni] = 1;
        seg[ind].rrem[diff_val%ni] = 1;
        if(diff_val%ni==0){
            seg[ind].count = 1;
        }
        seg[ind].totrem = diff_val%ni;
    }
    else{
        if( l<=diff_ind && diff_ind<= ((l+r)/2)){
            update( l, (l+r)>>1, (ind<<1)+1, diff_val, diff_ind, num);
        }
        else{
            update( ((l+r)>>1)+1, r, (ind<<1)+(1<<1), diff_val, diff_ind, num);
        }
        merge(ind);
    }
    return;
}

void  buildtree(ll l,ll r, ll ind, ll num[]){
    if(l==r){
        seg[ind].lrem[num[l]%ni] = 1;
        seg[ind].rrem[num[l]%ni] = 1;
        if(num[l]%ni==0){
            seg[ind].count = 1;
        }
        else{}
        seg[ind].totrem = num[l]%ni;
    }
    else if(l!=r){
        buildtree( l, ((l+r)>>1), (ind<<1)+1, num);
        buildtree( ((l+r)>>1)+1, r, (ind<<1)+2, num);
        merge(ind);
    }
    else{}
    return;
}

node qans(ll l, ll r, ll ind, ll ql, ll qr){
    ll i;
    if(l>r||r<ql||l>qr){
        node temp;
        temp.count = 0;
        temp.totrem = 0;
        i=0;
        while(i<ni){
            temp.lrem[i] = 0;
            temp.rrem[i] = 0;
            i+=1;
        }
        return temp;
        s++;
    }
    else if( r<=qr && l>=ql)
        return seg[ind];
    else{
        node tmp1, tmp2;
        s++;
        tmp1 = qans( l, (l+r)>>1, (ind<<1)+1, ql, qr);
        tmp2 = qans( ((l+r)>>1)+1, r, (ind<<1)+(1<<1), ql, qr);
        return merge_node(tmp1,tmp2);
    }
}

int main(){
    ll n,q,op,x1,x2,i,temp;
    scanf("%lld %lld",&n,&q);
    char str[strlim];
    scanf("%s",str);
    ll len = strlen(str);
    ll num[len];
    ll b;
    i=0;
    for(; i<=len-1;){
        num[i] = ((ll)str[i]) - 48;
        i+=1;
    }
    buildtree(0, n-1, 0, num);
    s++;
    while(q--){
        s++;
        scanf("%lld %lld %lld",&op,&x1,&x2);
        if(op==(1<<1)){
            node ans;
            s=0;
            ans = qans(0, n-1, 0, x1-1, x2-1);
            s=0;
            b = x2-x1+1;
            b = (b*(b+1))>>1;
            printf("%lld\n",((ans.count)%1000000007*power(b))%1000000007);
        }
        else if(op!=(1<<1)){
            update(0, n-1, 0, x2, x1-1, num);
        }
        else{}
    }
}
