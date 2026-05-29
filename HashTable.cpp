#include "HashTable.h"

//Constructor (is empty)
HashTable::HashTable() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        table[i] = nullptr;
    }
}

//Destructor
HashTable::~HashTable() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        HashNode* current = table[i];
        while (current != nullptr) {
            HashNode* temp = current;
            current = current->next;
            delete temp;
        }
        table[i] = nullptr;
    }
}

//Converts an ID to an index of the table
int HashTable::hashFunction(int id) {
    return id % TABLE_SIZE;
}

//Inserts a task in the table
void HashTable::insert(Task t) {
    int index = hashFunction(t.getId());
    HashNode* current = table[index];

 
    while (current != nullptr) {
        if (current->key == t.getId()) {
            cout << "[HashTable] The ID " << t.getId() << " already exist." << endl;
            return;
        }
        current = current->next;
    }

    HashNode* newNode = new HashNode(t.getId(), t);
    newNode->next = table[index];
    table[index] = newNode;
}

//Searches a task by ID
//If found it returns the pointer if not nullptr
Task* HashTable::search(int id) {
    int index = hashFunction(id);
    HashNode* current = table[index];

    while (current != nullptr) {
        if (current->key == id) {
            return &(current->task);
        }
        current = current->next;
    }
    return nullptr;
}

//Eliminates a task by ID
//Returns true if eliminated
bool HashTable::remove(int id) {
    int index = hashFunction(id);
    HashNode* current = table[index];
    HashNode* before = nullptr;

    while (current != nullptr) {
        if (current->key == id) {
            if (before == nullptr) {
                table[index] = current->next;
            } else {
                before->next = current->next;
            }
            delete current;
            return true;
        }
        before = current;
        current = current->next;
    }
    return false; 
}

//Upadates the information of the task in the table
void HashTable::update(Task t) {
    int index = hashFunction(t.getId());
    HashNode* current = table[index];

    while (current != nullptr) {
        if (current->key == t.getId()) {
            current->task = t; 
            return;
        }
        current = current->next;
    }
    cout << "[HashTable] There is no task with the ID " << t.getId() << " to update." << endl;
}

//Verifica si existe una tarea en la tabla
//Checks if a task exist in the table
//Returns true if found if not false
bool HashTable::exists(int id) {
    return search(id) != nullptr;
}
