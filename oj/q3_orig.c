 q3.c

#include<stdio.h>
#define init 0
#define lim 100010
long int function(long int string[], long int bottom,long int i){
    bottom++;
    string[bottom] = i;
    return bottom;
}

//long int fun(long int k, long int n, long int string[]){}

int main(){
    long int n,k,i,j,sum = init,end;
    scanf("%ld%ld",&n,&k);
    end=n-1;
    long int string[n];
    for(i=init;i<n;i++)
        scanf("%ld",&string[i]);
    if(k>=end){
        sum = string[end]+string[init];
    }
    else{
    long int stack[lim];
    long int i, low, front=-1, bottom=-1, queue[lim] = {init};
    queue[init] = string[init];
    for(i=1;i<k;i++)
        queue[i] = string[i] + queue[init];
other

    for(i = init; i < k; i++){
        while(front!=-1 && queue[i] <= queue[stack[bottom]]){
            if(bottom == front){
                bottom = -1;
                front = -1;
            }
            else
                bottom--;
        }
        if(front==-1)
            front=init;
        bottom = function(stack, bottom, i);
    }
    for( ; i < end; i++){
other

        low = queue[stack[front]]; 
        queue[i] = string[i] + low;

        while(front!=-1 && stack[front] <= i - k){
            if(front==bottom){
                front=-1;
                bottom=-1;
            }
            else
                front++;
        }
        while(front!=-1 && queue[i] <= queue[stack[bottom]]){
            if(bottom == front){
                bottom = -1;
                front = -1;
            }
            else
                bottom--;
        }

        if(front==-1){
            front=init;
        }
        bottom = function(stack, bottom, i);    
    }
    low = queue[stack[front]];
        queue[i] = string[i] + low;
    long int ans = queue[end];
    sum = ans;
    }
    printf("%ld",sum);
}


