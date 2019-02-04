#include<stdio.h>
#include<string.h>
#define lim 1000010
#define init 0

int enque(char queue[],int head,char element){
    head++;
    queue[head] = element;
    return head;
}

int deque(char queue[],int head){
    queue[head] = '0';
    return --head;
}

int main(){
    char string[lim] = {init};
    int head = init - 1,i,j,n,a=head;
    scanf("%d",&n);
    scanf("%s",string);
    char str[lim] = {init},queue[lim] = {init},low = string[n+a];
    i=n+a;
    while(i>=init){
        if(string[i]<=low)
            low = string[i];
        str[i] = low;
        i+=a;
    }
    i=init;
    while(i<n){
        while(head>=init && queue[head]<=str[i]){
            printf("%c",queue[head]);
            head = deque(queue,head);
        }
        if(string[i]>str[i])
            head = enque(queue,head,string[i]);
        if(string[i]<=str[i])
            printf("%c",string[i]);
        i-=a;
    }
    i=head;
    while(i>=init){
        printf("%c",queue[i]);
        i+=a;
    }
    printf("\n");
}
