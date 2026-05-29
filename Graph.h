#ifndef GRAPH_H
#define GRAPH_H
#include <vector>
#include "Task.h"
#include "Tasklist.h"
#include "Stack.h"

using namespace std;

class Graph {
public:
    bool addDependency(int taskId, int prereqId, tasklist& tasks);
    void showDependency();
    bool hasCycle();
    bool canComplete(tasklist& tasks, int taskId);
    void saveDependencies(string filename);
    void loadDependencies(string filename, tasklist& tasks);
private:
    static const int MAX_TASKS = 1000;
    vector<int> graph[MAX_TASKS];

    bool cycle(int taskId, bool visited[], bool recursion[]);
};

#endif
