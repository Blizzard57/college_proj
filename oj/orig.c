#include<stdio.h>

int arr[1005][1005];
int histmax(int hist[],int n){
    int st[n];
    int top=-1,li,ri;

    void push(int i){
        top++;
        st[top]=i;
    }
    void pop(){
        top--;
    }
    int max=0,temparea;

    push(0);
    int i=1;

    while(i < n+2) {
        if(hist[i]>=hist[st[top]]) {
            push(i);
            i++;
        }

        else {
            li = st[top-1];
            ri = i;
            temparea = hist[st[top]] * (ri - li -1);
            max = temparea>max ? temparea : max ;
            pop();
        }
    }   

    return max;

}
int main(){
    int n,m;
    scanf("%d",&m);
    scanf("%d",&n);
    char temp='b';
    for(int i=0; i<m ; i++){
        arr[i][0] = -5; 
        arr[i][n+1] = -1; 
        for(int j=1; j<=n ; j++){
            while(temp != 'E' && temp!= 'T'){
                scanf("%c",&temp);  
            }
            if( temp=='T' && i>0 ) arr[i][j]=arr[i-1][j]+1;
            else 
                if(temp == 'T' && i==0) arr[0][j] = 1;
                else arr[i][j]=0;
            temp='b';
        }
    }
    int max=0,tmax;
    for(int i=0;i<m;i++){
        tmax = histmax(arr[i],n+2);
        //printf("%d\n",tmax);
        if(tmax>max) max=tmax;
    }

    printf("%d\n",max);

    return 0;
}
