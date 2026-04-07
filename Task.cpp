#include "Task.h"

// Constructor (esta vacC-o)
Task::Task() {
        id = 0;
        title = "";
        description = "";
        course = "";
        priority = 3;
        dueDate = "";
        completed = false;
    }

// Getters
int Task::getId() {
    return id;
}
string Task::getTitle() {
    return title;
}

string Task::getDescription() {
    return description;
}

string Task::getCourse() {
    return course;
}

int Task::getPriority() {
    return priority;
}

string Task::getdueDate() {
    return dueDate;
}
bool Task::isCompleted() {
    return completed;
}
// Setters 
void Task::setId(int _id) {
    id = _id;
}

void Task::setTitle(string _title) {
    title = _title;
}

void Task::setDescription(string _description) {
    description = _description;
}

void Task::setCourse(string _course) {
    course = _course;
}

void Task::setPriority(int _priority) {
    priority = _priority;
}

void Task::setdueDate(string _date) {
    dueDate = _date;
}

void Task::markedCompleted() {
    completed = true;
}
