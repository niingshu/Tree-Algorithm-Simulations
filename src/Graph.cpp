#include "Graph.h"
#include <stdexcept>

//constructor 
Graph::Graph(int vertices, bool directed) 
    : adjList(vertices), isDirected(directed)
{
    if (vertices <= 0) {
        throw invalid_argument("Number of vertices must be positive");
    }
}

//add an edge between u and v, directed then u->v, undirected add also from v to u
void Graph::addEdge(int u, int v) { 
    if (u < 0 || v < 0 || u >= getSize() || v >= getSize()) {
        throw out_of_range("Vertex input out of range. Please revise");
    }

    adjList[u].push_back(v); //push v back as adjacent vertex with v

    //undirected 
    if (isDirected == 0) {
        adjList[v].push_back(u);
    }

}

const vector<int>& Graph::getNeigbours(int u) const {
    if (u < 0 || u >= getSize()) {
        throw out_of_range("Vertex input out of range. Please revise");
    }

    return adjList[u];
}

//size of the graph
int Graph::getSize() const {
    return adjList.size();
}