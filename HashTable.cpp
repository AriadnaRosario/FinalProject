#include "HashTable.h"

//Constructor (esta vacC-o)
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

//convierte un ID en un C-ndice de la tabla
int HashTable::hashFunction(int id) {
    return id % TABLE_SIZE;
}

//Inserta una tarea en la tabla
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

//Busca una tarea por el ID 
//Si encontrado devuelce el puntero si no nullptr
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

//Elimina una tarea usando el ID
//devuelve verdadero si se eliminC3
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

//Actualiza la informacion de la tarea en la tabla
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
//Devuelve verdadero si se encuentra si no falso
bool HashTable::exists(int id) {
    return search(id) != nullptr;
}
