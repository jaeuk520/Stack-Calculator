#include "Calculator2.h"
#include "Stack.h"
#include <iostream>
#include <exception>
using namespace std;

void Calculator2::console_input() {
    int i;

    while (1) {
        cout << "<조건1> : 연산자는 덧셈, 뺄셈, 곱셈, 나눗셈만 가능하며 연산자 외 수식은 괄호만 사용" << endl;
        cout << "<조건2> : 입력의 연산자, 숫자, 수식은 사용 후 한번 띄워 쓰기를 할 것" << endl;
        cout << "<조건3> : 계산에 사용되는 숫자의 범위와 계산값은 int 자료형(-2,147,483,648 ~ 2,147,483,647)을 벗어나지 않도록 한다." << endl;
        cout << "식을 입력하세요 : ";
        cin.getline(this->inputArr, 100);
        i = this->check_input();
        if (i != -1) break;
    }
}

class my_exception1 : public exception {
public:
    virtual const char* what() const throw() {
        return "괄호 exception 발생!";
    }
}myex1;

class my_exception2 : public exception {
public:
    virtual const char* what() const throw() {
        return "정의되지 않은 연산자 및 수식 exception 발생!";
    }
}myex2;

class my_exception3 : public exception {
public:
    virtual const char* what() const throw() {
        return "계산식 exception 발생!";
    }
}myex3;

class my_exception4 : public exception {
public:
    virtual const char* what() const throw() {
        return "입력의 연산자, 숫자, 수식은 사용 후 한번 띄워 쓰기를 할 것!";
    }
}myex4;

int Calculator2::check_input() {
    int i = 0;
    int l_count = 0, r_count = 0;
    int c_operand = 0, c_operator = 0;

    try {
        for (i = 0; this->inputArr[i] != '\0'; i++) {
            if (this->inputArr[i] != '(' && this->inputArr[i] != ')' && this->inputArr[i] != '-' && this->inputArr[i] != '+' && (this->inputArr[i] > '9' || this->inputArr[i] < '0') && this->inputArr[i] != '*' && this->inputArr[i] != '/' && this->inputArr[i] != ' ' && this->inputArr[i] != '<' && this->inputArr[i] != '>')
                throw myex2;
            else if (this->inputArr[i] == '(' || this->inputArr[i] == ')' || this->inputArr[i] == '+' || this->inputArr[i] == '*' || this->inputArr[i] == '/' || (this->inputArr[i] <= '9' && this->inputArr[i] >= '0') || this->inputArr[i] == '<' || this->inputArr[i] == '>') {
                if (this->inputArr[i + 1] != ' ' && this->inputArr[i + 1] != '\0' && (this->inputArr[i + 1] > '9' || this->inputArr[i + 1] < '0')) {
                    throw myex4;
                }
                if (this->inputArr[i] == '(') l_count++;
                else if (this->inputArr[i] == ')') r_count++;
            }
            if (this->inputArr[i] == '+' || this->inputArr[i] == '*' || this->inputArr[i] == '/' || (this->inputArr[i] == '-' && this->inputArr[i + 1] == ' ') || this->inputArr[i] == '<' || this->inputArr[i] == '>')
                c_operator++;
            else if ((this->inputArr[i] <= '9' && this->inputArr[i] >= '0') && (this->inputArr[i + 1] == ' ' || this->inputArr[i + 1] == '\0'))
                c_operand++;
        }
        if (l_count != r_count) throw myex1;
        if (c_operator == 0 || c_operand == 0 || ((c_operator + 1) != c_operand)) throw myex3;
    }

    catch (my_exception2 & e) {
        cout << e.what() << endl;
        return -1;
    }
    catch (my_exception1 & e) {
        cout << e.what() << endl;
        return -1;
    }
    catch (my_exception3 & e) {
        cout << e.what() << endl;
        return -1;
    }
    catch (my_exception4 & e) {
        cout << e.what() << endl;
        return -1;
    }
    return 0;
}

