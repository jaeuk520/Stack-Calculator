#include "Calculator2.h"
#include "Stack.h"
#include <iostream>
#include <exception>
using namespace std;

void Calculator2::console_input() {
    int i;

    while (1) {
        cout << "<����1> : �����ڴ� ����, ����, ����, �������� �����ϸ� ������ �� ������ ��ȣ�� ���" << endl;
        cout << "<����2> : �Է��� ������, ����, ������ ��� �� �ѹ� ��� ���⸦ �� ��" << endl;
        cout << "<����3> : ��꿡 ���Ǵ� ������ ������ ��갪�� int �ڷ���(-2,147,483,648 ~ 2,147,483,647)�� ����� �ʵ��� �Ѵ�." << endl;
        cout << "���� �Է��ϼ��� : ";
        cin.getline(this->inputArr, 100);
        i = this->check_input();
        if (i != -1) break;
    }
}

class my_exception1 : public exception {
public:
    virtual const char* what() const throw() {
        return "��ȣ exception �߻�!";
    }
}myex1;

class my_exception2 : public exception {
public:
    virtual const char* what() const throw() {
        return "���ǵ��� ���� ������ �� ���� exception �߻�!";
    }
}myex2;

class my_exception3 : public exception {
public:
    virtual const char* what() const throw() {
        return "���� exception �߻�!";
    }
}myex3;

class my_exception4 : public exception {
public:
    virtual const char* what() const throw() {
        return "�Է��� ������, ����, ������ ��� �� �ѹ� ��� ���⸦ �� ��!";
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
    if (cal_count == 0 && compare_count > 0) i = 1;  //�񱳼��ĸ� �����ϴ� ���


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
            if (i == 0) {   //�񱳼��ĸ� �ܵ����� ������� �ʰ� �ٸ� �Ϲ� �����İ� �Բ� ����� ��� -> '��ȣ'�� �ݵ�� ����ؾ� ��
                if (this->s_arr.peak() != '(') {
                    cout << "�� ������ �Ϲݽİ� �Բ� ����� �ÿ��� �ݵ�� ��ȣ�� ��Ƽ� ����ؾ� �մϴ�!" << endl;
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
        cout << "��ȣ��� : ( " << b << " * " << a << " ) = " << result << endl;
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
        cout << "��ȣ��� : ( " << b << " / " << a << " ) = " << result << endl;
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
        cout << "�и� 0�� ���� �����ϴ�!" << endl;
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
        cout << "��ȣ��� : ( " << b << " + " << a << " ) = " << result << endl;
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
        cout << "��ȣ��� : ( " << b << " - " << a << " ) = " << result << endl;
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
        cout << "����� : " << b << " > " << a << " = " << boolalpha << result << ", " << static_cast<int>(result) << endl;
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
        cout << "����� : " << b << " < " << a << " = " << boolalpha << result << ", " << static_cast<int>(result) << endl;
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
    // ��� ���ÿ� ���� ����ִµ� ��� ������ �� ���� 0~9������ ���ڰ� �ƴ� ��  -> b�� �ٷ� pop

    while ((this->s_cal.peak() >= 0 && this->s_cal.peak() <= 9) || this->s_cal.peak() == -1) {
        // ��� ������ �� ���� 0~9 ������ ���ڰų� -1�� �� (Ȥ�� �ƹ��͵� ���� ��)
        if ((this->s_cal.peak() < 0 || this->s_cal.peak() > 9) && this->s_cal.top == -1) {
            break; //��� ������ ������� ���� break
        }
        else if (this->s_cal.peak() == -1 && this->s_cal.top != -1) { //��� ���� �� ���� -1�� ��
            if (b == 0) {
                b = -1;
                break; //b�� 0�̸� b�� -1�� �ٲ��ְ� break -> -1�� ������
            }
            else {
                b *= -1;    //b�� 0�� �ƴϸ� b�� -1�� ���ϰ� j++
                j++;
            }
        }
        else {   //��� ������ �� ���� -1�� �ƴϰ� ��������� ���� �� (0~9)
            num2[j] = this->s_cal.pop();
            b += pow(10, j) * num2[j];
            j++;          //����ȭ(?)����
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