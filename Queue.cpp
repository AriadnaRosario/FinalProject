#include "Queue.h"

//Constructor
//Se inicializa vacio
Queue::Queue() {
    front = nullptr;
    back = nullptr;
}

//Inserta una tarea al final de la cola
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

//Muestras las tareas pendientes en la cola
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
