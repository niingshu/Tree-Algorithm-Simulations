#include "DFS.h"
#include <stack>
#include <stdexcept>

//constructor 
DFS::DFS() {};

vector<int> DFS::traverse(const Graph& graph, int start) {
    if (start < 0 || start >= graph.getSize()) 
        throw out_of_range("Vertex input out of range. Please revise");

    //clear the list for visited and discory if traverse is being called multiple times 
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
        }

        //push the neighbours in, inreverse order: B: A C then C in first then A 
        for (auto it = graph.getNeigbours(v).rbegin(); it != graph.getNeigbours(v).rend(); ++it) {
            if (!visited[it->first]) { //if havent visited then push, if not skip
                s.push(it->first);
            }
        }
    }

    return discovery;
}