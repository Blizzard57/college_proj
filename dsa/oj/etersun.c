#include<stdio.h>

long long int push(long long int arr[], long long int back,long long int i){
    back++;
    arr[back] = i;
    return back;
}

long long int fun(long long int k, long long int n, long long int arr[]){
    long long int slide[100010];
    long long int i; long long int min0; long long int top=-1, back=-1; long long int hello[100010] = {0};
    
    hello[0] = arr[0];
    for(i=1;i<k;i++){
        hello[i] = arr[i] + hello[0];
    }
    
    for(i = 0; i < k; i++){
        while(top!=-1 && hello[i] <= hello[slide[back]]){
            if(back == top){
                back = -1;
                top = -1;
            }
            else
                back--;
        }
        if(top==-1)
            top=0;
        back = push(slide, back, i);
    }
/////////////////////////////////////////////////////////////////

    for( ; i < n-1; i++){
        min0 = hello[slide[top]]; 
        hello[i] = arr[i] + min0;

        while(top!=-1 && slide[top] <= i - k){
            if(top==back){
                top=-1;
                back=-1;
            }
            else
                top++;
        }

        while(top!=-1 && hello[i] <= hello[slide[back]]){
            if(back == top){
                back = -1;
                top = -1;
            }
            else
                back--;
        }

        if(top==-1){
            top=0;
        }

        back = push(slide, back, i);    
    
    }

///////////////////////////////////////////////////////////////////    
//for( i=0; i<n; i++){
  //  printf("%lld\t", slide[i]);
//}
        
    min0 = hello[slide[top]];
  //      printf("min0: %lld \n", min0);
        hello[i] = arr[i] + min0;

    long long int ans = hello[n-1];
//for( i=0; i<n; i++){
 //   printf("%lld\t", hello[i]);
//}

    return ans;

}

int main(){
    long long int n,k,i,j;
    scanf("%lld",&n);
    scanf("%lld",&k);
    long long int arr[n];
    for(i=0;i<n;i++){
        scanf("%lld",&arr[i]);
    }

    long long int sum = 0;

    if(k>=n-1){
        sum = arr[n-1]+arr[0];
    }
    else{
        sum = fun(k, n, arr);
    }
    printf("%lld",sum);
}
