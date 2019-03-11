#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long int lu;
typedef long long int ll;
typedef long double ld;
#define v vector<ll>
#define vv vector<v>
#define vu vector<lu>
#define vld vector<ld>
#define vs vector<string>

void swap(ll *x, ll *y) {
    ll temp = *x;
    *x = *y;
    *y = temp;
}

ll mod_inverse(ll a, ll p) {
    ll y = 1;
    ll temp = p - 2;
    ll x = a;
    while (temp) {
        if (temp % 2 == 1) {
            y *= x;
            y = y % p;
        }
        x = ((x % p) * (x % p)) % p;
        x = x % p;
        temp /= 2;
    }
    return y;
}

ll ind(ll arr[],ll x,ll n)
{
    ll low=0;
    ll high=n-1;
    ll mid=(low+high)/2;
    while(low<=high)
    {
        mid= (low+high)/2;
        if(arr[mid] == x){
            if(mid == 0 || x!= arr[mid-1]){
                return mid;
            }
            else{
                high = mid-1;
            }
        }
        else if(x > arr[mid]){
            low = mid+1;
        }
        else if(x < arr[mid]){
            high = mid-1;
        }
    }
    return -1;
}


ll arr_inc[200000]={0};
ll arr_dec[200000]={0};
ll tree_inc[600000]={0};
ll tree_dec[600000]={0};
ll dp_inc[200000]={0};
ll dp_dec[200000]={0};

void update(ll arr[],ll segTree[],ll start,ll end,ll index,ll val,ll cur_node){
    if(start == end){
        arr[index] = val;
        segTree[cur_node] = arr[index];
        return;
    }

    ll mid = (start+end)/2;
    if(index <= mid)
    {
        update(arr,segTree,start,mid,index,val,2*cur_node+1);
    }
    else{
        update(arr,segTree,mid+1,end,index,val,2*cur_node+2);
    }
    segTree[cur_node] = segTree[cur_node*2 + 1] + segTree[2*cur_node+2];
}

ll query(ll segTree[],ll start,ll end,ll l,ll r,ll cur_node){
    if(l<=start && r>=end){
        return segTree[cur_node];
    }
    if(l > end || r< start){
        return 0;
    }

    ll mid = (start+end)/2;
    ll x = query(segTree,start,mid,l,r,2*cur_node+1);
    ll y = query(segTree,mid+1,end,l,r,2*cur_node+2);

    return (x+y)%(1000000007);
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    lu n;
    map<ll ,ll> m_inc;
    map<ll ,ll> m_dec;
    cin >> n;
    ll a[n],b[n];
    for(ll i=0;i<n;i++)
    {
        cin >> a[i];
        b[i] = a[i];
    }

    sort(b,b+n);

    for(ll i=0;i<n;i++)
    {
        ll y = m_inc[a[i]];
        ll idx = ind(b,a[i],n);
        if(idx+y == 0){
            update(arr_inc,tree_inc,0,n-1+y,0,1,0);
            dp_inc[i] = 1;
        }
        else{
            ll x = query(tree_inc,0,n-1,0,idx-1+y,0);
			x = x%(1000000007);
            update(arr_inc,tree_inc,0,n-1,idx+y,x+1,0);
            dp_inc[i] = x+1;
        }
        m_inc[a[i]]++;
    }

    for(ll i=n-1;i>=0;i--)
    {
        ll x = 0;
        ll y = m_dec[a[i]];
        ll z = m_inc[a[i]];
        ll idx = ind(b,a[i],n);
        if(idx == 0){
            x =0;
        }
        else {
            x = query(tree_dec, 0, n - 1, 0, idx-1, 0);
			x = x%(1000000007);
        }
        ll c = query(tree_dec,0,n-1,0,idx+y,0);
        update(arr_dec,tree_dec,0,n-1,idx+y,c+1,0);
        dp_dec[i] = x+1;
        m_dec[a[i]]++;
    }

    ll sum = 0;

//    for(ll i=0;i<n;i++){
//        cout << dp_inc[i] << " " <<dp_dec[i] <<endl;
//    }

    for(ll i=0;i<n;i++)
    {
        ll x = dp_inc[i];
        ll y = dp_dec[i];
        sum += (x*y);
		sum = sum%(1000000007);
    }

    cout << sum;
    return 0;
}
