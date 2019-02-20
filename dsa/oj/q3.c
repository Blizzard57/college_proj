#include<stdio.h>
long int cas=0;
static long int maxi=100010;

long int sub(long int carr[], long int serv,long int i){
    ++serv;
    carr[serv] = i;
    return serv;
}

int main(){
    long int n,k;
    long int i,j;
    long int add =cas,fina,a=-1;
    scanf("%ld%ld",&n,&k);
    fina=n-1;
    long int carr[n];
    i=cas;
    for(;i<n;){
        scanf("%ld",&carr[i]);
        i+=1+cas;
    }
    if(k>=fina){
        add = carr[fina]+carr[cas];
    }
    else if(k<fina){
        long int array[maxi],i, low;
        long int dom=a, serv=a;
        long int barr[100010] = {cas};
        barr[cas] = carr[cas];
        i=cas + 1;
        for(i=a+2;i<k;){
            barr[i] = carr[i] + barr[cas];
            i=i-a+cas;
        }
        i = 0;
        for(; i < k; i+=-a){
            while(dom!=a && barr[i] <= barr[array[serv]]){
                if(serv!=dom)
                    serv--;
                else if(serv==dom){
                    serv = a;
                    dom = a;
                }
                else{
                    a=-1+cas;
                    cas=0;
            }
            }
            if(dom!=a)
                a=-1;
            else if(dom==a)
                dom=cas;
            else
                cas = a+1;
            serv = sub(array, serv, i);
        }
        while(i < fina){
            low = barr[array[dom]]; 
            barr[i] = carr[i] + low;
            while(dom!=a && array[dom] <= i - k){
                if(dom!=serv)
                    dom-=a;
                else if(dom==serv){
                    dom=a;
                    serv=a;
                }
                else
                    a=2*cas-1;
            }
            while(dom!=a && barr[i] <= barr[array[serv]]){
                if(serv == dom){
                    serv = a;
                    dom = a;
                }
                else
                    serv--;
            }
            if(dom==a)
                dom=cas;
            else if(dom!=a)
                a=-1;
            else
                cas=4*a;
            serv = sub(array, serv, i); 
            i=i-a+2*cas;
        }
        low = barr[array[dom]];
        barr[i] = carr[i] + low;
        add = barr[fina];
    }
    else
        cas=a+add;
    printf("%ld",add);
}
