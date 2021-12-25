#include <iostream>
#include <cmath>
#include "Calculator.h"
#include "Stack.h"
using namespace std;

void Calculator::input() {
    int i;

    while (1) {
        cout << "<조건1> : 연산자는 덧셈, 뺄셈만 가능하며 연산자 외 수식은 괄호만 사용" << endl;
        cout << "식을 입력하세요 : ";
        cin.getline(this->inputArr, 100);
        i = this->check_input(); 
        if (i != -1) break;
    }
}

int Calculator::check_input() {
    int i = 0;
    for (i = 0; this->inputArr[i] != '\0'; i++) {
        if (this->inputArr[i] != '(' && this->inputArr[i] != ')' && this->inputArr[i] != '-' && this->inputArr[i] != '+' && (this->inputArr[i] > '9' || this->inputArr[i] < '0') && this->inputArr[i] != ' ') {
            cout << "수식입력에 문제가 생겨 식을 다시 입력합니다." << endl;
            cout << "<조건1>에 맞게 수식을 입력해주세요." << endl << endl;;
            return -1;
        }  
    }
    return 0;
}

void Calculator::reArrange() {

    for (this->inputIdx = 0; this->inputArr[this->inputIdx] != '\0'; this->inputIdx++) {
        if (this->inputArr[this->inputIdx] <= '9' && this->inputArr[this->inputIdx] >= '0') {
            this->outputArr[this->outputIdx] = this->inputArr[this->inputIdx];
            this->outputIdx++;
        }
        else if (this->inputArr[this->inputIdx] == '+'  || this->inputArr[this->inputIdx] == '-') {
   
            this->outputArr[this->outputIdx] = ' ';
            this->outputIdx++;
            this->s_arr.push(this->inputArr[this->inputIdx]);
        }

        else if (this->inputArr[this->inputIdx] == '(') {
            this->s_arr.push(this->inputArr[this->inputIdx]);
        }
        else if (this->inputArr[this->inputIdx] == ')') {
            for (this->s_arr.top; this->s_arr.peak() != '('; this->s_arr.top--) {
                this->outputArr[this->outputIdx] = this->s_arr.pop();
                this->s_arr.top++;
                this->outputIdx++;
            }
            this->outputArr[this->outputIdx] = this->s_arr.pop();
            this->outputIdx++;
        }
        else if (this->inputArr[this->inputIdx] == '*' || this->inputArr[this->inputIdx] == '/') {
            this->outputArr[this->outputIdx] = ' ';
            this->outputIdx++;
            this->s_arr.push(this->inputArr[this->inputIdx]);
        }

    }
    for (this->s_arr.top; this->s_arr.top != -1; this->s_arr.top--) {
        this->outputArr[this->outputIdx] = this->s_arr.pop();
        this->s_arr.top++;
        this->outputIdx++;
    }
    this->outputArr[this->outputIdx] = '\0';
}

int Calculator::change_value1() {
    int num1[50];
    int a = 0;
    int i = 0;
    char t;
    
    while (1) {
        num1[i] = this->s_cal.pop();
        if (num1[i] == ' ') {
            t = num1[i];
            break;
        }
        else if (num1[i] == -1) {
            a *= -1;
            i++;
        }
        else {
            a += pow(10, i) * num1[i];
            i++;
        }
    }
    return a;
}

int Calculator::change_value2() {
    int num2[50];
    int b = 0;
    int j = 0;
    
    if ((this->s_cal.peak() < 0 || this->s_cal.peak() > 9) && this->s_cal.peak() != -1) b = this->s_cal.pop();

    while ((this->s_cal.peak() >= 0 && this->s_cal.peak() <=9) || this->s_cal.peak() == -1 ) {
        if ((this->s_cal.peak() < 0 || this->s_cal.peak() > 9) && this->s_cal.top == -1) {
            break;
        }
        else if (this->s_cal.peak() == -1 && this->s_cal.top != -1) {
            if (b == 0) {
                b = -1;
                break;
            }
            else {
                b *= -1;
                j++;
            }
        }
        else {
            num2[j] = this->s_cal.pop();
            b += pow(10, j) * num2[j];
            j++;
        }
    }
    return b;
}

int Calculator::add() {
    int a, b;
    int result;
    a = this->change_value1();
    b = this->change_value2();
    result = b + a;
    if (this->outputArr[this->outputIdx + 1] == '(') {
        cout << "괄호출력 : (" << b << " + " << a << ") = " << result << endl;
        this->outputIdx++;
    }
    this->s_cal.push(result);
    return result;
}

int Calculator::subtract() {
    int a, b;
    int result;
    a = this->change_value1();
    b = this->change_value2();
    result = b - a;
    if (this->outputArr[this->outputIdx + 1] == '(') {
        cout << "괄호출력 : (" << b << " - " << a << ") = " << result << endl;
        this->outputIdx++;
    }
    this->s_cal.push(result);
    return result;
}

int Calculator::calc() {
    int result = 0;
    int i = 0;

    for (this->outputIdx = 0; this->outputArr[this->outputIdx] != '\0'; this->outputIdx++) {

        if (this->outputArr[this->outputIdx] <= '9' && this->outputArr[this->outputIdx] >= '0') {
            this->s_cal.push(this->outputArr[this->outputIdx] - '0');
        }
        else if (this->outputArr[this->outputIdx] == ' ') {
            this->s_cal.push(this->outputArr[this->outputIdx]);
        }
        else if (this->outputArr[this->outputIdx] == '+') {
            result = this->add();
        }
        else if (this->outputArr[this->outputIdx] == '-') {
            if (this->outputArr[this->outputIdx + 1] <= '9' && this->outputArr[this->outputIdx + 1] >= '0') {
                this->s_cal.push(-1);
            }
            else result = this->subtract();
        }
    }
    return result;
}
