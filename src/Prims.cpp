#include "Prims.h"
#include <stdexcept>
#include <queue>
#include <tuple> 
#include <functional> //to change it into min heap 
#include <vector> 

//constructor 
Prims::Prims() {};

//spanning tree from initially one vertex
//repeatedly choose the minimum-weight edge from a vertex to a vertex 
vector<tuple<int, int, int>> Prims::traverse(const Graph& graph, int start) {
    if (start < 0 || start >= graph.getSize()) { 
        throw out_of_range("Vertex input out of range. Please revise");
    }

    visited.assign(graph.getSize(), false);
    mst.clear();
    priority_queue<tuple<int,int,int>, vector<tuple<int,int,int>>, greater<tuple<int,int,int>>> prQ; //tuple of (weight, u, v)

    for (auto [neigh, weight]: graph.getNeigbours(start)) {
        prQ.push({weight, neigh, start});
    }
    visited[start] = true; 

    while (!prQ.empty() && mst.size() < graph.getSize() - 1) {
        auto [weight, u, v] = prQ.top(); //from u to v
        prQ.pop(); 

        if (!visited[u]) { //if neighbour is not visited
            mst.push_back(make_tuple(u, v, weight));
            visited[u] = true; 
        }

        //push the next ones in 
        for (auto [neigh, w]: graph.getNeigbours(u)) {
            prQ.push({w, neigh, u});
        }
    }

    return mst;

}