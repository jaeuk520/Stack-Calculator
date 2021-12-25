#pragma once
#include "Calculator.h"
using namespace std;

class Calculator2 : public Calculator {
private:
    char outputArr[100];
    c_Stack s_arr;
    i_Stack s_cal;
    int inputIdx;

public:
    Calculator2() { cout << "Calculator2 按眉 积己 肯丰!" << endl; } //constructor
    ~Calculator2() { cout << "Calculator2 按眉 家戈 肯丰!" << endl; } //destructor

    char inputArr[100];
    int outputIdx = 0;

    void console_input();
    int check_input();
    void reArrange();
    int multiply(int n, int p[], int q[], int r[], char op[], int* c);
    int divide(int n, int p[], int q[], int r[], char op[], int* c);
    int calc(int n, int p[], int q[], int r[], char op[], int* c);
    int add(int n, int p[], int q[], int r[], char op[], int* c);
    int subtract(int n, int p[], int q[], int r[], char op[], int* c);
    int change_value1();
    int change_value2();
    int compare_l(int n, int p[], int q[], int r[], char op[], int* c);
    int compare_s(int n, int p[], int q[], int r[], char op[], int* c);
    void trash();
};

