#include<bits/stdc++.h>
using namespace std;

int flag=0;

void dfs(int s, vector <vector<int>> &adj,int n,vector <int> &visit){
	int i;
	visit[s]=1;
	for(i=0;i<adj[s].size();i++){
		if(visit[adj[s][i]]==0)
			dfs(adj[s][i],adj,n,visit);
		else  if(visit[adj[s][i]]==1)
			flag=1;
	}
	visit[s]=2;
}

int main(){
	int n,e,p,q;
	cin>>n>>e;
	vector <vector<int>> adj(n,vector<int>(0));
	vector <int> visit(n,0);
    for(int i=0;i<e;i++){
		cin>>p>>q;
		adj[p].push_back(q);
	}
	dfs(0,adj,n,visit);
	if(flag)
        cout << "Cycle exists";
    else 
        cout << "Cycle Does no exist";
}
