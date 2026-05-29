#include "Tasklist.h"
#include <fstream>
#include <sstream>

//Constructor
//It inicialise empty
tasklist::tasklist() { 
    head = nullptr;
}

//Insert a task at the begining og the list
void tasklist::insertList(Task t) {
    Node* newNode = new Node;
    newNode->task = t;    
    newNode->next = head;  
    head = newNode;  
    
    
}    
    
//Shows all the task on the list 
void tasklist::showList() {
    Node* list = head;

    if (list == nullptr) {
        cout << "There are no task on the list" << endl;
        return;
    }

    while (list != nullptr) {
        cout << "ID: " << "[" << list->task.getId() << "]" << endl;
        cout << "title: " << list->task.getTitle() << endl;
        cout << "Description: " << list->task.getDescription() << endl;
        cout << "Course: " << list->task.getCourse() << endl;
        cout << "Priority: " << list->task.getPriority() << endl;
        cout << "Due Date: " << list->task.getdueDate() << endl;
        cout << "Status: " ;
        if (list->task.isCompleted()) {
            cout << "Completed";
        } else {
            cout << "Pending";
        } 
        cout << endl << endl;
        list = list->next;
    }
}

//Searches a task by ID in the list
//If found it returns the node if not nullptr
Node* tasklist::searchList(int id) {
    Node* list = head;

    while (list != nullptr) {
        if (list->task.getId() == id) {
            return list;
        }
        list = list->next;
    }
    return nullptr;
}

//Removes a task in the list by ID
void tasklist::removeList(int id) {
    Node* list = head;
    Node* before = nullptr;

    while (list != nullptr && list->task.getId() != id) {
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

//Shows tasks by priorities
void tasklist::showPriority(int priority) {
    Node* list = head;
    bool found = false;

    while (list != nullptr) {
        if (list->task.getPriority() == priority) {
            cout << "ID: [" << list->task.getId() << "]" << endl;
            cout << "Title: " << list->task.getTitle() << endl;
            cout << "Description: " << list->task.getDescription() << endl;
            cout << "Course: " << list->task.getCourse() << endl;
            cout << "Priority: " << list->task.getPriority() << endl;
            cout << "Due Date: " << list->task.getdueDate() << endl;
            cout << "Status: ";

            if (list->task.isCompleted()) {
                cout << "Completed";
            } else {
                cout << "Pending";
            }

            cout << endl << endl;
            found = true;
        }

        list = list->next;
    }

    if (!found) {
        cout << "No tasks with that priority." << endl;
    }
}

//Save the tasks in the list in a file
void tasklist::saveData(string filename) {
    
    if (head == nullptr) {
    cout << "No tasks to save" << endl;
    return;
    }
    
    ofstream file(filename);
    Node* current = head;

    while (current != nullptr) {
        Task t = current->task;

        file << t.getId() << "," << t.getTitle() << "," << t.getDescription() << ","
        << t.getCourse() << "," << t.getPriority() << "," << t.getdueDate() << ","
        << t.isCompleted() << endl;

        current = current->next;
    }

    file.close();
    
    cout << "Tasks saved successfully" << endl;
}

//Loads the task from the file
void tasklist::loadData(string filename, HashTable& hash, Queue& pending) {
    ifstream file(filename);

    if (!file) {
        cout << "No file found" << endl;
        return;
    }

    string line;

    while (getline(file, line)) {
        stringstream ss(line);

        string id, title, description, course, priority, dueDate, completed;

        getline(ss, id, ',');
        getline(ss, title, ',');
        getline(ss, description, ',');
	getline(ss, course, ',');
        getline(ss, priority, ',');
        getline(ss, dueDate, ',');
        getline(ss, completed, ',');

        Task t;

        t.setId(stoi(id));
        t.setTitle(title);
        t.setDescription(description);
        t.setCourse(course);
        t.setPriority(stoi(priority));
        t.setdueDate(dueDate);
        t.setCompleted(stoi(completed));

        insertList(t);
        hash.insert(t);

        if (!t.isCompleted()) {
            pending.enqueue(t);
        }
    }

    file.close();
    
    cout << "Tasks loaded successfully" << endl;
}
