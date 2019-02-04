#include<stdio.h>
int one=1,zero=0;
long long int top=-1;
long long int stack[100000];
void push(long long int v){
	top++;
	stack[top]=v;
}
long long int empty(){
	return top==-one;
}
long long int topp(){
	if(top!=-one)
		return stack[top];
}

long long int pop(){
	if(top==-one)
		return -one;
	return stack[top--];}

long long int max(long long int x,long long int y){
	return (x>y)?x:y;
}

long long int histo(long long int a[],long long int n){

	 long long int max_area=zero,area=zero;
	 long long int i=zero;
	while(i<n){
		
		if(empty()||a[topp()]<=a[i]){
			push(i++);
		}

		else{
			long long int top_val = a[topp()]; 
            pop(); 
            area = top_val * i; 
  
            if (!empty()) 
           	    area = top_val * (i - topp()-one ); 
            
            max_area = max(area, max_area); 
        } 
    } 
  
    while (!empty()) 
    { 
        long long int top_val = a[topp()]; 
        pop(); 
        area = top_val * i; 
        if (!empty()) 
            area = top_val * (i - topp() -one ); 
  
        max_area = max(area, max_area); 
    } 
    return max_area;
}

int main(){
	
		long long int m,n;
		char temp;
		scanf("%lld %lld",&m,&n);
		long long int grid[m][n];
		for(long long int i=zero;i<m;i++){
			for(long long int j=zero;j<n;j++){
				scanf("%c",&temp);
				if(temp=='T'){
					grid[i][j]=one;
				}
				else if(temp =='E'){
					grid[i][j]=zero;
				}
				else{
					j--;
				}
			}
		}

		

		long long int max_area=zero;

		for(long long int i=zero;i<m;i++){
			for(long long int j=zero;j<n;j++){
				if(i!=zero&&grid[i][j]){
					grid[i][j]+=grid[i-one][j];
				}	
			}	
			max_area=max(max_area,histo(grid[i],n));
		}

		printf("%lld\n",max_area );
	}
