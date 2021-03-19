import Pyro4
from collections import defaultdict

# Global Variables
graphList = {}

class Graph:
    def __init__(self,nodes):
        self.V = nodes
        self.graph = []
        self.adj = [[] for i in range(nodes)]

     
    def addEdge(self, u, v, w):
        self.graph.append([u, v, w])
        self.adj[u].append(v)
        self.adj[v].append(u)

    def DFSUtil(self, temp, v, visited):
        visited[v] = True
        temp.append(v)
 
        for i in self.adj[v]:
            if visited[i] == False:
                temp = self.DFSUtil(temp, i, visited)

        return temp
 
    def find(self, parent, i):
        if parent[i] == i:
            return i
        return self.find(parent, parent[i])
 
    def union(self, parent, rank, x, y):
        xroot = self.find(parent, x)
        yroot = self.find(parent, y)
 
        if rank[xroot] < rank[yroot]:
            parent[xroot] = yroot
        elif rank[xroot] > rank[yroot]:
            parent[yroot] = xroot
        else:
            parent[yroot] = xroot
            rank[xroot] += 1

    def isNotConnected(self):
        visited = []
        cc = []
        for i in range(self.V):
            visited.append(False)
        for v in range(self.V):
            if visited[v] == False:
                temp = []
                cc.append(self.DFSUtil(temp, v, visited))
        
        if len(cc) > 1:
            return True
        return False
 
    def KruskalMST(self):
        if len(self.graph) == 0:
            return -1

        if self.isNotConnected():
            return -1

        result = []
        i = 0
        e = 0
 
        self.graph =  sorted(self.graph, key=lambda item: item[2])
        parent, rank = [], []

        for node in range(self.V):
            parent.append(node)
            rank.append(0)
     
        while e < self.V-1:	
            u, v, w =  self.graph[i]
            i += 1
            x = self.find(parent, u)
            y = self.find(parent, v)
 
            if x != y:
                e += 1  
                result.append([u, v, w])
                self.union(parent, rank, x, y)

        ans = 0
        for u, v, weight in result:
            ans = ans + weight
        
        if len(result) > 0:
            return ans
        return -1

@Pyro4.expose
@Pyro4.behavior(instance_mode="single")
class GraphActions(object):
    def addGraph(self,identifier,n):
        graphList[identifier] = Graph(n)

    def appendVertex(self,identifier,u,v,w):
        graphList[identifier].addEdge(u,v,w)
    
    def getMst(self,identifier):
        return graphList[identifier].KruskalMST()


def main():
    Pyro4.Daemon.serveSimple(
            {
                GraphActions: "example.graphactions"
            },
            ns = False)

if __name__=="__main__":
    main()