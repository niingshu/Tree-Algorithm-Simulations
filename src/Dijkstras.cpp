#include "Dijkstras.h"
#include <stdexcept>
#include <queue> 
#include <functional> //to change it into min heap 

Dijkstras::Dijkstras() {}; //constructor 

int Dijkstras::find(int v) { //v is the vertex, from v to i 
    for (int i = 0; i < track.size(); i++) {
        if (track[i] == v) return i; //from v to i
    }
}

vector<int> Dijkstras::traverse(const Graph& graph, int start) {
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

        if (!visited[u]) { //if the vertex is not visited
            visited[u] = true; 
            for (auto [adjVer, weight]: graph.getNeigbours(u)) {
                if (!visited[adjVer] && distance[u] + weight < distance[adjVer]) { 
                    distance[adjVer] = distance[u] + weight; 
                    track[adjVer] = u; //track path from u is to adjVer
                    prQ.push({distance[adjVer], adjVer});
                }
            }
        }
    }

    return track;
    
}