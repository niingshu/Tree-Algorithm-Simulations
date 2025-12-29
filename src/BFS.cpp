#include "BFS.h"
#include <queue>
#include <stdexcept>

//constructor 
BFS::BFS() {}; 

//runs and returns the vector of discovery tree 
vector<int> BFS::traverse(const Graph& graph, int start) {
    if (start < 0 || start >= graph.getSize()) 
        throw out_of_range("Vertex input out of range. Please revise");

    //clear the list for visited and discory if traverse is being called multiple times 
    visited.clear();
    visited.assign(graph.getSize(), false);
    discovery.clear();

    queue<int> q; 
    visited[start] = true; //marked as visited
    discovery.push_back(start);
    q.push(start);

    while (!q.empty()) { //while the queue is not empty
        for (auto neigh: graph.getNeigbours(q.front())) {  //get the neighbour in the front 
            if (visited[neigh] == false) { //if hasnt been visited
            visited[neigh] = true; 
            discovery.push_back(neigh); //discovery tree
            q.push(neigh);
            }
        }
        q.pop();
    }

    return discovery;

}