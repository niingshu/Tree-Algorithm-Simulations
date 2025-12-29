#ifndef _DFS_H_
#define _DFS_H_

#include <utility>
#include "Graph.h"
#include <vector>

using namespace std;

class DFS { 
    public: 
    DFS(); //constructor 

    vector<int> traverse(const Graph& graph, int start); 

    private: 
    vector<bool> visited; 
    vector<int> discovery;


};


#endif