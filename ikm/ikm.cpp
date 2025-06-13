#include <iostream>
#include <string>
#include <stack>
#include <stdexcept>
#include "PostfixConverter.h"

using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");
    try {
        cout << "=== Конвертер постфиксных выражений в инструкции абстрактной машины ===" << endl;
        cout << "Введите постфиксное выражение (операнды - одиночные буквы, операторы: + - * /):" << endl;

        string expression;
        getline(cin, expression);

        if (expression.empty()) {
            throw runtime_error("Ошибка: Введено пустое выражение.");
        }

        PostfixConverter converter;
        vector<string> instructions = converter.convert(expression);

        cout << "\nСгенерированные инструкции:" << endl;
        for (const string& instr : instructions) {
            cout << instr << endl;
        }

    }
    catch (const exception& e) {
        cerr << "Ошибка: " << e.what() << endl;
        return 1;
    }

    return 0;
}