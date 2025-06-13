#ifndef POSTFIXCONVERTER_H
#define POSTFIXCONVERTER_H

#include <vector>
#include <string>
#include <stack>

class PostfixConverter {
private:
    int tempCounter; //������� ��� ��������� ����������

    bool isOperator(char c); //�������� �������� �� ������ ����������
    bool isOperand(char c); //�������� �������� �� ������ ���������
    std::string generateTempName(); //��������� ����� ��������� ����������

public:
    PostfixConverter();
    std::vector<std::string> convert(const std::string& expression); //�������� ����� ��������������
};

#endif