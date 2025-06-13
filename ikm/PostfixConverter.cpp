#include "PostfixConverter.h"
#include <stdexcept>

using namespace std;

PostfixConverter::PostfixConverter() : tempCounter(1) {}

//�������� ���������
bool PostfixConverter::isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

//�������� ��������
bool PostfixConverter::isOperand(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

//��������� ����� ��������� ����������
string PostfixConverter::generateTempName() {
    return "T" + to_string(tempCounter++);
}

//�������� ����� ��������������
vector<string> PostfixConverter::convert(const string& expression) {
    if (expression.empty()) {
        throw runtime_error("������ ���������");
    }

    stack<string> operands; //���� ��� �������� ���������
    vector<string> instructions; //������ ��� �������� ����������

    for (char c : expression) {
        if (isOperand(c)) {
            operands.push(string(1, c));
        }
        else if (isOperator(c)) {
            if (operands.size() < 2) {
                throw runtime_error("������������ ����������� ���������: ������������ ��������� ��� ���������");
            }

            string operand2 = operands.top();
            operands.pop();
            string operand1 = operands.top();
            operands.pop();

            string tempName = generateTempName();

            //��������� ���������� ��� ��������
            instructions.push_back("LD " + operand1);

            switch (c) {
            case '+':
                instructions.push_back("AD " + operand2);
                break;
            case '-':
                instructions.push_back("SB " + operand2);
                break;
            case '*':
                instructions.push_back("ML " + operand2);
                break;
            case '/':
                instructions.push_back("DV " + operand2);
                break;
            default:
                throw runtime_error("����������� ��������");
            }

            instructions.push_back("ST " + tempName);
            operands.push(tempName);
        }
        else {
            throw runtime_error("������������ ������ � ���������: " + string(1, c));
        }
    }

    if (operands.size() != 1) {
        throw runtime_error("������������ ����������� ���������: �������� ������ ��������");
    }
    return instructions;
}