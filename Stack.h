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
private:
    StkNode* head;
};

#endif
