#include "BFS.h"
#include <queue>
#include <stdexcept>

//constructor 
BFS::BFS() = default;

//runs and returns the vector of discovery tree 
vector<int> BFS::traverse(const Graph& graph, int start, EventRecord& recorder) {
    if (start < 0 || start >= graph.getSize())
        throw out_of_range("Vertex input out of range. Please revise");

    //clear the list for visited and discovery if traverse is being called multiple times
    visited.clear();
    visited.assign(graph.getSize(), false);
    discovery.clear();

    queue<int> q;
    visited[start] = true; //marked as visited
    discovery.push_back(start);
    q.push(start);
    recorder.record(Algorithm::BFS, Action::VISIT_NODE, start);

    while (!q.empty()) { //while the queue is not empty
        int source = q.front();
        for (auto [neigh, weight]: graph.getNeighbours(source)) {  //get the neighbour in the front
            if (visited[neigh] == false) { //if hasn't been visited
                visited[neigh] = true;
                recorder.record(Algorithm::BFS, Action::VISIT_NODE, -1, neigh); //node being visit
                discovery.push_back(neigh); //discovery tree
                recorder.record(Algorithm::BFS, Action::DISCOVERY_EDGE, source, neigh, weight);
                recorder.record(Algorithm::BFS, Action::ADD_TO_TREE, source, neigh, weight);
                q.push(neigh);
            } else {
                recorder.record(Algorithm::BFS, Action::RELAX_EDGE, source, neigh, weight);
            }
        }
        q.pop();
    }

    return discovery;

}