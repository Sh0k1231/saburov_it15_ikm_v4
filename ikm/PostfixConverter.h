#ifndef POSTFIXCONVERTER_H
#define POSTFIXCONVERTER_H

#include <vector>
#include <string>
#include <stack>

class PostfixConverter {
private:
    int tempCounter; //счетчик для временных переменных

    bool isOperator(char c); //проверка является ли символ оператором
    bool isOperand(char c); //проверка является ли символ операндом
    std::string generateTempName(); //генерация имени временной переменной

public:
    PostfixConverter();
    std::vector<std::string> convert(const std::string& expression); //основной метод преобразования
};

#endif