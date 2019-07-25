#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using std::vector;
using std::queue;

void printVector(vector<int> &vector1){
  std:: cout << "vector1 is ";
  for(int i = 0; i < vector1.size(); i++){
    std::cout << vector1[i] << " ";
  }
  std::cout << std::endl;
}

int BFS(vector<vector<int> > &G, int s, int t, int edges){
  vector<int> dist;
  vector<int> prev;
  dist.resize(edges);
  prev.resize(edges);
  int infinity = edges+1;// can't have a path longer than the number of edges
  std::fill(dist.begin(),dist.end(),infinity);// fill with inifinity
  std::fill(prev.begin(),prev.end(),NULL);
  
  dist[s] = 0;
  queue<int> Q;
  Q.push(s);

  while(!Q.empty()){
    int u = Q.front();
    Q.pop();
    
    for(int i=0; i < G[u].size(); i ++){
      int v = G[u][i];
      if(dist[v] == infinity){
        Q.push(v);// push vertex location
        dist[v] = dist[u] + 1;
        prev[v] = u;
      }
    }
  }
  // check if the node was visited
  if(dist[t] == infinity)
    return -1;
  // if not visited, return the level count
  int u = t;
  int counter = 0;
  while( u != s && counter < edges){
    u = prev[u];
    counter++;
  }

  return counter;
}

int distance(vector<vector<int> > &adj, int s, int t, int edges) {
  
  return BFS(adj, s, t, edges);
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
  int s, t;
  std::cin >> s >> t;
  s--, t--;
  std::cout << distance(adj, s, t, n);
}
