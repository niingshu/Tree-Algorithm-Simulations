#include "Prims.h"
#include <stdexcept>
#include <queue>
#include <tuple> 
#include <functional> //to change it into min heap 
#include <vector>
#include "event.h"

//constructor 
Prims::Prims() {};

//spanning tree from initially one vertex
//repeatedly choose the minimum-weight edge from a vertex to a vertex 
vector<tuple<int, int, int>> Prims::traverse(const Graph& graph, int start, EventRecord& recorder) {
    if (start < 0 || start >= graph.getSize()) { 
        throw out_of_range("Vertex input out of range. Please revise");
    }

    visited.assign(graph.getSize(), false);
    mst.clear();
    priority_queue<
        tuple<int,int,int>,
        vector<tuple<int,int,int>>,
        greater<tuple<int,int,int>>
        > prQ; //tuple of (weight, u, v)

    for (auto [neigh, weight]: graph.getNeighbours(start)) {
        prQ.push({weight, start, neigh});
    }
    visited[start] = true;
    recorder.record(Algorithm::PRIMS, Action::VISIT_NODE, -1, start);

    while (!prQ.empty() && mst.size() < graph.getSize() - 1) {
        auto [weight, u, v] = prQ.top(); //from u to v
        prQ.pop(); 
        recorder.record(Algorithm::PRIMS, Action::DISCOVERY_EDGE, u, v, weight);

        if (visited[v]) {
            recorder.record(Algorithm::PRIMS, Action::RELAX_EDGE, u, v, weight);
            continue;
        }

        mst.push_back(make_tuple(u, v, weight));
        visited[v] = true;
        recorder.record(Algorithm::PRIMS, Action::VISIT_NODE, -1, v);
        recorder.record(Algorithm::PRIMS, Action::ADD_TO_TREE, u, v, weight);

        //push the next ones in 
        for (auto [neigh, w]: graph.getNeighbours(u)) {
            prQ.push({w, v, neigh});
        }
    }

    return mst;

}