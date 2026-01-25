//
// Created by Ning Shu on 2026-01-24.
//

#ifndef TREE_ALGORITHM_SIMULATIONS_JSONEXPORTER_H
#define TREE_ALGORITHM_SIMULATIONS_JSONEXPORTER_H

#include <sqlite3.h>

using namespace std;

class JsonExporter {
    sqlite3* database;

    public:
    JsonExporter(sqlite3* database);

    void exportGraph(int graphId);
    void exportEvents(int runId);
};

#endif //TREE_ALGORITHM_SIMULATIONS_JSONEXPORTER_H