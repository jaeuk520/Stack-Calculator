#pragma once
#pragma once
#include <iostream>
using namespace std;

class c_Stack {
private:
    char Arr[100];
public:
    int top = -1;
    void push(char data);
    char pop();
    char peak();
};


class i_Stack {
private:
    int Arr[100];
public:
    int top = -1;
    void push(int data);
    int pop();
    int peak();
};