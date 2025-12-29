#ifndef _PRIMS_H_
#define _PRIMS_H_

#include <utility>
#include "Graph.h"
#include <vector>

using namespace std;

class Prims { 
    public: 
    Prims(); //constructor 

    vector<int> traverse(const Graph& graph, int start); 

    private: 
    vector<bool> visited; 
    vector<int> mst;


};


#endif