#include "Dijkstras.h"
#include <stdexcept>
#include <queue> 
#include <functional> //to change it into min heap
#include "event.h"

Dijkstras::Dijkstras() {}; //constructor 

int Dijkstras::find(int v) { //v is the vertex, from v to i 
    for (int i = 0; i < track.size(); i++) {
        if (track[i] == v) return i; //from v to i
    }
    return -1;
}

vector<int> Dijkstras::traverse(const Graph& graph, int start, EventRecord& recorder) {
    int size = graph.getSize();
    if (start < 0 || start >= size)
        throw out_of_range("Vertex input out of range. Please revise");

    track.assign(size, -1);
    distance.assign(size, INT_MAX);
    visited.assign(size, false);

    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> prQ; //pair(current distance, vertex)
    distance[start] = 0;
    prQ.push({0, start});

    while(!prQ.empty()) { //check and push in 
        auto [dist, u] = prQ.top();
        prQ.pop();

        if (dist > distance[u]) continue; //move to the next iteration
        if (visited[u]) continue; //stop the current iteration and jump to the next one

        visited[u] = true;
        recorder.record(Algorithm::DIJKSTRA, Action::VISIT_NODE, -1, u);

        if (track[u] != -1) {
            recorder.record(Algorithm::DIJKSTRA, Action::ADD_TO_TREE, track[u], u,
                distance[u] - distance[track[u]]);
        }

        for (auto [adjVer, weight]: graph.getNeighbours(u)) {
                recorder.record(Algorithm::DIJKSTRA, Action::DISCOVERY_EDGE, u, adjVer, weight);

                if (!visited[adjVer] && distance[u] + weight < distance[adjVer]) { 
                    distance[adjVer] = distance[u] + weight; 
                    track[adjVer] = u; //track path from u is to adjVer
                    prQ.push({distance[adjVer], adjVer});
                } else {
                    recorder.record(Algorithm::DIJKSTRA, Action::RELAX_EDGE, u, adjVer, weight);
                }

        }


    }

    return track;
    
}