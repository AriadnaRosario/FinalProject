#ifndef STACK_H
#define STACK_H
#include <iostream>
#include <string>

using namespace std;

struct StkNode {
    string action;
    StkNode* next;
};

class Stack {
public:
    Stack();
    void push(string action);
    void show();
    void saveHistory(string filename);
    void loadHistory(string filename);
private:
    StkNode* head;
};

#endif
