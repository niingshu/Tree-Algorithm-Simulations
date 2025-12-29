#ifndef _BFS_H_
#define _BFS_H_

#include <utility>
#include "Graph.h"
#include <vector>

using namespace std;

class BFS { 
    public: 
    BFS(); //constructor 

    vector<int> traverse(const Graph& graph, int start); 

    private: 
    vector<bool> visited; 
    vector<int> discovery;


};


#endif