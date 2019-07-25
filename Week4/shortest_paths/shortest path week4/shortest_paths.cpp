#include <iostream>
#include <unordered_set>
#include <vector>
#include <limits>
#include <queue>
#include <math.h> 

using std::vector;
using std::queue;
using std::pair;
using std::priority_queue;
using std::cout;
using std::endl;

static const long long maximum = std::numeric_limits<long long>::max();

void printVector(vector<long long> &vector1){
  //double infinity = std::numeric_limits<double>::infinity();
  //cout << maximum << endl;
  for(int i = 0; i < vector1.size(); i++){
    //cout << std::isfinite(vector1[1]);
    //cout << "vector1[i]: " << vector1[i] << std::endl;
    if (vector1[i] ==  maximum) {
      std::cout << "*\n";
    } else if (vector1[i] == -maximum) {
      std::cout << "-\n";
    } else {
      std::cout << vector1[i] << "\n";
    }
    
  }
  
}

void BFS(vector<vector<int> > &adj, vector<vector<int> > &cost,int s, vector<bool> &visited, vector<long long>& dist,vector<float>& prev, bool& updated, bool go, int& findAll ){
  //double  maximum = std::numeric_limits<double>::max();
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
      if(!BFSvisited[v])// stop infinite loops don't keep looping
        Q.push(v);
      //std::cout << "w: " << w << std::endl;
      
      if(dist[v] > dist[u] + w ){
          //std::cout << "v=" << v+1 << ", u="<<u+1<< ", dist[v]=" <<dist[v]<< ", dist[u]="<< dist[u] <<std::endl;
          dist[v] = dist[u] + w;
          updated = true;
          if(go){
            dist[v] = -maximum;
            findAll = v;
          }
            
        }
    }
    
  }// end of while 

}

void BFSnINF(vector<vector<int> > &adj,int s, vector<long long>& dist ){

  //double maximum = std::numeric_limits<double>::max();
  vector<bool> BFSvisited;
  BFSvisited.resize(adj.size());

  std::queue<int> Q;
  Q.push(s);

  while(!Q.empty()){
    int u = Q.front();
    BFSvisited[u] = true;
    Q.pop();

    for(size_t i=0; i < adj[u].size(); i++){
      int v = adj[u][i];
      if(!BFSvisited[v])
        Q.push(v);
      
      dist[v] = -maximum;
      }
    
    
  }// end of while 

}

void Relax(vector<vector<int> > &adj, vector<vector<int> > &cost,vector<long long> &dist, int u,vector<bool> &reachableLookUp,vector<int> &reachable,bool& updated){

  for(size_t i=0; i < adj[u].size(); i++){
    int v = adj[u][i]; 
    int w = cost[u][i];
    //std::cout << "dist[v]: " << dist[u] << std::endl;
    if(dist[v] > dist[u] + w && dist[u] != maximum){
        dist[v] = dist[u] + w;// update dist
        updated = true; 
    }
    if(!reachableLookUp[v]){
          reachable.push_back(v);// now apart of reachable nodes 
          reachableLookUp[v] = true;// we mark that we know it is there 
        }
  }
}

void RelaxSaveUpdatedV(vector<vector<int> > &adj, vector<vector<int> > &cost,vector<long long> &dist, int u,vector<bool> &reachableLookUp,vector<int> &reachable, vector<int>& updatedList){

  for(size_t i=0; i < adj[u].size(); i++){
    int v = adj[u][i];
    int w = cost[u][i];
    if(dist[v] > dist[u] + w && dist[u] != maximum){
        dist[v] = dist[u] + w;// update dist
        updatedList.push_back(v);// insert node in updated list 
    }
    
  }
}

void BellmanFord(vector<vector<int> > &adj, vector<vector<int> > &cost,int s, vector<bool> &visited,vector<int> &reachable){
  vector<bool>reachableLookUp;
  vector<long long> dist;
  dist.resize(adj.size());
  reachableLookUp.resize(adj.size());
  //double  maximum = std::numeric_limits<double>::max();
  for(int i=0; i < adj.size(); i ++){dist[i]=maximum;}// intialize arrays to inf

  dist[s] = 0;
  visited[s] = true;
  reachable.push_back(s);
  for(int i=0; i < adj[s].size(); i++){
    reachable.push_back(adj[s][i]);
    reachableLookUp[adj[s][i]] = true;
  }
  
  bool updated = false;
  bool negativeCycles = true;
  for(size_t k =0; k < adj.size()-1; k++){// relax all reachable edges |V|-1 times 
    updated = false;
    for(int i=0; i < reachable.size(); i++){// relax only reachable vertices
      int u = reachable[i];
      Relax(adj, cost, dist, u, reachableLookUp, reachable, updated);
    }
    if(!updated){
      negativeCycles = false;
      break; // no negativeCycles
    } 
  }
  // now BFS on negativeCycles to mark -Inf 
  if(negativeCycles){
    vector<int> updatedList;
    for(int i=0; i < reachable.size(); i++){// relax only reachable vertices
      int u = reachable[i]; 
      RelaxSaveUpdatedV(adj, cost, dist, u, reachableLookUp, reachable, updatedList);
    }
    for(int i=0; i < updatedList.size(); i++){
      int u = updatedList[i];
      if(dist[u] != -maximum)
        BFSnINF(adj, u, dist);
    }
  }

  printVector(dist);

  
}

void shortest_paths(vector<vector<int> > &adj, vector<vector<int> > &cost, int s, vector<long long> &distance, vector<int> &reachable, vector<int> &shortest) {
  /**BellmanFord, and make an if loop to save updated verticies on the last loop of cycle
  mark them as dist of -Inf
  BellmanFord should have all the correct distances set up, the last loop with the last updates should do the trick
  and then just do a BFS on just one of the nodes in the negative cycle 
  */
  vector<bool> visited;
  visited.resize(adj.size());
  BellmanFord(adj, cost, s, visited,reachable);
}

int main() {
  int n, m, s;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  vector<vector<int> > cost(n, vector<int>());
  for (int i = 0; i < m; i++) {
    int x, y, w;
    std::cin >> x >> y >> w;
    adj[x - 1].push_back(y - 1);
    cost[x - 1].push_back(w);
  }
  std::cin >> s;
  s--;
  vector<long long> distance(n, std::numeric_limits<long long>::max());
  vector<int> reachable(n, 0);
  vector<int> shortest(n, 1);
  shortest_paths(adj, cost, s, distance, reachable, shortest);
  /**for (int i = 0; i < n; i++) {
    if (!reachable[i]) {
      std::cout << "*\n";
    } else if (!shortest[i]) {
      std::cout << "-\n";
    } else {
      std::cout << distance[i] << "\n";
    }
  }*/
}
