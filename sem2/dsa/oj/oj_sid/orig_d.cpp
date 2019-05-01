#include<bits/stdc++.h>
using namespace std;
vector<pair<int ,int >>g[1000000+5];
long long int val[1000000+5],arr[1000000+5],iter;
bool check[1000000+5];
priority_queue <pair<int,int>, vector<pair<int ,int > >, greater<pair<int,int>> > q;
void combine(long long int l ,long long int k,long long int r);
void merge(long long int l,long long int r){
        long long int k1;
        if(l<r){
                k1=(l+r)>>1;
                merge(l,k1);
                merge(k1+1,r);
                combine(l,k1,r);
        }
        return;
}
void combine(long long int l,long long int k,long long int r){
        long long int q1,i,w,j,p;
        q1=k+1;
        w=r;
        i=l;
        j=k;
        p=l;
        for(;i<=j||q1<=w;){
                if(j<i)
                {arr[p++]=val[q1++];}
                else if(q1>w)
                {arr[p++]=val[i++];}
                else if(val[i]<=val[q1])
                {arr[p++]=val[i++];}
                else
                {arr[p++]=val[q1++];}
        }
        for( i=l;i<=r;i++)
        {val[i]=arr[i];}
        return;
}

void mst(long long int sour ){
while(q.size()!=0){
   iter=q.top().second;
		check[iter]=true;
                q.pop();
                for(unsigned int i=0;i<g[iter].size();i++){
                        if(check[g[iter][i].first]==false&&val[g[iter][i].first]>g[iter][i].second){
             
			      	val[g[iter][i].first]=g[iter][i].second;
               
				q.push({ val[g[iter][i].first], g[iter][i].first});             
		       }
                         
                }
}

}
int main(){
long long int n,m,K;
scanf("%lld%lld%lld",&n,&m,&K);
for(int i=0;i<m;i++){
int a,b,c;
	scanf("%d%d%d",&a,&b,&c);
if(a!=b){
g[a].push_back({b,c});
g[b].push_back({a,c});
}
}
for(int i=0;i<n+3;i++){
val[i]=INT_MAX;
//val[i]-=10;
}


/*for(int i=1;i<=n;i++){
for(int j=0;j<g[i].size();j++){
printf("%d ",g[i][j]);
}
printf("\n");
}*/

int sour;
sour=1;
q.push({0,sour});
val[sour]=0;
//check[sour]=true;
mst(sour);
merge(1,n);

long long int sum=0;
//for(int i=1;i<=n;i++)
//printf("%d ",val[i]);
for(int i=2;i<=n;i++){
	if(val[i]!=INT_MAX) {
		sum+=val[i];
	}else{
	printf("%d\n",-1);
	return 0;
	}

}
long long int ans=0;
for(int i=n;i>1;i--){
if(sum>K){
//	printf("   %dsum\n",sum);
sum-=val[i];
sum+=1;
ans++;

}
}
if(sum<=K)
printf("%lld\n",ans);
else 
printf("-1\n");
return 0;
}

