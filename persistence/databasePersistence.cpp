//
// Created by Ning Shu on 2026-01-20.
//

#include "databasePersistence.h"
#include "EventLog.h"
#include "Graph.h"
#include <vector>
#include <tuple>

//constructor
databasePersistence::databasePersistence(sqlite3 *database)
    : database(database) {}

int databasePersistence::insertGraph(const Graph& graph) { //used when the user first called the program
    const char *sql =
        "INSERT INTO graphs (name, directed, created_at) "
        "VALUES (?, ?, date('now')); ";

    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(database, sql, -1, &stmt, nullptr);

    sqlite3_bind_text(stmt, 1, graph.getName().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 2, graph.getDirected());

    sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    return static_cast<int> (sqlite3_last_insert_rowid(database)); //return the graph_id
}

void databasePersistence::insertEdge(int graphId, int u, int v, int weight) {
    const char *sql =
        "INSERT INTO edges (graph_id, u, v, weight) "
        "VALUES (?, ?, ?, ?); ";

    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(database, sql, -1, &stmt, nullptr);

    sqlite3_bind_int(stmt, 1, graphId);
    sqlite3_bind_int(stmt, 2, u);
    sqlite3_bind_int(stmt, 3, v);
    sqlite3_bind_int(stmt, 4, weight);

    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
}

//insert a row into runs table, return the run_id
int databasePersistence::insertRun(int graphId, Algorithm algorithm) {
    const char *sql =
        "INSERT INTO runs (graph_id, algorithm, started_at) "
        "VALUES (?, ?, date('now'));";
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(database, sql, -1, &stmt, nullptr);
    //open the connection to db in main.cpp
    //access the opened database, zsql/sql is statement to be compiled
    // nbyte neg -> zsql read up to the first zero terminator
    //pztail null, pointer to the left of a compiled prepared statement (next)
    //-> output parameter populates a pointer to a sqlite3_stmt passed in

    sqlite3_bind_int(stmt, 1, graphId);
    sqlite3_bind_int(stmt, 2, static_cast<int>(algorithm));

    //execute the statement using
    sqlite3_step(stmt); //execute prepared statement
    sqlite3_finalize(stmt); //destroy prepared statement

    return static_cast<int> (sqlite3_last_insert_rowid(database));
}

void databasePersistence::insertEvent(int runId, const Event& event) {
    const char *sql =
    "INSERT INTO steps (run_id, step_index, action, u, v, weight)"
    "VALUES (?, ?, ?, ?, ?, ?); ";

    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(database, sql, -1, &stmt, nullptr);

    sqlite3_bind_int(stmt, 1, runId);
    sqlite3_bind_int(stmt, 2, event.step);
    sqlite3_bind_int(stmt, 3, static_cast<int>(event.action));
    sqlite3_bind_int(stmt, 4, event.u);
    sqlite3_bind_int(stmt, 5, event.v);
    sqlite3_bind_int(stmt, 6, event.weight);

    //execute
    sqlite3_step(stmt);
    //finalize
    sqlite3_finalize(stmt);
}

int databasePersistence::saveRun(int graphId, const EventLog& event_log) {
    //for each run, call to insert run and call
    sqlite3_exec(database, "BEGIN TRANSACTION;", nullptr, nullptr, nullptr);

    int runId = insertRun(graphId, event_log.getAlgorithm());

    for (auto e: event_log.getEvents()) {
        insertEvent(runId, e);
    }

    //end the transaction
    sqlite3_exec(database, "COMMIT;", nullptr, nullptr, nullptr);

    return runId; //indicating which run is just being saved
}

int databasePersistence::saveGraphwithEdges(const Graph& graph) {
    //for each run, call to insert run and call
    sqlite3_exec(database, "BEGIN TRANSACTION;", nullptr, nullptr, nullptr);

    int graphId = insertGraph(graph);

    for (int u = 0; u < graph.getSize(); u++) {
        for (auto [v, w]: graph.getNeighbours(u)) {
            insertEdge(graphId, u, v, w);
        }
    }

    sqlite3_exec(database, "COMMIT;", nullptr, nullptr, nullptr);
    return graphId; //indicating which graph is just being saved

}

Graph databasePersistence::loadGraph(int graphId) {
    //to construct a graph, need string graphName, int vertices, bool directed
    const char *sql1 =
        "SELECT name, directed FROM graphs where id = ?; ";

    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(database, sql1, -1, &stmt, nullptr);
    sqlite3_bind_int(stmt, 1, graphId);

    string graphName;
    bool directed = false;

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        //check if the execution of a prepared sql statement has successfully retireved a new row
        //or it means to check if the prepare statement actually return any new row
        graphName = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        directed = sqlite3_column_int(stmt, 1);
    } else {
        throw runtime_error("Graph is not yet in database");
    }

    sqlite3_finalize(stmt);

    const char *sql2 =
        "SELECT u, v, weight FROM edges WHERE graph_id = ?; ";

    sqlite3_stmt* stmt2;
    sqlite3_prepare_v2(database, sql2, -1, &stmt2, nullptr);
    sqlite3_bind_int(stmt2, 1, graphId);

    //first, find the number of vertices
    int maxVertex = -1; //keep track of the vertex with highest value seen
    vector<tuple<int,int,int>> edges; //u,v,weight

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int u = sqlite3_column_int(stmt, 0);
        int v = sqlite3_column_int(stmt, 1);
        int w = sqlite3_column_int(stmt, 2);

        maxVertex = max({maxVertex, u, v, w});
        edges.push_back({u,v,w});
    }

    sqlite3_finalize(stmt2);

    //create graph
    Graph g(graphName, maxVertex, directed);

    //add the edges in
    for (auto [u,v,w]: edges) {
        g.addEdge(u, v, w);
    }

    return g;
}

vector<Event> databasePersistence::loadEvents(int runId) {
    //event: algorithm, action, u,v, weight, step
    const char *sql1 = //ake the algorithm
        "SELECT algorithm FROM runs where id = ?; ";
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(database, sql1, -1, &stmt, nullptr);
    sqlite3_bind_int(stmt, 1, runId);

    Algorithm algorithm;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        algorithm = static_cast<Algorithm>(sqlite3_column_int(stmt, 0));
    } else {
        throw runtime_error("Algorithm is not yet saved in database");
    }

    sqlite3_finalize(stmt);

    const char *sql2 =
        "SELECT step_index, action, u, v, weight FROM steps WHERE run_id = ?; ";
    sqlite3_stmt* stmt2;
    sqlite3_prepare_v2(database, sql2, -1, &stmt2, nullptr);
    sqlite3_bind_int(stmt2, 1, runId);

    vector<Event> events;

    while (sqlite3_step(stmt2) == SQLITE_ROW) {

        int step_index = sqlite3_column_int(stmt2, 0);
        Action action = static_cast<Action>(sqlite3_column_int(stmt2, 1));
        int u = sqlite3_column_int(stmt2, 2);
        int v = sqlite3_column_int(stmt2, 3);
        int w = sqlite3_column_int(stmt2, 4);

        Event e(algorithm, action, u, v, w, step_index);
        events.push_back(e);
    }

    return events;
}

vector<int> databasePersistence::getRuns(int graphId) {
    const char *sql1 =
        "SELECT id FROM runs WHERE graph_id = ?; ";

    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(database, sql1, -1, &stmt, nullptr);
    sqlite3_bind_int(stmt, 1, graphId);

    vector<int> runs;

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        runs.push_back(sqlite3_column_int(stmt, 0));
    }

    sqlite3_finalize(stmt); //avoid leaks

    return runs;
}




