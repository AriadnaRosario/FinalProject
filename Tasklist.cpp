#include "Tasklist.h"

tasklist::tasklist() {
    head = nullptr;
}

void tasklist::insertList(Task t) {
    Node* newNode = new Node;
    newNode->task = t;    
    newNode->next = head;  
    head = newNode;  
    
    
}    
    
void tasklist::showList() {
    Node* list = head;

    if (list == nullptr) {
        cout << "There are no task on the list" << endl;
        return;
    }

    while (list != nullptr) {
        cout << "ID: " << "[" << list->task.id << "]" << endl;
        cout << "title: " << list->task.title << endl;
        cout << "Description: " << list->task.description << endl;
        cout << "Course: " << list->task.course << endl;
        cout << "Priority: " << list->task.priority << endl;
        cout << "Due Date: " << list->task.dueDate << endl;
        cout << "Status: " ;
        if (list->task.completed) {
            cout << "Completed";
        } else {
            cout << "Pending";
        } 
        cout << endl << endl;
        list = list->next;
    }
}

Node* tasklist::searchList(int id) {
    Node* list = head;

    while (list != nullptr) {
        if (list->task.id == id) {
            return list;
        }
        list = list->next;
    }
    return nullptr;
}

void tasklist::removeList(int id) {
    Node* list = head;
    Node* before = nullptr;

    while (list != nullptr && list->task.id != id) {
        before = list;
        list = list->next;
    }

    if (list == nullptr) {
        cout << "The task is not on the list";
        return;
    }

    if (before == nullptr) {
        head = list->next;
    } else {
        before->next = list->next;
    }
    
    delete list;
    cout << "The task was removed" << endl;
}
