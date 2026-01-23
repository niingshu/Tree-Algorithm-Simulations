//
// Created by Ning Shu on 2026-01-20.
//

#ifndef TREE_ALGORITHM_SIMULATIONS_DATABASEPERSISTENCE_H
#define TREE_ALGORITHM_SIMULATIONS_DATABASEPERSISTENCE_H

#pragma once
#include <sqlite3.h>
#include "EventLog.h"
#include "Graph.h"

using namespace std;

class databasePersistence {
    public: //do what -> what being called in main.cpp
    explicit databasePersistence(sqlite3* database);
    //tell the compiler to only explicitly use this constructor when being called

    int saveRun(int graphId, const EventLog& event_log);
    //returns run_id

    //save the graph to db
    int saveGraphwithEdges(const Graph& graph);

    private: //remember what -> keeping the connection with database
    sqlite3* database;

    int insertRun(int graphId, Algorithm algorithm);
    //insert a row into runs table, return the run_id
    void insertEvent(int runId, const Event& event);
    //insert many rows into the steps table, update on db
    void insertEdge(int graphId, int u, int v, int weight);
    int insertGraph(const Graph& graph);
};



#endif //TREE_ALGORITHM_SIMULATIONS_DATABASEPERSISTENCE_H