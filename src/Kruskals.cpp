#include "Kruskals.h"
#include <stdexcept>
#include <queue>
#include <tuple> 
#include <functional> //to change it into min heap 

//constructor 
Kruskals::Kruskals() {};

int Kruskals::find(int u) {
    if (parents[u] != u) {
        parents[u] = find(parents[u]); //recursion to find the parent
    } 
    return parents[u];
}

void Kruskals::unionSet(int u, int v) {
    int parentU = find(u);
    int parentV = find(v);

    if (parentU != parentV) {
        if (rank[parentU] > rank[parentV]) { //union on the higher tree
            parents[parentV] = parentU; 
        } else if (rank[parentV] > rank[parentU]) {
            parents[parentU] = parentV; 
        } else { 
            parents[parentV] = parentU; 
            rank[parentU]++;
        }
    }
}

vector<tuple<int, int, int>> Kruskals::traverse(const Graph& graph) {
    parents.resize(graph.getSize());
    for (int i = 0; i < graph.getSize(); i++) {
        parents[i] = i;
    }
    rank.assign(graph.getSize(), 0);
    mst.clear();
    priority_queue<tuple<int,int,int>, vector<tuple<int,int,int>>, greater<tuple<int,int,int>>> prQ; //tuple of (weight, u, v)

    int size = graph.getSize();
    for (int i = 0; i < size; i++) {
        for (auto [neigh, weight]: graph.getNeigbours(i)) {
            if (i < neigh) {
                prQ.push({weight, i, neigh});
            }
        }
    } //push all in 

    while (!prQ.empty() && mst.size() < graph.getSize() - 1) {
        auto [weight, u, v] = prQ.top(); //from u to v -> u is parent 
        prQ.pop();

        if (find(u) != find(v)) { //different parents
            unionSet(u, v);
            mst.push_back(make_tuple(u, v, weight));
        }
    }

    return mst;
    
}