#ifndef QUEUE_H
#define QUEUE_H
#include <iostream>
#include "Task.h"

using namespace std;

struct QueNode {
    Task task;
    QueNode* next;
};

class Queue {
public:
    Queue();
    void enqueue(Task t);
    void show();
    void removeTask(int id);
    
private:
    QueNode* front;
    QueNode* back;
};

#endif
