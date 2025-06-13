#ifndef POSTFIXCONVERTER_H
#define POSTFIXCONVERTER_H

#include <vector>
#include <string>
#include <stack>
using namespace std;

class PostfixConverter {
private:
    int tempCounter; //счетчик для временных переменных

    bool isOperator(char c); //проверка является ли символ оператором
    bool isOperand(char c); //проверка является ли символ операндом
    string generateTempName(); //генерация имени временной переменной

public:
    PostfixConverter();
    vector<string> convert(const string& expression); //основной метод преобразования
};

#endif