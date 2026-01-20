#ifndef _BFS_H_
#define _BFS_H_

#include <utility>
#include "Graph.h"
#include <vector>
#include "event.h"

using namespace std;

class BFS { 
    public: 
    BFS(); //constructor 

    vector<int> traverse(const Graph& graph, int start, EventRecord& recorder);

    private: 
    vector<bool> visited; 
    vector<int> discovery;


};


#endif