#ifndef _DIJKSTRAS_H_
#define _DIJKSTRAS_H_

#include <utility>
#include "Graph.h"
#include <vector>

using namespace std;

class Dijkstras { 
    public: 
    Dijkstras(); //constructor 

    vector<int> traverse(const Graph& graph, int start); 

    private: 
    vector<bool> visited; 
    vector<int> shortest;


};


#endif