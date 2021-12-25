#include <iostream>
#include "Calculator.h"
#include "Calculator2.h"
#include "Stack.h"
#include <fstream>
#include <string>
using namespace std;

void exc_File(ifstream& inFile, ofstream& outFile, Calculator2& c2, int& j);
void show_output_File(ofstream& outFile, int& c, char op[], int resVal, int q[], int p[], int r[]);

class f_my_exception1 : public exception {
public:
    virtual const char* what() const throw() {
        return "괄호 exception 발생!";
    }
}f_myex1;

class f_my_exception2 : public exception {
public:
    virtual const char* what() const throw() {
        return "정의되지 않은 연산자 및 수식 exception 발생!";
    }
}f_myex2;

class f_my_exception3 : public exception {
public:
    virtual const char* what() const throw() {
        return "계산식 exception 발생!";
    }
}f_myex3;

class f_my_exception4 : public exception {
public:
    virtual const char* what() const throw() {
        return "입력의 연산자, 숫자, 수식은 사용 후 한번 띄워 쓰기를 할 것!";
    }
}f_myex4;

int main(void) {
    Calculator2 c2;
    Calculator2 odd, even;
    int resVal = 0;
    int num = 0;
    ifstream inFile;
    ofstream outFile1, outFile2;
    int p[20], q[20], r[20];
    char op[20];
    int c = 0;
    int i = 0, j = 1;
    char buffer[100];

    cout << "**********계산기************" << endl;
    cout << "계산식 입력 방법" << endl;
    cout << "=======================================" << endl;
    cout << "1. 콘솔 입력" << endl;
    cout << "2. File I/O 입력" << endl;
    cin >> num;
    cin.getline(buffer, 100);

    switch (num) {

    case 1:
        c2.console_input();
        c2.reArrange();
        resVal = c2.calc(num, p, q, r, op, &c);
        cout << "총 계산 결과 : " << resVal << endl;
        break;

    case 2:
        inFile.open("input.txt");
        if (!inFile) {
            cerr << "Unable to open input file" << endl;
            exit(0);
        }
        outFile1.open("Output_odd.txt");
        if (!outFile1) {
            cerr << "Unable to open output file" << endl;
            exit(0);
        }
        outFile2.open("Output_even.txt");
        if (!outFile2) {
            cerr << "Unable to open output file" << endl;
            exit(0);
        }

        while (!inFile.eof()) {
            if (j % 2 == 1) {
                try {
                    exc_File(inFile, outFile1, odd, j);
                }
                catch (f_my_exception2 & e) {
                    outFile1 << e.what() << endl << endl;;
                    continue;
                }
                catch (f_my_exception1 & e) {
                    outFile1 << e.what() << endl << endl;;
                    continue;
                }
                catch (f_my_exception3 & e) {
                    outFile1 << e.what() << endl << endl;;
                    continue;
                }
                catch (f_my_exception4 & e) {
                    outFile1 << e.what() << endl << endl;;
                    continue;
                }
                odd.reArrange();
                resVal = odd.calc(num, p, q, r, op, &c);
                show_output_File(outFile1, c, op, resVal, q, p, r);

                c = 0;
                odd.outputIdx = 0;
                odd.trash();
            }

            else if (j % 2 == 0) {
                try {
                    exc_File(inFile, outFile2, even, j);
                }
                catch (f_my_exception2 & e) {
                    outFile2 << e.what() << endl << endl;;
                    continue;
                }
                catch (f_my_exception1 & e) {
                    outFile2 << e.what() << endl << endl;;
                    continue;
                }
                catch (f_my_exception3 & e) {
                    outFile2 << e.what() << endl << endl;;
                    continue;
                }
                catch (f_my_exception4 & e) {
                    outFile2 << e.what() << endl << endl;;
                    continue;
                }
                even.reArrange();
                resVal = even.calc(num, p, q, r, op, &c);

                show_output_File(outFile2, c, op, resVal, q, p, r);
                c = 0;
                even.outputIdx = 0;
                even.trash();
            }

        }
        break;

    default:
        cout << "1 또는 2번으로 다시 선택해주세요.." << endl;
        break;

    }

    inFile.close();
    outFile1.close();
    outFile2.close();
    return 0;
}

void exc_File(ifstream& inFile, ofstream& outFile, Calculator2& c2, int& j) {
    int l_count = 0, r_count = 0;
    int c_operand = 0, c_operator = 0;

    inFile.getline(c2.inputArr, 100);
    outFile << "계산식 " << j << endl;
    j++;
    l_count = 0, r_count = 0;
    c_operand = 0, c_operator = 0;

    for (int i = 0; c2.inputArr[i] != '\0'; i++) {
        if (c2.inputArr[i] != '(' && c2.inputArr[i] != ')' && c2.inputArr[i] != '-' && c2.inputArr[i] != '+' && (c2.inputArr[i] > '9' || c2.inputArr[i] < '0') && c2.inputArr[i] != '*' && c2.inputArr[i] != '/' && c2.inputArr[i] != ' ' && c2.inputArr[i] != '<' && c2.inputArr[i] != '>')
            throw f_myex2;
        else if (c2.inputArr[i] == '(' || c2.inputArr[i] == ')' || c2.inputArr[i] == '+' || c2.inputArr[i] == '*' || c2.inputArr[i] == '/' || (c2.inputArr[i] <= '9' && c2.inputArr[i] >= '0') || c2.inputArr[i] == '<' || c2.inputArr[i] == '>') {
            if (c2.inputArr[i + 1] != ' ' && c2.inputArr[i + 1] != '\0' && (c2.inputArr[i + 1] > '9' || c2.inputArr[i + 1] < '0')) {
                throw f_myex4;
            }
            if (c2.inputArr[i] == '(') l_count++;
            else if (c2.inputArr[i] == ')') r_count++;
        }
        if (c2.inputArr[i] == '+' || c2.inputArr[i] == '*' || c2.inputArr[i] == '/' || (c2.inputArr[i] == '-' && c2.inputArr[i + 1] == ' ') || c2.inputArr[i] == '<' || c2.inputArr[i] == '>')
            c_operator++;
        else if ((c2.inputArr[i] <= '9' && c2.inputArr[i] >= '0') && (c2.inputArr[i + 1] == ' ' || c2.inputArr[i + 1] == '\0'))
            c_operand++;
    }
    if (l_count != r_count) throw f_myex1;
    if (c_operator == 0 || c_operand == 0 || ((c_operator + 1) != c_operand)) throw f_myex3;

}

void show_output_File(ofstream& outFile, int& c, char op[], int resVal, int q[], int p[], int r[]) {
    for (int a = 0; a < c; a++) {
        if (op[a] == '<' || op[a] == '>') {
            outFile << "비교출력 : " << q[a] << " " << op[a] << " " << p[a] << " = " << boolalpha << static_cast<bool>(r[a]) << ", " << r[a] << endl;
        }
        else outFile << "괄호출력 : ( " << q[a] << " " << op[a] << " " << p[a] << " ) = " << r[a] << endl;
    }
    outFile << "총 계산 결과 : " << resVal << endl << endl;;
}