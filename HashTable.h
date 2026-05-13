#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <iostream>
#include "Task.h"

using namespace std;

struct HashNode {
    int key;        
    Task task;      
    HashNode* next; 

    HashNode(int k, Task t) {
        key = k;
        task = t;
        next = nullptr;
    }
};

class HashTable {
public:
    HashTable();
    ~HashTable();

    void insert(Task t);         
    Task* search(int id);         
    bool remove(int id);          
    void update(Task t);         
    bool exists(int id);          
    
private:
    static const int TABLE_SIZE = 101; 
    HashNode* table[TABLE_SIZE];

    int hashFunction(int id);    
};

#endif
