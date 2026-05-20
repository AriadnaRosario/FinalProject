#include <iostream>
#include "Graph.h"

using namespace std;

//Registra dependencias entre tareas
void Graph::addDependency(int taskId, int prereqId, tasklist& tasks) {
    if (taskId == prereqId) {
        cout << "Invalid, a task cannot depend on itself" << endl;
        return;
    }

    graph[taskId].push_back(prereqId);

    if (hasCycle()) {
        graph[taskId].pop_back();
        cout << "Dependency rejected" << endl;
        return;
    }

    cout << "Dependency added successfully" << endl;
}

//Muestra las dependencias en el grafo
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

//Verifica si hay ciclos en el grafo
//Devuelve verdadero si hay algun ciclo entre dependencias
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

//Verifica si la tarea se puede completar por sus prerequisitos
//Devuelve verdadero si los prerequisitos estan completados
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

//Detecta si hay ciclos en el grafo
//Devuelve verdadero si encuentra un ciclo
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
