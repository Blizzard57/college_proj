#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<math.h>

/*int compare (const void * a, const void * b)
{
  return ( *(int*)a - *(int*)b );
}*/
int gcd(int a,int b){
    if(b==0) return a;
    else gcd(b,a%b);
    return -1;
}

using namespace std;
int main(){
    std::ios::sync_with_stdio(false);
    int n,d,e;
    cin>>n>>d>>e;
    int inta,intb,ans;
    inta = gcd(d,5*e);
    intb = n/inta;
    ans = n - (intb * inta);
    cout<<n << " "<< inta << " " << intb << " " << ans;   
    return 0;    
}