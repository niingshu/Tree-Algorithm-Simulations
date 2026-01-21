//
// Created by Ning Shu on 2026-01-20.
//

#include "databasePersistence.h"
#include "EventLog.h"
#include "Graph.h"

//constructor
databasePersistence::databasePersistence(sqlite3 *database)
    : database(database) {}

int databasePersistence::saveGraph(const Graph& graph) { //used when the user first called the program
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
    sqlite3_step(stmt); //execute prepared statment
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

