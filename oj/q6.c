#include<stdio.h>
#define lim 1005
long int string[lim][lim];

long int valima(long int function[],long int n){
    long int back[n],front=-1,cas,xap;
    void deque(long int i){
        front++;
        back[front]=i;
    }
    void enque(){
        front--;
    }
    long int val=0,vol;
    deque(0);
    long int i=1;
    while(i < n+2) {
        if(function[i]<function[back[front]]){
            cas = back[front-1];
            xap = i;
            vol = function[back[front]] * (xap - cas -1);
            if(vol>val)
                val=vol;
            enque();
        }
        else{
            deque(i);
            i++;
        }
    }   
    return val;
}

int main(){
    long int n,m,i,j,val=0,xa;
    scanf("%ld%ld",&m,&n);
    char temp='b';
    i=0;
    while(i<m){
        string[i][0] = -5; 
        string[i][n+1] = -1; 
        j=1;
        while(j<=n){
            while(temp != 'E' && temp!= 'T'){
                scanf("%c",&temp);  
            }
            if( temp=='T' && i>0 ) 
                string[i][j]=string[i-1][j]+1;
            else 
                if(temp == 'T' && i==0) 
                    string[0][j] = 1;
                else 
                    string[i][j]=0;
            temp='b';
        j++;
        }
    i++;
    }
    i=0;
    while(i<m){
        xa = valima(string[i],n+2);
        if(xa>val) val=xa;
        i++;
    }
    printf("%ld\n",val);
    return 0;
}
