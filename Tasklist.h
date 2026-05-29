#ifndef TASKLIST_H
#define TASKLIST_H
#include "Task.h"
#include "HashTable.h"
#include "Queue.h"
#include <iostream>
#include <string>

using namespace std;

struct Node {
    Task task;
    Node* next;
};

class tasklist {
public:
    tasklist();
    void insertList(Task t);
    void showList();
    Node* searchList(int id);
    void removeList(int id);
    void showPriority(int priority);
    void saveData(string filename);
    void loadData(string filename, HashTable& hash, Queue& pending);
private:
    Node* head;    
};

#endif
