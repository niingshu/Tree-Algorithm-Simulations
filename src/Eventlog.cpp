//
// Created by Ning Shu on 2026-01-20.
//
#include "EventLog.h"
#include "event.h"

//constructor
EventLog::EventLog(Algorithm algorithm, int graphId)
    : algorithm(algorithm), graphId(graphId), stepCounter(0) {}

void EventLog::record(Algorithm algorithm, Action action, int u, int v, int weight) {
    Event e;
    e.algorithm = algorithm;
    e.action = action;
    e.u = u;
    e.v = v;
    e.weight = weight;
    e.step = stepCounter++;

    events.push_back(e);
}

const vector<Event>& EventLog::getEvents() const {
    return events;
}

void EventLog::clear() {
    events.clear();
    stepCounter = 0;
}



