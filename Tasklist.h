#ifndef TASKLIST_H
#define TASKLIST_H
#include "Task.h"
#include <iostream>

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
private:
    Node* head;    
};

#endif
