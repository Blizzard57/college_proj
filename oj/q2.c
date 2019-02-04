#include<stdio.h>
char s[100001],n[100001],d[100001];
int main(){
    int n,sp=0,np=0,dp=0;
    scanf("%d",&n);
    scanf("%s",s);
    char min='z';
    for(int i=0;i<n;i++){
        if(s[i]<min)
            min=s[i];   
    }  
}   
