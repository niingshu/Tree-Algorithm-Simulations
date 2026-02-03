//
// Created by Ning Shu on 2026-01-24.
//

#include "JsonExporter.h"
#include <sqlite3.h>
#include <nlohmann/json.hpp>
#include <string>
#include <iostream>
#include <fstream>
#include "../persistence/databasePersistence.h"

using json = nlohmann::json;

//constructor
JsonExporter::JsonExporter(sqlite3 *database)
    : database(database) {}

void JsonExporter::exportGraph(int graphId) {
    Graph g = databasePersistence(database).loadGraph(graphId);

    json j;
    j["id"] = graphId;
    j["graphName"] = g.getName();
    j["directed"] = g.getDirected();

    //vertices
    for (int i = 0; i < g.getSize(); i++) {
        j["vertices"].push_back(i); //list of vertices (int)
    }

    //edges
    for (int u = 0; u < g.getSize(); u++) {
        for (auto [v,w]: g.getNeighbours(u)) {
            j["edges"].push_back({{"u", u}, {"v", v}, {"weight",w}});
        }
    }

    std::ofstream file("../frontend/graphRuning.json");
    //ofstream -> output file stream -> write data to files
    file << j.dump(4); //j is nlohmann::json object with
    // converts the json object to string with 4-space indentation
    //file << means write that string into file

}

void JsonExporter::exportEvents(int runId) {
    vector<Event> events = databasePersistence(database).loadEvents(runId);

    json j;
    for (const auto& event : events) {
        j["events"].push_back({
            {"algorithm", static_cast<int>(event.algorithm)},
            {"action", static_cast<int>(event.action)},
            {"u", event.u},
            {"v", event.v},
            {"weight", event.weight},
            {"step", event.step}});
    }

    std::ofstream file("../frontend/events.json");
    if (!file.is_open()) {
        std::cerr << "Failed to open events.json for writing\n";
        return;
    }
    file << j.dump(4);
    file.close();

}
