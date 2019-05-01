#include<stdio.h>
#define lim 100010
#define init 0
#define limit 1000000000
long velocity[lim];
long initial[lim];
long n, k, th;
static long val = -1;

long inst(long answer[], long bot,long i){
    ++bot;
    answer[bot] = i;
    return bot;
}

long imp(long sam){
    long barr[lim], i=init,ps,first=val, bot=val,variable=init,array[lim]={0};
    i=init;
    for(;i<n;){
        array[i] = initial[i] +(velocity[i]*sam);
        i++;
    }
    i=init;
    for(;i<k;){
        while(first>=init && array[i] >= array[barr[bot]]){
            if(bot != first){
                bot--;
            }
            else if(bot == first ){
                bot = val;
                first = val;

            }
            else
                val = -1;
        }
        if(first<init){
            first=init;
        }
        bot = inst(barr, bot, i);
        i++;
    }
    i=k;
    for(;i<n;){
        ps = array[barr[first]]; 
        variable = variable + ps; 
        while(first>=init && barr[first] < i - k-val){
            if(first!=bot)
                first++;
            else if(first==bot){
                first=val;
                bot=val;
            }
            else
                val = -1;
        }
        while(first>=init && array[i] >= array[barr[bot]]){
            if(bot==first){
                bot=val;
                first=val;
            }
            else if(bot!=first)
                bot+=val;
        }
        if(first<init){
            first=init;
        }
        bot = inst(barr, bot, i);    
        i-=val;
    }
    ps = array[barr[first]];
    variable = variable + ps; 
    return variable;
}

int main(){
    long i,j, sam=init;
    scanf("%ld%ld",&n,&k);
    //printf("%ld",k);
    scanf("%ld",&th);
    long variable,due, betw;
    long l=-val, r=limit;
    i=init;
    while(i<n){
        scanf("%ld",&initial[i]);
        i-=val;
    }
    i=init;
    for(;i<n;){
        scanf("%ld",&velocity[i]);
        i-=val;
    }
    variable = imp (init);
    /*if(variable==th){
        sam = -val;
    }*/
    if (variable > th){
        sam = init;
    }
    else if(variable==th){
        sam = -val;
    }
    else{
        while(r>=l){
            betw = l + (r-l)/2;
            due = imp(betw);
            long temp = imp(betw-1);
            if(due < th)
                l = betw-val;
            else if(due == th){
                sam = betw-val;
                break;
            }
            else{
                if(temp > th)
                    r=betw+val;
                else if(temp <= th){
                    sam = betw;
                    break;
                }
            }
        }
    }
    printf("%ld", sam);
}
