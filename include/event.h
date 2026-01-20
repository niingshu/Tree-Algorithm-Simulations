#pragma once //make sure that the file is included only once
#include <vector>

enum class Action {
    VISIT_NODE = 1,
    DISCOVERY_EDGE = 2,
    ADD_TO_TREE = 3,
    RELAX_EDGE = 4
};

struct Event {
    Action action;
    int u; //source vertex
    int v; //target vertex
    int weight = 0; //stored as default
};

class EventRecord {
public:
    std::vector<Event> events;

    void record(Action action, int u = -1, int v = -1, int weight = 0) {
        events.push_back({action, u, v});
    }
};