#include "PostfixConverter.h"
#include <iostream>

int main() {
    setlocale(LC_ALL, "Russian");
    //вывод информации о программе
    cout << "=== конвертер постфиксных выражений ===" << endl;

    //ввод выражения
    cout << "введите выражение: ";
    string expression;
    getline(cin, expression);

    try {
        //обработка выражения
        PostfixConverter converter;
        converter.convert(expression);

        //вывод результата
        cout << "\nрезультат:" << endl;
        converter.printInstructions();
    }
    catch (const exception& e) {
        //обработка ошибок
        cerr << "\nошибка: " << e.what() << endl;
        cerr << "введите выражение в правильном формате" << endl;
        return 1;
    }

    return 0;
}
