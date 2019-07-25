#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using std::vector;
using std::queue;

bool BFS(vector<vector<int> > &adj, int s, int vertices, vector<int> &color, vector<bool> &visited,
  queue<int> &Q){
  
  int red = 0;// can't have a path longer than the number of vertices
  int blue = 1;
  int noColor = 2;
  
  color[s] = red;
  Q.push(s);
  
  while(!Q.empty()){
    int u = Q.front();
    Q.pop();
    visited[u] = true;

    for(int i=0; i < adj[u].size(); i ++){
      int v = adj[u][i];
      // check if visited
      if(color[v] == noColor){
        Q.push(v);// push vertex location
        if(color[u] == red)
          color[v] = blue;
        else
          color[v] = red;

      }else if(color[v] == color[u]){
        return false;
      }
    }
  }

  return true;
}

int bipartite(vector<vector<int> > &adj,int vertices) {
  vector<int> color;
  vector<bool> visited;
  color.resize(vertices);
  visited.resize(vertices);

  int noColor = 2;
  queue<int> Q;
  std::fill(color.begin(),color.end(),noColor);// fill with inifinity

  bool pass = true;
  for(int j = 0; j < visited.size(); j++){
    bool pass = true;
    if(!visited[j])
      pass = BFS(adj,j,vertices,color,visited,Q);
      if(!pass)
        return false;
  }

  return true;
}

int main() {
  int n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  for (int i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
    adj[y - 1].push_back(x - 1);
  }
  std::cout << bipartite(adj,n);
}
