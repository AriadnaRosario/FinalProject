#include "Queue.h"

//Constructor
//It inicialise empty
Queue::Queue() {
    front = nullptr;
    back = nullptr;
}

//Inserts a task at the end of the queue
void Queue::enqueue(Task t) {
    QueNode* newNode = new QueNode;
    newNode->task = t;
    newNode->next = nullptr;

    if (back == nullptr) {
        front = newNode;
        back = newNode;
    } else {
        back->next = newNode;
        back = newNode;
    }
}

//Shows the task that are pending in the queue
void Queue::show() {
    QueNode* list = front;

    if (list == nullptr) {
        cout << "There are no pending tasks in the queue." << endl;
        return;
    }

    while (list != nullptr) {
        cout << list->task.getTitle() << "[" << list->task.getId() << "] " << endl;
        list = list->next;
    }
}

//Eliminates tasks from the queue
void Queue::removeTask(int id) {

    QueNode* current = front;
    QueNode* before = nullptr;

    while (current != nullptr) {
        if (current->task.getId() == id) {
            if (before == nullptr) {
                front = current->next;
                if (current == back) {
                    back = nullptr;
                }
            } else {
                before->next = current->next;
                if (current == back) {
                    back = before;
                }
            }
            delete current;
            return;
        }

    before = current;
    current = current->next;
    }
}
