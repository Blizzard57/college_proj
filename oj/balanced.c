#include<stdio.h>

int push(int stack[],int head,int element){
stack[head] = element;
head = head +1;
return head;
}
int pop(int stack[],int head){
head = head-1;
return head;
}

int main(){
    int n;
    scanf("%d",&n);
    int stack[n];
    int j;
    for(j=0;j<n;j++){
        stack[j]=0;
    }
   
    char arr[n];
            scanf("%s",arr);
    int i,h=0,flag=0,countc=0,counta=0;
    for(i=0;i<n;i++){
       
        
       if(arr[i]=='A'){
         if(flag==0 ||flag ==1){
             flag = 1;
            h = push(stack,h,65);
           }
         if(flag==2){
             h = push(stack,h,65);
         }
               }
        if(arr[i]=='C'){
            if(flag==1){
            h = pop(stack,h);
            flag = 0;
                   }
       
            else{
if(stack[h-1]==65){
    h = pop(stack,h);
}
else{
                h = push(stack,h,67);
                  // printf("hello %d %d %d",countc,counta,h );
}
                    flag=2;                  
     }
        }
   // printf("%d",i);    
    }
//.   printf("head  %d\n",h); 
   
    for(i=0;i<h;i++){

        if(stack[i]==65){
        counta++;
    }
    else{
        countc++;
    }
    }
    
    
    if(n%2!=0){
        printf("-1\n");
    }
    else if(counta==0&&countc==0){
        printf("0\n");
    }
    else{
        if(counta%2==0){
            printf("%d\n",((counta/2)+(countc/2)));

    }
        else{
            printf("%d\n",(((counta+1)/2)+((countc+1)/2)));
}
}
}
