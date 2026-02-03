//
// Created by Ning Shu on 2026-01-21.
//

#include "../persistence/databasePersistence.h"
#include <sqlite3.h>
#include "../export/JsonExporter.h"
#include "Graph.h"
#include "EventLog.h"
#include  <iostream>

int main() {
    sqlite3 *database;
    sqlite3_open(
 "/Users/ningshu/Downloads/PROJECTS/tree/Tree-Algorithm-Simulations/trees.db",
    &database);

    //clean the tables
    //graph
    sqlite3_exec(database, "DELETE FROM steps; ", nullptr, nullptr, nullptr);
    sqlite3_exec(database, "DELETE FROM runs; ", nullptr, nullptr, nullptr);
    sqlite3_exec(database, "DELETE FROM edges; ", nullptr, nullptr, nullptr);
    sqlite3_exec(database, "DELETE FROM graphs; ", nullptr, nullptr, nullptr);

    databasePersistence persistence(database);

    Graph g = Graph("one", 3, false);
    g.addEdge(0,1,5);
    g.addEdge(1,2,3);

    int graphId = persistence.saveGraphwithEdges(g);

    EventLog log(Algorithm::BFS, graphId); //initialize event log
    log.record(Algorithm::BFS, Action::DISCOVERY_EDGE, 0, 1, 5);
    log.record(Algorithm::BFS, Action::VISIT_NODE, -1, 0);
    log.record(Algorithm::BFS, Action::VISIT_NODE, -1, 2);
    log.record(Algorithm::BFS, Action::ADD_TO_TREE, 0, 1, 5);
    log.record(Algorithm::BFS, Action::ADD_TO_TREE, 1, 2, 3);

    int runId = persistence.saveRun(graphId, log);
    std::cout << "runId = " << runId << std::endl;

    JsonExporter exporter(database);
    exporter.exportGraph(graphId);
    exporter.exportEvents(runId);

    sqlite3_close(database);

}