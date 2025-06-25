#ifndef POSTFIX_CONVERTER_H
#define POSTFIX_CONVERTER_H

#include <string>

using namespace std;

//узел стека для хранения операндов
struct StackNode {
    string data;
    StackNode* next;
    StackNode(const string& val) : data(val), next(nullptr) {}
};

//реализация стека на связном списке
class SimpleStack {
private:
    StackNode* topNode;
    int stackSize;

public:
    SimpleStack();
    ~SimpleStack();
    void push(const string& val); //добавить элемент
    void pop(); //удалить верхний элемент
    string top() const; //получить верхний элемент
    bool empty() const; //проверить на пустоту
    int size() const; //получить размер
};

//узел списка команд
struct InstructionNode {
    string instruction;
    InstructionNode* next;
    InstructionNode(const string& instr) : instruction(instr), next(nullptr) {}
};

//список для хранения сгенерированных команд
class InstructionList {
private:
    InstructionNode* head;
    InstructionNode* tail;
    int listSize;

public:
    InstructionList();
    ~InstructionList();
    void addInstruction(const string& instr); //добавить команду
    void printAll() const; //вывести все команды
    int size() const; //получить размер
};

//основной класс конвертера
class PostfixConverter {
private:
    SimpleStack operands; //стек операндов
    InstructionList instructions; //список команд
    int tempCounter; //счетчик временных переменных

    bool isOperator(char c); //проверить оператор
    bool isOperand(char c); //проверить операнд
    string generateTempName(); //сгенерировать имя временной переменной

public:
    PostfixConverter();
    void convert(const string& expression); //конвертировать выражение
    void printInstructions() const; //вывести инструкции
};

#endif
