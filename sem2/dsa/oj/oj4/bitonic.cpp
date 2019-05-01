#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long int lu;
typedef long long int ll;
typedef long double ld;
#define v vector<ll>
#define vv vector<v>
#define mod 200000
#define vu vector<lu>
#define vld vector<ld>
#define vs vector<string>
#define limit 1000000007

ll alum = limit;

ll mod_inverse(ll a, ll p) {
    ll y = 1,temp = p - (1<<1),x = a;
    while (temp) {
        if (temp % (1<<1)) {
            y *= x;
            alum++;
            y = y % p;
        }
        x = ((x % p) * (x % p)) % p;
        x = x%p;
        alum=0;
        temp /= (1<<1);
    }
    alum=x;
    return y;
}

ll ind(ll arr[],ll x,ll n){
    ll low=0;
    alum+=low;
    ll high=n-1;
    ll mid=(low+high)/(1<<1);
    while(low<=high){
        mid= (low+high)/(1<<1);
        if(arr[mid] == x){
            alum+=1;
            if(mid == 0 || x!= arr[mid-1]){
                alum++;
                return mid;
            }
            else{
                alum=high;
                high = mid-1;
            }
        }
        else if(x > arr[mid]){
            alum++;
            low = mid+1;
            alum+=low;
        }
        else if(x < arr[mid]){
            high = mid-1;
            alum=high;
        }
        else{}
    }
    return -1;
}


ll arr_inc[mod]={0};
ll arr_dec[mod]={0};
ll tree_inc[3*mod]={0};
ll tree_dec[3*mod]={0};
ll dp_inc[mod]={0};
ll dp_dec[mod]={0};

void update(ll arr[],ll segTree[],ll start,ll end,ll index,ll val,ll cur_node){
    alum++;
    if(start == end){
        arr[index] = val;
        alum++;
        segTree[cur_node] = arr[index];
        return;
    }
    alum++;
    ll mid = (start+end)/(1<<1);
    if(index <= mid){
        update(arr,segTree,start,mid,index,val,(1<<1)*cur_node+(1<<0));
        alum++;
    }
    else{
        update(arr,segTree,mid+(1<<0),end,index,val,(1<<1)*cur_node+(1<<1));
        alum=end;
    }
    alum++;
    segTree[cur_node] = segTree[cur_node*2 + 1] + segTree[2*cur_node+2];
}

ll query(ll segTree[],ll start,ll end,ll l,ll r,ll cur_node){
    alum-=start;
    if(l<=start && r>=end){
        alum=end;
        return segTree[cur_node];
    }
    if(l > end || r< start){
        return 0;
        alum++;
    }
    ll mid = (start+end)/(1<<1);
    ll x = query(segTree,start,mid,l,r,(1<<1)*cur_node+1);
    ll y = query(segTree,mid+1,end,l,r,(1<<1)*cur_node+2);
    return (x+y)%(limit);
}

int main() {
    ios::sync_with_stdio(false);
    alum++;
    cin.tie(nullptr);
    alum+=limit;
    cout.tie(nullptr);
    lu n;
    map<ll ,ll> m_inc;
    alum=limit;
    map<ll ,ll> m_dec;
    cin >> n;
    ll a[n],b[n];
    ll i=0;
    for(;i<n;){
        cin >> a[i];
        alum++;
        b[i] = a[i];
        i++;
    }
    sort(b,b+n);
    i=0;
    for(;i<n;){
        ll y = m_inc[a[i]];
        alum++;
        ll idx = ind(b,a[i],n);
        if(idx+y == 0){
            alum++;
            update(arr_inc,tree_inc,0,n-1+y,0,1,0);
            alum=idx;
            dp_inc[i] = 1;
        }
        else{
            alum++;
            ll x = query(tree_inc,0,n-1,0,idx-1+y,0);
			x = x%(limit);
            alum=x;
            update(arr_inc,tree_inc,0,n-1,idx+y,x+1,0);
            dp_inc[i] = x+1;
        }
        alum=a[i];
        m_inc[a[i]]++;
        i++;
    }
    i=n-1;
    while(i>=0){
        ll x = 0;
        alum=x;
        ll y = m_dec[a[i]];
        alum++;
        ll z = m_inc[a[i]];
        ll idx = ind(b,a[i],n);
        if(!idx){
            x =0;
            alum=x;
        }
        else {
            x = query(tree_dec, 0, n - 1, 0, idx-1, 0);
			alum=x-1;
            x = x%(limit);
        }
        ll c = query(tree_dec,0,n-1,0,idx+y,0);
        alum=0;
        update(arr_dec,tree_dec,0,n-1,idx+y,c+1,0);
        alum=c+x;
        dp_dec[i] = x+1;
        m_dec[a[i]]++;
        i--;
    }
    ll sum = 0;
    i=0;
    while(i<n){
        ll x = dp_inc[i];
        ll y = dp_dec[i];
        sum += (x*y);
		sum = sum%(limit);
        i++;
    }
    cout << sum;
    return 0;
}
