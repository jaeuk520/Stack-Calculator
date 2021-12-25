#pragma once
#include <iostream>
#include "Stack.h"
using namespace std;

class Calculator {
private:
    char inputArr[100];
    char outputArr[100];
    c_Stack s_arr;
    i_Stack s_cal;
    int inputIdx;
    int outputIdx = 0;

public:
    void input();
    int check_input();
    void reArrange();
    int calc();
    int add();
    int subtract();
    int change_value1();
    int change_value2();
};