#ifndef GRAPH_H
#define GRAPH_H
#include <vector>
#include "Task.h"
#include "Tasklist.h"

using namespace std;

class Graph {
public:
    void addDependency(int taskId, int prereqId, tasklist& tasks);
    void showDependency();
    bool hasCycle();
    bool canComplete(tasklist& tasks, int taskId);
private:
    static const int MAX_TASKS = 1000;
    vector<int> graph[MAX_TASKS];

    bool cycle(int taskId, bool visited[], bool recursion[]);
};

#endif
