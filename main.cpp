#include "include/Graph.h"
#include "include/BFS.h"
#include "include/DFS.h"
#include "include/Prims.h"
#include "include/Kruskals.h"
#include "include/Dijkstras.h"
#include <tuple>
#include <iostream>

int main() {
    //build graph 
    Graph g = Graph(6, false);
    g.addEdge(0, 1, 4); 
    g.addEdge(1, 2, 8);
    g.addEdge(2, 3, 4);
    g.addEdge(3, 4, 10); 
    g.addEdge(4, 5, 7);
    g.addEdge(0, 2, 5); 
    g.addEdge(0, 5, 2); 
    g.addEdge(2, 4, 6);
    g.addEdge(2, 5, 11);
    g.addEdge(1, 3, 3);
    g.addEdge(3, 5, 2);

    //runs algorithm 
    Kruskals algo; 
    vector<tuple<int, int, int>> path = algo.traverse(g); //weight, u, v

    //print path 
    cout << "print path: " << endl;
    for (auto [u, v, weight]: path) {
        cout << "vertex: " << u << " vertex:  " << v << " weight: " << weight << endl;
    }

    return 0;

}