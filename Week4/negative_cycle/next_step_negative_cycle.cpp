#include <iostream>
#include <vector>
#include <limits>
#include <queue>

using std::vector;

void printVector(vector<float> &vector1){
  std:: cout << "vector1 is ";
  for(int i = 0; i < vector1.size(); i++){
    std::cout << vector1[i] << " ";
  }
  std::cout << std::endl;
}

void Relax(vector<vector<int> > &adj, vector<vector<int> > &cost,vector<double> &dist, vector<double> &prev, int u, vector<bool> &visited, bool &updated){

  for(size_t i=0; i < adj[u].size(); i++){
    int v = adj[u][i];
    int w = cost[u][i];
    if(dist[v] > dist[u] + w){
        dist[v] = dist[u] + w;
        prev[v] = u;
        visited[v] = true;
        updated = true;
    }
  }
}

void BFS(vector<vector<int> > &adj, vector<vector<int> > &cost,int s, vector<bool> &visited, vector<float>& dist,vector<float>& prev, bool& updated){
  vector<bool> BFSvisited;
  BFSvisited.resize(adj.size());

  std::queue<int> Q;
  Q.push(s);

  while(!Q.empty()){
    int u = Q.front();
    visited[u] = true;
    BFSvisited[u] = true;
    //std::cout << "u: "<< u+1 << std::endl;
    Q.pop();

    for(size_t i=0; i < adj[u].size(); i++){
      int v = adj[u][i];
      int w = cost[u][i];
      if(!BFSvisited[v])
        Q.push(v);
      //std::cout << "w: " << w << std::endl;
      if(dist[v] > dist[u] + w){
          //std::cout << "v=" << v+1 << ", u="<<u+1<< ", dist[v]=" <<dist[v]<< ", dist[u]="<< dist[u] <<std::endl;
          dist[v] = dist[u] + w;
          prev[v] = u;
          updated = true;
        }
    }
    
  }

}

bool BellmanFord(vector<vector<int> > &adj, vector<vector<int> > &cost,int s, vector<bool> &visited){
  
  vector<float> dist, prev;
  dist.resize(adj.size());
  prev.resize(adj.size());
  
  // intialize arrays to 0
  double  maximum = std::numeric_limits<double>::max();
  for(int i=0; i < adj.size(); i ++){
    dist[i]=maximum;
    prev[i]=0;
  }

  dist[s] = 0;
  //bool updated = false;
  //BFS(adj,cost,s,visited,dist,prev,updated);
  
  for(size_t k =0; k < adj.size(); k++){// keep going through BFS and relaxing each edge 
    bool updated = false;

    BFS(adj,cost,s,visited,dist,prev,updated);
    //printVector(dist);

    if(!updated)
      return false;
  }
  return true;// we hit the negative cycle because we had an update each time
  
}

int negative_cycle(vector<vector<int> > &adj, vector<vector<int> > &cost) {
  vector<bool> visited;
  visited.resize(adj.size());

  //return BellmanFord(adj, cost, 0, visited);
  for(int s =0; s < adj.size(); s++){// do BellmanFord using each vertex as a starting point. Skip nodes that were already visited 

    if(!visited[s])
      if(BellmanFord(adj, cost, s, visited))
        return true;

  }

  return false;
}

int main() {
  int n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  vector<vector<int> > cost(n, vector<int>());
  for (int i = 0; i < m; i++) {
    int x, y, w;
    std::cin >> x >> y >> w;
    adj[x - 1].push_back(y - 1);
    cost[x - 1].push_back(w);
  }
  std::cout << negative_cycle(adj, cost);
}
