#include<stdio.h>
#include<stdlib.h>
#include<iostream>


int min_fn(int x,int y){
    if(x>y) return y;
    return x;
}

using namespace std;
int main(){
    int t,n;
    cin>>t;
    while(t--){
        cin>>n;
        int arr[n];
        int high=0,low=0;
        for(int i=0;i<n;i++){
            cin>>arr[i];
            if(arr[i]>=high){
                low=high;
                high=arr[i];
                //cout<<low<<" "<<high<<" "<<"\n";
            }
            else if(low<=high && low<=arr[i]){
                low=arr[i];
            }
        }
        //cout<<low<<" ";
        //for(int i=0;i<n;i++)
            //cout<<arr[i]<<" ";
        int ans = min_fn(low-1,n-2);
        //cout<<ans<<" ";
        if(ans>0) cout<<ans<<"\n";
        else cout<<0<<"\n";
    }
    return 0;    
}