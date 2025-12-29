#include "Graph.h"

//constructor 
Graph::Graph(int vertices, bool directed) 
    : adjList(vertices), isDirected(directed)
{
    if (vertices <= 0) {
        throw invalid_argument("Number of vertices must be positive");
    }
}

//add an edge between u and v 
void Graph::addEdge(int u, int v) { 
}

const vector<int>& Graph::getNeigbours(int u) const {

}

int Graph::getSize() const {

}