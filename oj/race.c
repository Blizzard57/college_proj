#include<stdio.h>
long long int speed[100010];
long long int start[100010];
long long int n, k, th;
long long int push(long long int arr[], long long int back,long long int i){
    back++;
    arr[back] = i;
    return back;
}

long long int fun(long long int time){
    long long int slide[100010];
    long long int i; long long int max0; long long int top=-1, back=-1; 
    long long int sum0=0;
    long long int hello[100010]={0};
    for(i=0;i<n;i++){
        hello[i] = start[i] +(speed[i]*time);
    }
    for(i = 0; i < k; i++){
        while(top>=0 && hello[i] >= hello[slide[back]]){
            if(back == top){
                back = -1;
                top = -1;
            }
            else
                back--;
        }
        if(top<0){
            top=0;
        }
        back = push(slide, back, i);
    }

    for(i=k ; i<n; i++){
        max0 = hello[slide[top]]; 
        sum0 = sum0 + max0; 
            while(top>=0 && slide[top] < i - k+1){
                if(top==back){
                    top=-1;
                    back=-1;
                }
                else
                    top++;
            }

        while(top>=0 && hello[i] >= hello[slide[back]]){
            if(back == top){
                back = -1;
                top = -1;
            }
            else
                back--;
        }

        if(top<0){
            top=0;
        }

        back = push(slide, back, i);    

    }
    max0 = hello[slide[top]];
    sum0 = sum0 + max0; 
    return sum0;
}




int main(){
    long long int i,j, time=0;
    scanf("%lld",&n);
    scanf("%lld",&k);
    scanf("%lld",&th);
    long long int sum0;
    long long int resource, mid, l=1, r=1000000000;
    for(i=0;i<n;i++){
        scanf("%lld",&start[i]);
    }

    for(i=0;i<n;i++){
        scanf("%lld",&speed[i]);
    }
    sum0 = fun (0);
    if(sum0>th){
        time = 0;
    }
    else if (sum0 == th){
        time = 1;
    }
    else{
        while(r>=l){
            mid = l + (r-l)/2;
            resource = fun(mid);
            long long int tmp = fun(mid-1);
            if(resource == th){
                time = mid+1;
                break;
            }
            else if(resource < th){
                l = mid+1;
            }
            else{
                if(tmp <= th){
                    time = mid;
                    break;
                }
                else{
                    r=mid-1;
                }
            }
        }
    }

    printf("%lld", time);
}
