#include <iostream>
#include <fstream>
#include <sstream>
#include "Graph.h"

using namespace std;

//Registar a Dependency between tasks
//Returns true if a dependency was added if not false
bool Graph::addDependency(int taskId, int prereqId, tasklist& tasks)
{
    if (taskId == prereqId) {
        cout << "Invalid, a task cannot depend on itself" << endl;
        return false;
    }

    graph[taskId].push_back(prereqId);
    if (hasCycle()) {
        graph[taskId].pop_back();
        cout << "Dependency rejected" << endl;
        return false;
    }
    cout << "Dependency added successfully" << endl;
    return true;
}

//Shows the Dependenciesin the graph
void Graph::showDependency() {
    
    cout << endl << "===== Task Dependencies =====" << endl;

    bool found = false;

    for (int i = 0; i < MAX_TASKS; i++) {
        if (!graph[i].empty()) {
            found = true;
            cout << "Task " << i << " depends on: ";

            for (int prereq : graph[i]) {
                cout << prereq << " ";
            }

            cout << endl;
        }
    }

    if (!found) {
        cout << "No dependencies registered" << endl;
    }
}

//Checks if they are any cycles in the graph
//Returnes true if they are cycles  etween dependency
bool Graph::hasCycle() {
    bool visited[MAX_TASKS] = {false};
    bool recursion[MAX_TASKS] = {false};

    for (int i = 0; i < MAX_TASKS; i++) {
        if (!visited[i]) {
            if (cycle(i, visited, recursion)) {
                return true;
            }
        }
    }
    return false;
}

//Checks if the task can be completed by its prerequist
//Returns true if the prerequisits are completed
bool Graph::canComplete(tasklist& tasks, int taskId) {
    
    if (tasks.searchList(taskId) == nullptr) {
        cout << "Task not found" << endl;
        return false;
    }

    for (int prereq : graph[taskId]) {
        Node* node = tasks.searchList(prereq);

        if (node == nullptr || !node->task.isCompleted()) {
            cout << "You must complete task " << prereq << " first" << endl;
            return false;
        }
    }

    return true;
}

//Detects if they are cycles in the graph
//returns true if its finds a cycle
bool Graph::cycle(int taskId, bool visited[], bool recursion[]) {
    visited[taskId] = true;
    recursion[taskId] = true;

    for (int prereq : graph[taskId]) {
        if (!visited[prereq]) {
            if (cycle(prereq, visited, recursion)) {
                return true;
            }
        }
        else if (recursion[prereq]) {
            return true;
        }
    }

    recursion[taskId] = false;
    return false;
}

//Save the dependencies in a file
void Graph::saveDependencies(string filename) {
    ofstream file(filename);
    
    for (int taskId = 0; taskId < MAX_TASKS; taskId++) {
        for (int prereqId : graph[taskId]) {
            file << taskId << "," << prereqId << endl;
        }
    }

    file.close();

    cout << "Dependencies saved successfully" << endl;
}

//Loads the dependencies from the file
void Graph::loadDependencies(string filename, tasklist& tasks) {
    ifstream file(filename);

    if (!file) {
        cout << "No dependency file found" << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string taskId, prereqId;
        getline(ss, taskId, ',');
        getline(ss, prereqId, ',');

        addDependency(stoi(taskId), stoi(prereqId), tasks);
    }

    file.close();

    cout << "Dependencies loaded successfully" << endl;
}
