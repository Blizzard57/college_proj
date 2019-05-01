#include<stdio.h>

long long int standard;

long long int ans(long long int arr[], long long int ind)
{
    long long int a = arr[ind];
    return a;
}

long long int push(long long int arr[], long long int back,long long int i)
{
    back++;
    arr[back] = i;
    return back;
}

long long int fun(long long int k, long long int n, long long int arr[])
{
    long long int slide[100010];
    long long int i, min0, takeme, top=-1, back=-1;
    long long int hello[100010] = {0};
    hello[0] = arr[0];

    for(i=1;i<k;i++)
    {
        hello[i] = arr[i] + hello[0];
    }

    for(i = 0; i < k; i++)
    {
        while(top>=0 && hello[i] <= hello[slide[back]])
        {
            if(back == top)
            {
                back = -1;
                top = -1;
            }

            else
            {
                back--;
            }
        }

        if(top<0)
        {
            top=0;
        }

        back = push(slide, back, i);
    }

    for(i = k ; i < n-1; i++)
    {
        min0 = hello[slide[top]]; 
        hello[i] = arr[i] + min0;

        while(top>=0 && slide[top] < i - k + 1)
        {
            if(top == back)
            {
                top=-1;
                back=-1;
            }

            else
            {
                top++;
            }
        }

        while(top>=0 && hello[i] <= hello[slide[back]])
        {
            if(back == top)
            {
                back = -1;
                top = -1;
            }
            else
            {
                back--;
            }
        }

        if(top<0)
        {
            top=0;
        }

        back = push(slide, back, i);    

    }

    min0 = hello[slide[top]];
    hello[i] = arr[i] + min0;
    takeme = ans( hello, n-1);
    return takeme + n-1;
}

void binarysearch(long long int l, long long int r, long long int thresh, long long int reenter[], long long int n)
{

    standard = 1000000000;

    while(l<=r)
    {
        long long int m = l + (r-l)/2;

        if(fun(m,n,reenter) > thresh)
        {
            l = m+1;
        }

        else
        {
            if(m < standard)
            {
                standard = m;
            }

            r = m-1;
        }

    }
}

int main()
{
    long long int n, t, i, ans;
    scanf("%lld %lld",&n,&t);
    long long int travel[100010];
    long long int reenter[100010];
    reenter[0] = 0;
    reenter[n-1] = 0;

    for(i=1;i<=n-1;i++)
    {
        scanf("%lld",&travel[i]);
    }

    for(i=1;i<n-1;i++)
    {
        scanf("%lld",&reenter[i]);
    }

    binarysearch(1, n-1, t, reenter, n);

    ans = standard < 1000000000 ? travel[standard] : n-1;

    for(i = standard+1; i<n; i++)
    {
            if(travel[i] < ans)
            {
                ans = travel[i];
            }
    }

    printf("%lld", ans);
   
}
