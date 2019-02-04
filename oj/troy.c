#include <stdio.h>
#define ll long long int

ll s[1005];
ll h[1005];
char a[1005][1005];
ll top;

void push(int val)
{
    s[++top]=val;
}

int pop()
{
    if(top==-1)
        return 0;
    top--;
    return 1;
}

int main()
{
    top=-1;
    ll m,n,tmp,li,ri,area,max=0;
    scanf("%lld %lld ",&m,&n);
    for(ll i=0;i<m;i++)
    {
        //printf("%s",a[i]);
        for(ll j=0;j<n;j++)
        {
            char tt[2];
            scanf("%s", tt);
            a[i][j] = tt[0];
            if(a[i][j]=='T')
                h[j]++;
            else
                h[j]=0;
        }
	    ll i=0;
	    for(i=0;i<n;)
	    {
	        if(top==-1 || h[s[top]]<=h[i])
	            push(i++);
	        else if(h[s[top]]>h[i])
	        {
	            tmp=s[top];
	            pop();
	            if(top==-1)
	                li=0,ri=i;
	            else
	                li=s[top]+1,ri=i;
	            area=h[tmp]*(ri-li);
	            if(area>max)
	                max=area;
	            //printf("tmp=%lld h[tmp]=%lld ri=%lld li=%lld area=%lld max=%lld\n",tmp,h[tmp],ri,li,area,max);
	        }
	        /*for(int i=0;i<=top;i++)
	        {
	            printf("%lld ",s[i]);
	        }
	        printf("\n");*/

	    }
	    while(top!=-1)
	    {
	        tmp=s[top];
	        pop();
	        if(top==-1)
	            li=0,ri=i;
	        else
	            li=s[top],ri=i-1;
	        area=h[tmp]*(ri-li);
	        if(area>max)
	            max=area;
	        //printf("YEET tmp=%lld h[tmp]=%lld ri=%lld li=%lld area=%lld max=%lld\n",tmp,h[tmp],ri,li,area,max);
	    }
    }
    /*for(int i=0;i<n;i++)
        printf("%lld ",h[i]);
    printf("\n");*/
    
    printf("%lld\n",max);
    return 0;       
}

