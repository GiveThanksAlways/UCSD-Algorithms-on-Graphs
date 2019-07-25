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


vector<int> DFS(vector<vector<int> > &adj) {
  vector<bool> visited;
  vector<int> postOrder;
  vector<int> preOrder;
  visited.resize(adj.size());
  preOrder.resize(adj.size());
  postOrder.resize(adj.size());
  //int cc = 0;
  int clock = 0;
  for(size_t v = 0; v < adj.size(); v++){
    if(!visited[v]){
      clock = explore(v, adj, visited, clock,preOrder,postOrder);
      //cc++;
    }
  }
  
  return postOrder;
}

void printVector(vector<pair<int,int> > &vector1){
  for(int i = 0; i < vector1.size(); i++){
    std::cout << vector1[i].first << " ";
  }
  std::cout << std::endl;
}

bool compare(const pair<int,int> &a, const pair<int,int> &b){
  return (a.first > b.first);
} 


vector<pair<int,int> > toposort(vector<vector<int> > adj) {
  //vector<int> used(adj.size(), 0);
  vector<int> order;
  vector<int> ans;
  ans.resize(adj.size());
  // sort in reverse order
  order = DFS(adj);
  std::pair <int,int> foo;
  foo = std::make_pair (10,20);
  vector< pair <int,int> > answer;
  for(int i = 0; i < order.size(); i++){
    answer.push_back(std::make_pair(order[i],i));
  }
  //printVector(answer);
  sort(answer.begin(),answer.end(),compare);
  //printVector(answer);

  return answer;
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
  vector< pair<int,int> > order = toposort(adj);
  for (size_t i = 0; i < order.size(); i++) {
    std::cout << order[i].second + 1 << " ";
  }
}
