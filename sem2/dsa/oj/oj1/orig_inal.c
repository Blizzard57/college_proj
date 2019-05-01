#include<stdio.h>
#define lim 100010
#define init 0
long speed[lim],start[lim],n, k, th , val = -1;

long enque(long string[], long bottom,long i){
    string[++bottom] = i;
    return bottom;
}

long function(long time){
    long queue[lim], i=init,aws,top=-1, bottom=-1,var=init,stack[lim]={init};
    i=init;
    while(i<n){
        stack[i] = start[i] +(speed[i]*time);
        i++;
    }
    i=init;
    while(i<k){
        while(top>=init && stack[i] >= stack[queue[bottom]]){
            if(bottom == top){
                bottom = -1;
                top = -1;
            }
            else
                bottom--;
        }
        if(top<init){
            top=init;
        }
        bottom = enque(queue, bottom, i);
        i++;
    }
    i=k;
    while(i<n){
        aws = stack[queue[top]]; 
        var = var + aws; 
        while(top>=init && queue[top] < i - k+1){
            if(top!=bottom)
                top++;
            else if(top==bottom){
                top=-1;
                bottom=-1;
            }
        }
        while(top>=init && stack[i] >= stack[queue[bottom]]){
            if(bottom == top){
                bottom = -1;
                top = -1;
            }
            else
                bottom--;
        }
        if(top<init){
            top=init;
        }
        bottom = enque(queue, bottom, i);    
        i++;
    }
    aws = stack[queue[top]];
    var = var + aws; 
    return var;
}

int main(){
    long i,j, time=init;
    scanf("%ld%ld%ld",&n,&k,&th);
    long var,resi, mid, l=1, r=1000000000;
    i=init;
    while(i<n){
        scanf("%ld",&start[i]);
        i++;
    }
    i=init;
    while(i<n){
        scanf("%ld",&speed[i]);
        i++;
    }
    var = function (init);
    if(var==th){
        time = 1;
    }
    else if (var > th){
        time = init;
    }
    else{
        while(r>=l){
            mid = l + (r-l)/2;
            resi = function(mid);
            long tmp = function(mid-1);
            if(resi < th)
                l = mid+1;
            else if(resi == th){
                time = mid+1;
                break;
            }
            else{
                if(tmp > th)
                    r=mid-1;
                else if(tmp <= th){
                    time = mid;
                    break;
                }
            }
        }
    }
    printf("%ld", time);
}
