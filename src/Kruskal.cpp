#include "Kruskals.h"
#include <stdexcept>
#include <queue>
#include <tuple> 
#include <functional> //to change it into min heap 
#include <vector> 

//constructor 
Kruskals::Kruskals() {};

vector<tuple<int, int, int>> Kruskals::traverse(const Graph& graph) {
    parents.assign(graph.getSize(), -1);
    rank.clear();
    mst.clear();
    priority_queue<tuple<int,int,int>, vector<tuple<int,int,int>>, greater<tuple<int,int,int>>> prQ; //tuple of (weight, u, v)

    int size = graph.getSize();
    for (int i = 0; i < size; i++) {
        for (auto [neigh, weight]: graph.getNeigbours(i)) {
            prQ.push({weight, i, neigh});
        }
    } //push all in 

    while (!prQ.empty() && mst.size() < graph.getSize() - 1) {
        auto [weight, u, v] = prQ.top(); //from u to v -> u is parent 
        prQ.pop();

        if (parents[u] != parents[v]) {

        }
    }
    
}