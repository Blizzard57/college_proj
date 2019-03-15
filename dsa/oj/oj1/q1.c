#include<stdio.h>
char pos[100001];
int main(){
    int n,na=0,nc=0;
    char c;
    scanf("%d",&n);
    scanf("%s",pos);
    if(n%2!=0)
        printf("-1\n");
    else{
        for(int i=0;i<n;i++){
            if(pos[i]=='A')
                na++;
            else if(pos[i]=='C'){
                if(na!=0)
                    na--;
                else
                    nc++;
            }
        }
        printf("%d\n",(na+nc)/2 + na%2);
    }
}
