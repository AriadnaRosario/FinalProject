#include "Stack.h"

//Constructor
//Se inicializa vacio
Stack::Stack() {
    head = nullptr;
}

//Agrega una acciC3n a la pila
void Stack::push(string action) {
    StkNode* newNode = new StkNode;
    newNode->action = action;
    newNode->next = head;
    head = newNode;
}

//Muestra todas las acciones almacenadas en la pila
void Stack::show() {
    StkNode* list = head;

    if (list == nullptr) {
        cout << "There are no action in the history." << endl;
        return;
    }

    int num = 1;
    while (list != nullptr) {
        cout << num << ". " << list->action << endl;
        list = list->next;
        num++;
    }
}
