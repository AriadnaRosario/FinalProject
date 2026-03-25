#ifndef TASK_H
#define TASK_H
#include <string>

using namespace std;

class Task {
public:
    int id;
    string title;
    string description;
    string course;
    int priority;
    string dueDate;
    bool completed;
    Task(){
        completed = false;
    };

};

#endif
