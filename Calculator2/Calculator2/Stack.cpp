#include <iostream>
#include "Stack.h"
using namespace std;

void c_Stack::push(char data) {
    int stackCapacity = (sizeof(this->Arr) / sizeof(*this->Arr));

    if (top == stackCapacity - 1) {
        return;
    }

    top++;
    this->Arr[top] = data;

}

char c_Stack::pop() {
    if (top == -1) {
        return -1;
    }

    char rtn;
    rtn = this->Arr[top];
    top--;
    return rtn;
}

char c_Stack::peak() {
    if (top == -1) {
        return -1;
    }
    return Arr[top];
}

void i_Stack::push(int data) {
    int stackCapacity = (sizeof(this->Arr) / sizeof(*this->Arr));

    if (top == stackCapacity - 1) {
        return;
    }

    top++;
    this->Arr[top] = data;

}

int i_Stack::pop() {
    if (top == -1) {
        return -1;
    }

    int rtn;
    rtn = this->Arr[top];
    top--;
    return rtn;
}

int i_Stack::peak() {
    if (top == -1) {
        return -1;
    }
    return Arr[top];
}