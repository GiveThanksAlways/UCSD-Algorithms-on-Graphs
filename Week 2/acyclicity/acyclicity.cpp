#include <iostream>
#include <vector>

using std::vector;
using std::pair;

void printVector(vector<int> &vector1){
  for(int i = 0; i < vector1.size(); i++){
    std::cout << vector1[i] << " ";
  }
  std::cout << std::endl;
}

int explore(int v,vector<vector<int> > &adj,vector<bool> &visited, int clock,vector<int> &preOrder, vector<int> &postOrder){
  visited[v] = true;
  preOrder[v] = clock;//previsit(v);
  clock++;
  for(size_t i = 0; i < adj[v].size(); i++){
    // if not visited then explore
    int w = adj[v][i]; // edge (v,w) explore all the w vertices 
    if(!visited[w])
      clock = explore(w, adj, visited, clock, preOrder, postOrder);
  }
  postOrder[v] = clock;//postvisit(v);
  clock++;
  return clock;
}


bool DFS(vector<vector<int> > &adj) {
  vector<bool> visited;
  vector<int> postOrder;
  vector<int> preOrder;
  visited.resize(adj.size());
  preOrder.resize(adj.size());
  postOrder.resize(adj.size());
  //int cc = 0; 
  int clock = 1;
  for(size_t v = 0; v < adj.size(); v++){
    if(!visited[v]){
      clock = explore(v, adj, visited, clock,preOrder,postOrder);
      //cc++;
    }
  }
  //printVector(preOrder);
  //printVector(postOrder);
  //std::cout << postOrder[0];
  for(size_t i = 0; i < adj.size(); i++){
    vector<int> u = adj[i];
    // go through each edge u to v 
    for(size_t j = 0; j < u.size(); j++){
      int v = u[j];
      if(postOrder[i] < postOrder[v])
        return true; // failed the theorem
    }
    
  }
  //std::cout << "yo";
  return false;
}

bool acyclic(vector<vector<int> > &adj) {
  
  return DFS(adj);
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
  }
  std::cout << acyclic(adj);
}

