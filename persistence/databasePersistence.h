//
// Created by Ning Shu on 2026-01-20.
//

#ifndef TREE_ALGORITHM_SIMULATIONS_DATABASEPERSISTENCE_H
#define TREE_ALGORITHM_SIMULATIONS_DATABASEPERSISTENCE_H

#pragma once
#include <sqlite3.h>
#include "EventLog.h"

using namespace std;

class DatabasePersistence {
    public: //do what -> what being called in main.cpp
    explicit DatabasePersistence(sqlite3* database);
    //tell the compiler to only explicitly use this constructor when being called

    int saveRun(int graphId, const EventLog& event_log);
    //returns run_id

    private: //remember what -> keeping the connection with database
    sqlite3* database;

    int insertRun(int graphId, Algorithm algorithm);
    //insert a row into runs table, return the run_id
    void insertEvent(int graphId, const Event& event);
    //insert many rows into the steps table, update on db
};



#endif //TREE_ALGORITHM_SIMULATIONS_DATABASEPERSISTENCE_H