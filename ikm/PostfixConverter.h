#ifndef POSTFIXCONVERTER_H
#define POSTFIXCONVERTER_H

#include <vector>
#include <string>
#include <stack>
using namespace std;

class PostfixConverter {
private:
    int tempCounter; //������� ��� ��������� ����������

    bool isOperator(char c); //�������� �������� �� ������ ����������
    bool isOperand(char c); //�������� �������� �� ������ ���������
    string generateTempName(); //��������� ����� ��������� ����������

public:
    PostfixConverter();
    vector<string> convert(const string& expression); //�������� ����� ��������������
};

#endif