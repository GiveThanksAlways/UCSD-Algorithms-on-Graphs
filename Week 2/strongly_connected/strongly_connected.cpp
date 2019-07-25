#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::pair;


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

void printVector(vector<int> &vector1){
  for(int i = 0; i < vector1.size(); i++){
    std::cout << vector1[i] << " ";
  }
  std::cout << std::endl;
}

bool compare(const pair<int,int> &a, const pair<int,int> &b){
  return (a.first > b.first);
} 

vector<int> DFS(vector<vector<int> > &adj) {
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
  
  return postOrder;
}

vector<int> toposort(vector<vector<int> > adj) {
  //vector<int> used(adj.size(), 0);
  vector<int> order;
  // sort in reverse order
  order = DFS(adj);
  std::sort(order.begin(),order.end());
  return order;
}

void exploreBasic(int v,vector<vector<int> > &adj,vector<bool> &visited){
  visited[v] = true;
  for(size_t i = 0; i < adj[v].size(); i++){
    // if not visited then explore
    int w = adj[v][i]; // edge (v,w) explore all the w vertices 
    if(!visited[w])
      exploreBasic(w, adj, visited);
  }
}

int number_of_strongly_connected_components(vector<vector<int> > &adj,vector<vector<int> > &adjR) {
  int result = 0;
  vector<int> postOrderR;
  vector<bool> visited;
  visited.resize(adj.size());
  // DFS on reversed directed graph
  postOrderR = DFS(adjR);
  //printVector(postOrderR);
  vector< pair <int,int> > postorderPairs;
  for(int i = 0; i < postOrderR.size(); i++){
    postorderPairs.push_back(std::make_pair(postOrderR[i],i));
  }
  //printVector(postorderPairs);
  sort(postorderPairs.begin(),postorderPairs.end(),compare);
  //printVector(postorderPairs);

  int SCC = 0;
  for(size_t i = 0; i < postorderPairs.size(); i++){
    int v = postorderPairs[i].second;
    if(!visited[v]){
      exploreBasic(v, adj, visited);
      //mark visited vertices as a new SCC 
      SCC++;
    }
  }

  return SCC;
}

int main() {
  size_t n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  vector<vector<int> > adjR(n, vector<int>());
  for (size_t i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    int a = x-1;
    int b = y-1;
    adj[a].push_back(b);
    adjR[b].push_back(a);// reversed directions
  }
  std::cout << number_of_strongly_connected_components(adj,adjR);
}
