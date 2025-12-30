#ifndef _PRIMS_H_
#define _PRIMS_H_

#include <utility>
#include "Graph.h"
#include <vector>

using namespace std;

class Prims { 
    public: 
    Prims(); //constructor 

    //u,v,weight. return as a vector of edges 
    vector<tuple<int, int, int>> traverse(const Graph& graph, int start); 

    private: 
    vector<bool> visited; 
    vector<tuple<int, int, int>> mst;


};


#endif