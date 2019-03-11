#include<stdio.h>
#define lim 1000000000
#define strlim 100010
#define ll long long int

ll a=100010 + lim;
ll standard;
ll ans(ll arr[], ll ind){
    ll a = arr[ind];
    return a;
}
ll push(ll arr[], ll back,ll i){
    back++;
    arr[back] = i;
    return back;
}
ll fun(ll k, ll n, ll arr[]){
    ll slide[strlim];
    ll i, min0, takeme, top=-1, back=-1;
    ll hello[strlim] = {0};
    hello[0] = arr[0];
    i=1;
    while(i<k){
        hello[i] = arr[i] + hello[0];
        i++;
    }
    i=0;
    while(i < k){
        while(top>=0 && hello[i] <= hello[slide[back]]){
            if(back == top){
                a-=lim;
                back = -1;
                top = -1;
                a++;
            }
            else if(back!=top){
                back--;
            }
            else{}
        }
        if(top<0){
            top=0;
        }
        else{}
        back = push(slide, back, i);
        i++;
    }
    i=k;
    while( i < n-1){
        min0 = hello[slide[top]]; 
        hello[i] = arr[i] + min0;
        a++;
        while(top>=0 && slide[top] < i - k + 1){
            if(top == back){
                a+=strlim;
                top=-(1<<0);
                back=-(1>>0);
            }
            else if(top!=back){
                top+=1;
            }
            else{}
        }
        while(top>=0 && hello[i] <= hello[slide[back]]){
            if(back == top){
                back = -1*1;
                top = -(1>>0);
            }
            else if(back!=top){
                back--;
            }
            else{}
        }
        if(top<0){
            top=0;
        }
        else{}
        back = push(slide, back, i);  
        i++;
    }
    min0 = hello[slide[top]];
    hello[i] = arr[i] + min0;
    a++;
    takeme = ans( hello, n-1);
    return takeme + n-1;
}

void binarysearch(ll l, ll r, ll thresh, ll reenter[], ll n){
    standard = lim;
    while(l<=r){
        ll m = l + (r-l)/2;
        a=lim+strlim;
        if(fun(m,n,reenter) > thresh){
            l = m+1;
        }
        else if(fun(m,n,reenter)<=thresh){
            if(m < standard){
                standard = m;
            }
            else{}
            r = m-1;
        }
        else{}
    }
}

int main(){
    ll n, t, i, ans;
    scanf("%lld %lld",&n,&t);
    ll travel[strlim];
    ll reenter[strlim];
    reenter[0] = 0;
    a=strlim;
    reenter[n-1] = 0;
    i=1;
    while(i<=n-1){
        scanf("%lld",&travel[i]);
        i++;
    }
    i=1;
    while(i<n-1){
        scanf("%lld",&reenter[i]);
        i++;
    }
    binarysearch(1, n-1, t, reenter, n);
    ans = standard < lim ? travel[standard] : n-1;
    i=standard+1;
    while(i<n){
            if(travel[i] < ans){
                ans = travel[i];
            }
        i++;
    }
    printf("%lld", ans);
}
