#pragma once //make sure that the file is included only once
#include <vector>

enum class Action : int {
    VISIT_NODE = 1,
    DISCOVERY_EDGE = 2,
    ADD_TO_TREE = 3,
    RELAX_EDGE = 4
};

enum class Algorithm : int {
    BFS = 1,
    DFS = 2,
    DIJKSTRA = 3,
    KRUSKALS = 4,
    PRIMS = 5
};

struct Event {
    Algorithm algorithm;
    Action action;
    int u; //source vertex
    int v; //target vertex
    int weight = 0; //stored as default
    int step; //record which step we are at for rewind

    Event(Algorithm algorithm, Action action, int u, int v, int weight, int step)
        : algorithm(algorithm), action(action), u(u), v(v), weight(weight), step(step) {}
};

class EventRecord {
public:
    std::vector<Event> events;
    void record(Algorithm algorithm, Action action, int u = -1, int v = -1, int weight = 0, int step = 0) {
        events.push_back({algorithm, action, u, v, weight, step});
    }
};