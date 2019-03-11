#include<bits/stdc++.h>
#define mod 1000000007

struct node
{
    long long int lrem[9] = {0};
    long long int rrem[9] = {0};
    long long int count = 0;
    long long int totrem = 0;
};

long long int power(long long int x) 
{ 
    long long int res = 1;   
    x = x%mod;
    long long int y = mod -2;

    while (y > 0) 
    { 
        if (y%2==1)
        {
            res = (res*x)%mod; 
        }

        y = y/2;  
        x = (x*x)%mod;   
    } 

    return res%mod; 
}





struct node seg[400005];

node merge_node( node a, node b)
{

    long long int i;
    node temp;

    temp.count = a.count +b.count;
    temp.totrem = (a.totrem + b.totrem)%9;

    for(i=0;i<9;i++)
    {
        temp.lrem[i] = a.lrem[i];
        temp.rrem[i] = b.rrem[i];
    }


    for(i=0;i<9;i++)
    {
        temp.lrem[i] = temp.lrem[i] + b.lrem[(18-(a.totrem - i))%9];
        temp.rrem[i] = temp.rrem[i] + a.rrem[(18-(b.totrem - i))%9];
    }

    for(i=0;i<9;i++)
    {
        temp.count = temp.count + (b.lrem[i]*a.rrem[(9-i)%9]);
    }

    return temp;
}

void merge(long long int ind)
{

    long long int i;
    long long int c1 = 2*ind+1;
    long long int c2 = 2*ind+2;
    seg[ind].count  = seg[c1].count + seg[c2].count;

    seg[ind].totrem = (seg[c1].totrem + seg[c2].totrem)%9;

    for(i=0;i<9;i++)
    {
        seg[ind].lrem[i] = seg[c1].lrem[i];
        seg[ind].rrem[i] = seg[c2].rrem[i];
    }


    for(i=0;i<9;i++)
    {
        seg[ind].lrem[i] = seg[ind].lrem[i] + seg[c2].lrem[(18-(seg[c1].totrem - i))%9];
        seg[ind].rrem[i] = seg[ind].rrem[i] + seg[c1].rrem[(18-(seg[c2].totrem - i))%9];
    }

    for(i=0;i<9;i++)
    {
        seg[ind].count = seg[ind].count + (seg[c2].lrem[i]*seg[c1].rrem[(9-i)%9]);
    }

    return;

}

void update(long long int l, long long int r, long long int ind, long long int diff_val, long long int diff_ind, long long int num[])
{
    long long int i;

    if(l==r)
    {
        seg[ind].count = 0;
        seg[ind].totrem = 0;

        for(i=0;i<9;i++)
        {
            seg[ind].lrem[i] = 0;
            seg[ind].rrem[i] = 0;
        }

        seg[ind].lrem[diff_val%9] = 1;
        seg[ind].rrem[diff_val%9] = 1;

        if(diff_val%9==0)
        {
            seg[ind].count = 1;
        }

        seg[ind].totrem = diff_val%9;
    }

    else
    {
        if( l<=diff_ind && diff_ind<= ((l+r)/2))
        {
            update( l, (l+r)/2, (2*ind)+1, diff_val, diff_ind, num);
        }
        else// if( ((l+r)/2)+1<=diff_ind && diff_ind<= r)
        {
            update( ((l+r)/2)+1, r, (2*ind)+2, diff_val, diff_ind, num);
        }

        merge(ind);
    }

    return;
}

void  buildtree(long long int l,long long int r, long long int ind, long long int num[])
{

    if(l==r)
    {
        seg[ind].lrem[num[l]%9] = 1;
        seg[ind].rrem[num[l]%9] = 1;

        if(num[l]%9==0)
        {
            seg[ind].count = 1;
        }

        seg[ind].totrem = num[l]%9;
    }

    else
    {
        buildtree( l, (l+r)/2, (2*ind)+1, num);
        buildtree( ((l+r)/2)+1, r, (2*ind)+2, num);
        merge(ind);
    }

    return;
}

node qans(long long int l, long long int r, long long int ind, long long int ql, long long int qr)
{
    long long int i;
    if(l>r || r<ql || l>qr)
    {
        node temp;
        temp.count = 0;
        temp.totrem = 0;

        for(i=0;i<9;i++)
        {
            temp.lrem[i] = 0;
            temp.rrem[i] = 0;
        }

        return temp;
    }

    else if( r<=qr && l>=ql)
    {
        return seg[ind];
    }

    else
    {
        node tmp1, tmp2;
        tmp1 = qans( l, (l+r)/2, (2*ind)+1, ql, qr);
        tmp2 = qans( ((l+r)/2)+1, r, (2*ind)+2, ql, qr);

        return merge_node(tmp1,tmp2);
    }
}


int main()
{
    long long int n,q,op,x1,x2,i,temp;
    scanf("%lld %lld",&n,&q);
    char str[100005];
    scanf("%s",str);
    long long int len = strlen(str);
    long long int num[len];
    long long int b;

    for(i=0; i<=len-1; i++)
    {
        num[i] = ((long long int)str[i]) - 48;
    }

    buildtree(0, n-1, 0, num);

    while(q--)
    {
        scanf("%lld %lld %lld",&op,&x1,&x2);
        if(op==2)
        {
            node ans;
            ans = qans(0, n-1, 0, x1-1, x2-1);
            b = x2-x1+1;
            b = (b*(b+1))/2;
            printf("%lld\n",((ans.count)%mod*power(b))%mod);

        }
        else
        {
            update(0, n-1, 0, x2, x1-1, num);
        }
    }
}

