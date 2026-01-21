//
// Created by Ning Shu on 2026-01-20.
//

#ifndef TREE_ALGORITHM_SIMULATIONS_EVENLOG_H
#define TREE_ALGORITHM_SIMULATIONS_EVENLOG_H


#include <vector>
#include "event.h"

using namespace std;

class EventLog {
    public:
    EventLog(Algorithm algorithm, int graphId);

    void record(Algorithm algorithm, Action action, int u = -1, int v = -1, int weight = 0);

    const vector<Event>& getEvents() const;

    const Algorithm& getAlgorithm() const;

    void clear();

    private:
    Algorithm algorithm;
    int graphId;
    int stepCounter;
    vector<Event> events;

};

#endif //TREE_ALGORITHM_SIMULATIONS_EVENLOG_H