void Calculator2::reArrange() {
    int i = 0;
    int compare_count = 0, cal_count = 0;

    for (this->inputIdx = 0; this->inputArr[this->inputIdx] != '\0'; this->inputIdx++) {
        if (this->inputArr[this->inputIdx] == '>' || this->inputArr[this->inputIdx] == '<') compare_count++;
        else if (this->inputArr[this->inputIdx] == '+' || this->inputArr[this->inputIdx] == '-' || this->inputArr[this->inputIdx] == '/' || this->inputArr[this->inputIdx] == '*') cal_count++;
    }
    if (cal_count == 0 && compare_count > 0) i = 1;  //비교수식만 존재하는 경우


    for (this->inputIdx = 0; this->inputArr[this->inputIdx] != '\0'; this->inputIdx++) {

        if (this->inputArr[this->inputIdx] <= '9' && this->inputArr[this->inputIdx] >= '0') {
            this->outputArr[this->outputIdx] = this->inputArr[this->inputIdx];
            this->outputIdx++;
        }
        else if (this->inputArr[this->inputIdx] == '+') {
            if (this->s_arr.peak() == '*' || this->s_arr.peak() == '/') {
                for (this->s_arr.top; this->s_arr.peak() != '*' && this->s_arr.peak() != '/'; this->s_arr.top--) {
                    this->outputArr[this->outputIdx] = this->s_arr.pop();
                    this->s_arr.top++;
                    this->outputIdx++;
                }
            }
            this->outputArr[this->outputIdx] = ' ';
            this->outputIdx++;
            this->s_arr.push(this->inputArr[this->inputIdx]);
        }

        else if (this->inputArr[this->inputIdx] == '-') {

            if (this->inputArr[this->inputIdx + 1] <= '9' && this->inputArr[this->inputIdx + 1] >= '0') {
                this->outputArr[this->outputIdx] = this->inputArr[this->inputIdx];
                this->outputIdx++;
            }

            else if (this->s_arr.peak() == '*' || this->s_arr.peak() == '/') {
                for (this->s_arr.top; this->s_arr.peak() != '*' && this->s_arr.peak() != '/'; this->s_arr.top--) {
                    this->outputArr[this->outputIdx] = this->s_arr.pop();
                    this->s_arr.top++;
                    this->outputIdx++;
                }
            }
            if (this->inputArr[this->inputIdx + 1] > '9' || this->inputArr[this->inputIdx + 1] < '0') {
                this->outputArr[this->outputIdx] = ' ';
                this->outputIdx++;
                this->s_arr.push(this->inputArr[this->inputIdx]);
            }
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

        else if (this->inputArr[this->inputIdx] == '<' || this->inputArr[this->inputIdx] == '>') {
            if (i == 0) {   //비교수식만 단독으로 사용하지 않고 다른 일반 계산수식과 함께 사용할 경우 -> '괄호'와 반드시 사용해야 함
                if (this->s_arr.peak() != '(') {
                    cout << "비교 수식은 일반식과 함께 사용할 시에는 반드시 괄호에 담아서 사용해야 합니다!" << endl;
                    exit(0);
                }
            }
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

int Calculator2::multiply(int n, int p[], int q[], int r[], char op[], int* c) {
    int a, b;
    int result;
    a = this->change_value1();
    b = this->change_value2();
    result = b * a;
    if (this->outputArr[this->outputIdx + 1] == '(' && n == 1) {
        cout << "괄호출력 : ( " << b << " * " << a << " ) = " << result << endl;
        this->outputIdx++;
    }
    else if (this->outputArr[this->outputIdx + 1] == '(' && n == 2) {
        p[*c] = a;
        q[*c] = b;
        r[*c] = result;
        op[*c] = '*';
        this->outputIdx++;
        (*c)++;
    }
    s_cal.push(result);
    return result;
}

int Calculator2::divide(int n, int p[], int q[], int r[], char op[], int* c) {
    int a, b;
    int result;
    a = this->change_value1();
    b = this->change_value2();
    result = b / a;
    if (this->outputArr[this->outputIdx + 1] == '(' && n == 1) {
        cout << "괄호출력 : ( " << b << " / " << a << " ) = " << result << endl;
        this->outputIdx++;
    }
    else if (this->outputArr[this->outputIdx + 1] == '(' && n == 2) {
        p[*c] = a;
        q[*c] = b;
        r[*c] = result;
        op[*c] = '/';
        this->outputIdx++;
        (*c)++;
    }

    if (a == 0) {
        cout << "분모가 0일 수는 없습니다!" << endl;
        return -1;
    }
    s_cal.push(result);
    return result;
}

int Calculator2::add(int n, int p[], int q[], int r[], char op[], int* c) {
    int a, b;
    int result;
    a = this->change_value1();
    b = this->change_value2();
    result = b + a;

    if (this->outputArr[this->outputIdx + 1] == '(' && n == 1) {
        cout << "괄호출력 : ( " << b << " + " << a << " ) = " << result << endl;
        this->outputIdx++;
    }
    else if (this->outputArr[this->outputIdx + 1] == '(' && n == 2) {
        p[*c] = a;
        q[*c] = b;
        r[*c] = result;
        op[*c] = '+';
        this->outputIdx++;
        (*c)++;

    }
    this->s_cal.push(result);
    return result;
}

int Calculator2::subtract(int n, int p[], int q[], int r[], char op[], int* c) {
    int a, b;
    int result;
    a = this->change_value1();
    b = this->change_value2();
    result = b - a;
    if (this->outputArr[this->outputIdx + 1] == '(' && n == 1) {
        cout << "괄호출력 : ( " << b << " - " << a << " ) = " << result << endl;
        this->outputIdx++;
    }
    else if (this->outputArr[this->outputIdx + 1] == '(' && n == 2) {
        p[*c] = a;
        q[*c] = b;
        r[*c] = result;
        op[*c] = '-';
        this->outputIdx++;
        (*c)++;
    }
    this->s_cal.push(result);
    return result;
}


int Calculator2::compare_l(int n, int p[], int q[], int r[], char op[], int* c) {
    int a, b;
    bool result;
    a = this->change_value1();
    b = this->change_value2();
    result = (b > a);

    if (n == 1) {
        cout << "비교출력 : " << b << " > " << a << " = " << boolalpha << result << ", " << static_cast<int>(result) << endl;
        this->outputIdx++;
    }
    else if (n == 2) {
        p[*c] = a;
        q[*c] = b;
        r[*c] = result;
        op[*c] = '>';
        (*c)++;
    }
    this->s_cal.push(static_cast<int>(result));
    return static_cast<int>(result);
}

int Calculator2::compare_s(int n, int p[], int q[], int r[], char op[], int* c) {
    int a, b;
    bool result;
    a = this->change_value1();
    b = this->change_value2();
    result = (b < a);
    if (n == 1) {
        cout << "비교출력 : " << b << " < " << a << " = " << boolalpha << result << ", " << static_cast<int>(result) << endl;
        this->outputIdx++;
    }
    else if (n == 2) {
        p[*c] = a;
        q[*c] = b;
        r[*c] = result;
        op[*c] = '<';
        (*c)++;
    }
    this->s_cal.push(static_cast<int>(result));
    return static_cast<int>(result);
}

int Calculator2::change_value1() {
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

int Calculator2::change_value2() {
    int num2[50];
    int b = 0;
    int j = 0;

    if ((this->s_cal.peak() < 0 || this->s_cal.peak() > 9) && this->s_cal.peak() != -1) b = this->s_cal.pop();
    // 계산 스택에 뭐가 들어있는데 계산 스택의 맨 위가 0~9사이의 숫자가 아닐 때  -> b로 바로 pop

    while ((this->s_cal.peak() >= 0 && this->s_cal.peak() <= 9) || this->s_cal.peak() == -1) {
        // 계산 스택의 맨 위가 0~9 사이의 숫자거나 -1일 때 (혹은 아무것도 없을 때)
        if ((this->s_cal.peak() < 0 || this->s_cal.peak() > 9) && this->s_cal.top == -1) {
            break; //계산 스택이 비어있을 때는 break
        }
        else if (this->s_cal.peak() == -1 && this->s_cal.top != -1) { //계산 스택 맨 위가 -1일 때
            if (b == 0) {
                b = -1;
                break; //b가 0이면 b를 -1로 바꿔주고 break -> -1을 리턴함
            }
            else {
                b *= -1;    //b가 0이 아니면 b에 -1을 곱하고 j++
                j++;
            }
        }
        else {   //계산 스택의 맨 위가 -1도 아니고 비어있지도 않을 때 (0~9)
            num2[j] = this->s_cal.pop();
            b += pow(10, j) * num2[j];
            j++;          //정수화(?)과정
        }
    }
    return b;
}

int Calculator2::calc(int n, int p[], int q[], int r[], char op[], int* c) {
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
            result = this->add(n, p, q, r, op, c);
        }
        else if (this->outputArr[this->outputIdx] == '-') {
            if (this->outputArr[this->outputIdx + 1] <= '9' && this->outputArr[this->outputIdx + 1] >= '0') {
                this->s_cal.push(-1);
            }
            else result = this->subtract(n, p, q, r, op, c);
        }
        else if (this->outputArr[this->outputIdx] == '*') {
            result = this->multiply(n, p, q, r, op, c);
        }
        else if (this->outputArr[this->outputIdx] == '/') {
            result = this->divide(n, p, q, r, op, c);
        }
        else if (this->outputArr[this->outputIdx] == '>') {
            result = this->compare_l(n, p, q, r, op, c);
        }
        else if (this->outputArr[this->outputIdx] == '<') {
            result = this->compare_s(n, p, q, r, op, c);
        }

    }

    return result;
}

void Calculator2::trash() {
    int i = 0;
    int temp;
    while (this->s_cal.top != -1) {
        temp = this->s_cal.pop();
    }
}