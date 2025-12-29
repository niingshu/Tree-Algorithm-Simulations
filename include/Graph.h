#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <utility>
#include <vector>
#include <cmath>

using namespace std;

class Graph {
    public: 
    Graph(int vertices, bool directed = false); //set to undirected graph
    
    void addEdge(int u, int v); //add new edges
    int getNeigbours(int u); //for bfs and dfs 
    int const getSize();

    private: 
    //vertices list, each connect to a list of its adjacent vertices 
    // outter vector is the vertex at index a 
    // adjList[a] is a list of vertices adjacent to u 
    vector<vector<int>> adjList; 
    int numVertices; //size of the graph 
    bool isDirected; //directed or undirected graph
};

#endif