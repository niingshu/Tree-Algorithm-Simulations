#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <utility>
#include <vector>
#include <cmath>

using namespace std;

class Graph {
    public: 
    Graph(int vertices, bool directed = false); //set to undirected graph
    
    void addEdge(int u, int v, int weight); //add new edges
    const vector<pair<int,int>>& getNeigbours(int u) const; //for bfs and dfs 
    int getSize() const;

    private: 
    //vertices list, each connect to a list of its adjacent vertices 
    //outter vector is the vertex at index a 
    //adjList[a] is a list of vertices adjacent to u and the weight 
    //update so it takes in weight also 
    vector<vector<pair<int,int>>> adjList; 
    bool isDirected;
    // directed or undirected graph
};

#endif