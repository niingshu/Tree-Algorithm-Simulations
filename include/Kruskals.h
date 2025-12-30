#ifndef _KRUSKALS_H_
#define _KRUSKALS_H_

#include <utility>
#include "Graph.h"
#include <vector>

using namespace std;

class Kruskals { 
    public: 
    Kruskals(); //constructor 

    //u,v,weight. return as a vector of edges 
    vector<tuple<int, int, int>> traverse(const Graph& graph); 

    private: 
    //disjoint-set: parents for find operations, path compression
    vector<int> parents; 
    vector<int> rank;
    vector<tuple<int, int, int>> mst;

};


#endif