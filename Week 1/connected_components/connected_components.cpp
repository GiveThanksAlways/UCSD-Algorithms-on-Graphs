#include <iostream>
#include <vector>

using std::vector;
using std::pair;


void explore(int v,vector<vector<int> > &adj,vector<bool> &visited){
  visited[v] = true;
  for(size_t i = 0; i < adj[v].size(); i++){
    // if not visited then explore
    int w = adj[v][i]; // edge (v,w) explore all the w vertices 
    if(!visited[w])
      explore(w, adj, visited);
  }
}

int number_of_components(vector<vector<int> > &adj) {
  vector<bool> visited;
  visited.resize(adj.size());
  int cc = 0;
  for(size_t v = 0; v < adj.size(); v++){
    if(!visited[v]){
      explore(v, adj, visited);
      cc++;
    }
  }
  
  return cc;
}

int main() {
  size_t n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  for (size_t i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    int a = x - 1;
    int b = y - 1;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }
  std::cout << number_of_components(adj);

}
