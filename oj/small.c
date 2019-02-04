#include<stdio.h>
//#include<string.h>

int push(char stack[],int head,char element){
    stack[++head] = element;
    return head;
}

int pop(char stack[],int head){
 stack[head] = '0';
    head--;
    return head;
}

int main(){
char arr[1000010] = {0};
int n;
scanf("%d",&n);
scanf("%s",arr);
// n = strlen(arr);
char low[1000010] = {0};
char stack[1000010] = {0};
int head = -1;
int i,j;
char min = arr[n-1];
for(i=n-1;i>=0;i--){
    if(arr[i]<=min){
        min = arr[i];
        
    }
    
    low[i] = min;
}

//for(i=0;i<n;i++){
  //    printf("%c",low[i]);
 // }

//printf("\n");

for(i=0;i<n;i++){
 
    
    while(head>=0 && stack[head]<=low[i]){
          printf("%c",stack[head]);
            head = pop(stack,head);
    }
    if(arr[i]>low[i]){
        head = push(stack,head,arr[i]);
    }

   if(arr[i]<=low[i]){
printf("%c",arr[i]);
    }
}


for(i=head;i>=0;i--){
    printf("%c",stack[i]);
}
printf("\n");
}
