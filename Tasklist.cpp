#include "Tasklist.h"

//Constructor
//Se inicializa vacio
tasklist::tasklist() { 
    head = nullptr;
}

//Inserta una tarea al pricipio de la lista
void tasklist::insertList(Task t) {
    Node* newNode = new Node;
    newNode->task = t;    
    newNode->next = head;  
    head = newNode;  
    
    
}    
    
//Muestra todas las tareas en la lista 
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

//Busca una tarea por el ID en la lista 
//Si encontrado retorna el nodo si no nullptr
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


//Remueve una tarea en la lista por ID
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

//Muestras tareas por prioridad
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
