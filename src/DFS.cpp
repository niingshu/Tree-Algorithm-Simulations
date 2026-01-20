#include "DFS.h"
#include <stack>
#include <stdexcept>
#include "event.h"

//constructor 
DFS::DFS() = default;

vector<int> DFS::traverse(const Graph& graph, int start, EventRecord& recorder) {
    if (start < 0 || start >= graph.getSize()) 
        throw out_of_range("Vertex input out of range. Please revise");

    //clear the list for visited and discovery if traverse is being called multiple times
    visited.clear();
    visited.assign(graph.getSize(), false);
    discovery.clear();

    stack<int> s; 
    s.push(start);

    while (!s.empty()) {
        int v = s.top();
        s.pop(); //pop it out of the stack 

        if (!visited[v]) { //havent visited yet
            visited[v] = true; 
            discovery.push_back(v);
            recorder.record(Action::VISIT_NODE, v); //VISIT_NODE
        }

        //push the neighbours in, inreverse order: B: A C then C in first then A 
        for (auto it = graph.getNeighbours(v).rbegin(); it != graph.getNeighbours(v).rend(); ++it) {
            int neighbor = it->first;
            int weight = it->second;
            recorder.record (Action::DISCOVERY_EDGE, v, neighbor, weight);

            if (!visited[neighbor]) { //if havent visited then push, if not skip
                s.push(neighbor);
                recorder.record(Action::ADD_TO_TREE, v, neighbor, weight);
            } else {
                recorder.record(Action::RELAX_EDGE, v, neighbor, weight);
            }
        }
    }

    return discovery;
}