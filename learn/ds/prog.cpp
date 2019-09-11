#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<math.h>

int compare (const void * a, const void * b)
{
  return ( *(int*)a - *(int*)b );
}

using namespace std;
int main(){
    int k,n;
    cin>>n>>k;
    int arr[n];
    for(int i=0;i<n;i++)
        cin>>arr[i];
    qsort(arr,n,sizeof(int),compare);
    int flag=0;
    for(int i=0;i<n-1;i++){
        if(arr[i]==arr[i+1]){
            arr[i] = -1;
            flag++;
        }
    }
    //qsort(arr,n,sizeof(int),compare);
    //for(int i=flag;i<n;i++)
        //cout<<arr[i]<<" ";
    //cout<<"\n"<<n-flag<<" ";    
    int ans = 8*k/n;
    int fin_ans = pow(2,ans);
    cout<<fin_ans<<"\n";
    return 0;    
}