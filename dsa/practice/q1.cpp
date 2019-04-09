#include<bits/stdc++.h>
using namespace std;

/*void dfs(int s,vector<vector<int>> &adj,int n){
  vector<int> visit[n];
//visit[s]='g';
for(int i=0;i<adj[s].size;i++){
if(visit[adj[s][i]]!='g' && visit[adj[s][i]]!='b')
dfs(adj[s][i],adj,n);
else if(visit[adj[s][i]]=='b')
cout << "Loop Exists";
}
visit[s]='b';
}*/

int main(){
    int n,e,p,q;
    cin >> n >> e;
    vector <vector <int>> adj(n,vector <int>(0));
    for (int i=0;i<e;i++){
        cin >> p >> q;
        adj[p].push_back(q);
    }
    queue <int> bfs;
    vector <bool> visit(n,false);
    int sh;
    //cout << "Enter Source  :";
    //cin >> sh;
    for(int i=0;i<n;i++){
        if(visit[i]==false){
            sh = i;
            bfs.push(sh);
            while(!bfs.empty()){
                int node = bfs.front();
                bfs.pop();
                visit[node]=true;
                for(int i=0;i<adj[node].size();i++){
                    if(!visit[adj[node][i]])
                        bfs.push(adj[node][i]);
                    visit[adj[node][i]]=true;
                }
                cout << node << " ";
            }
        }
    }
    return 0;
}
