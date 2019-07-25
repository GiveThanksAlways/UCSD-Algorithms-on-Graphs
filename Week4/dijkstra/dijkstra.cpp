#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using std::vector;
using std::queue;
using std::pair;
using std::priority_queue;

using namespace std;

void printVector(vector<int> &vector1){
  std:: cout << "vector1 is ";
  for(int i = 0; i < vector1.size(); i++){
    std::cout << vector1[i] << " ";
  }
  std::cout << std::endl;
}

int distance(vector<vector<int> > &adj, vector<vector<int> > &cost, int s, int t, int n) {
  //std::pair <int,int> product1;
  typedef std::pair<int, int> daPairs; // first is dist value  and second is the vectice value 1st,2nd,3rd, etc.
  std::priority_queue< daPairs, vector<daPairs> , greater<daPairs> > pq; // makes a min heap instead or max heap defined by the daPairs.first element 

  vector<int> dist;
  vector<int> prev;
  dist.resize(n);
  prev.resize(n);
  int  maximum = std::numeric_limits<int>::max();
  int inf = std::numeric_limits<int>::infinity();
  for(int i=0; i < n; i++){
    dist[i] = maximum;
    prev[i] = 0;
  }
  dist[s] = 0;

  pq.push(make_pair(0, s));


  while(!pq.empty()){
    daPairs p1 = pq.top();
    int u = pq.top().second;
    pq.pop();
    // check for old non updated vertices in the priority queue 
    //cout << (p1.first != dist[u]) << endl;
    while(p1.first != dist[u] && !pq.empty()){
      // not the updated one
      p1 = pq.top();
      u = pq.top().second;
      pq.pop();
    }

    for(size_t i = 0; i < adj[u].size(); i++){
      int v = adj[u][i];
      int w = cost[u][i];
      if(dist[v] > dist[u] + w){
        dist[v] = dist[u] + w;
        prev[v] = u;
        pq.push(make_pair(dist[v],v));// just make a new pair and check the dist[v] value to see if we throw it away when we pop at the beginning of the loop

      }
    } 
  }
  if(dist[t] == maximum)
    return -1;
  
  return dist[t];
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
  int s, t;
  std::cin >> s >> t;
  s--, t--;
  std::cout << distance(adj, cost, s, t, n);
}
