#include "Stack.h"
#include <fstream>

//Constructor
//It inicialise empty
Stack::Stack() {
    head = nullptr;
}

//Adds an action to the stack
void Stack::push(string action) {
    StkNode* newNode = new StkNode;
    newNode->action = action;
    newNode->next = head;
    head = newNode;
}

//Shows all the actions stored in the stack
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

//Save the action history in the stack in a file
void Stack::saveHistory(string filename) {

    ofstream file(filename);
    if (head == nullptr) {
        cout << "No history to save" << endl;
        return;
    }

    StkNode* current = head;
    while (current != nullptr) {
        file << current->action << endl;
        current = current->next;

    }

    file.close();

    cout << "History saved successfully" << endl;

}

//Loads the action history from the file
void Stack::loadHistory(string filename) {
    ifstream file(filename);

    if (!file) {
        cout << "No history file found" << endl;
        return;
    }

    string action;
    while (getline(file, action)) {
        push(action);
    }

    file.close();
    cout << "History loaded successfully" << endl;
}
