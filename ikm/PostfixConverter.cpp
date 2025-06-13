#include "PostfixConverter.h"
#include <stdexcept>

using namespace std;

PostfixConverter::PostfixConverter() : tempCounter(1) {}

//проверка оператора
bool PostfixConverter::isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

//проверка операнда
bool PostfixConverter::isOperand(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

//генерация имени временной переменной
string PostfixConverter::generateTempName() {
    return "T" + to_string(tempCounter++);
}

//основной метод преобразования
vector<string> PostfixConverter::convert(const string& expression) {
    if (expression.empty()) {
        throw runtime_error("Пустое выражение");
    }

    stack<string> operands; //стек для хранения операндов
    vector<string> instructions; //вектор для хранения инструкций

    for (char c : expression) {
        if (isOperand(c)) {
            operands.push(string(1, c));
        }
        else if (isOperator(c)) {
            if (operands.size() < 2) {
                throw runtime_error("Некорректное постфиксное выражение: недостаточно операндов для оператора");
            }

            string operand2 = operands.top();
            operands.pop();
            string operand1 = operands.top();
            operands.pop();

            string tempName = generateTempName();

            //генерация инструкций для операции
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
                throw runtime_error("Неизвестный оператор");
            }

            instructions.push_back("ST " + tempName);
            operands.push(tempName);
        }
        else {
            throw runtime_error("Некорректный символ в выражении: " + string(1, c));
        }
    }

    if (operands.size() != 1) {
        throw runtime_error("Некорректное постфиксное выражение: остались лишние операнды");
    }
    return instructions;
}
