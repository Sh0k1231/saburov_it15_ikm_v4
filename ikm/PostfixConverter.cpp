#include "PostfixConverter.h"
#include <iostream>
#include <stdexcept>
#include <cctype>

//реализация методов SimpleStack
SimpleStack::SimpleStack() : topNode(nullptr), stackSize(0) {}

SimpleStack::~SimpleStack() {
    while (!empty()) {
        pop();
    }
}

void SimpleStack::push(const string& val) {
    StackNode* newNode = new StackNode(val);
    newNode->next = topNode;
    topNode = newNode;
    stackSize++;
}

void SimpleStack::pop() {
    if (empty()) {
        throw runtime_error("stack underflow");
    }
    StackNode* temp = topNode;
    topNode = topNode->next;
    delete temp;
    stackSize--;
}

string SimpleStack::top() const {
    if (empty()) {
        throw runtime_error("stack is empty");
    }
    return topNode->data;
}

bool SimpleStack::empty() const {
    return topNode == nullptr;
}

int SimpleStack::size() const {
    return stackSize;
}

//реализация методов InstructionList
InstructionList::InstructionList() : head(nullptr), tail(nullptr), listSize(0) {}

InstructionList::~InstructionList() {
    InstructionNode* current = head;
    while (current != nullptr) {
        InstructionNode* next = current->next;
        delete current;
        current = next;
    }
}

void InstructionList::addInstruction(const string& instr) {
    InstructionNode* newNode = new InstructionNode(instr);
    if (head == nullptr) {
        head = tail = newNode;
    }
    else {
        tail->next = newNode;
        tail = newNode;
    }
    listSize++;
}

void InstructionList::printAll() const {
    InstructionNode* current = head;
    while (current != nullptr) {
        cout << current->instruction << endl;
        current = current->next;
    }
}

int InstructionList::size() const {
    return listSize;
}

//реализация методов PostfixConverter
PostfixConverter::PostfixConverter() : tempCounter(1) {}

bool PostfixConverter::isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

bool PostfixConverter::isOperand(char c) {
    return isalpha(c) && isupper(c);
}

string PostfixConverter::generateTempName() {
    if (tempCounter > 100) {
        throw runtime_error("превышено максимальное количество временных переменных");
    }
    return "T" + to_string(tempCounter++);
}

void PostfixConverter::convert(const string& expression) {
    if (expression.empty()) {
        throw runtime_error("введена пустая строка");
    }

    //проверка корректности выражения
    int operandCount = 0;
    int operatorCount = 0;

    for (char c : expression) {
        if (isOperand(c)) {
            operandCount++;
        }
        else if (isOperator(c)) {
            operatorCount++;
            if (operandCount <= operatorCount) {
                throw runtime_error("недостаточно операндов для оператора '" + string(1, c) + "'");
            }
        }
        else if (!isspace(c)) {
            throw runtime_error("недопустимый символ '" + string(1, c) + "'");
        }
    }

    if (operandCount != operatorCount + 1) {
        throw runtime_error("неправильное количество операторов и операндов");
    }

    //обработка выражения
    for (char c : expression) {
        if (isspace(c)) continue;

        if (isOperand(c)) {
            operands.push(string(1, c));
        }
        else if (isOperator(c)) {
            try {
                string operand2 = operands.top();
                operands.pop();
                string operand1 = operands.top();
                operands.pop();

                string tempName = generateTempName();

                instructions.addInstruction("LD " + operand1);

                switch (c) {
                case '+': instructions.addInstruction("AD " + operand2); break;
                case '-': instructions.addInstruction("SB " + operand2); break;
                case '*': instructions.addInstruction("ML " + operand2); break;
                case '/': instructions.addInstruction("DV " + operand2); break;
                }

                instructions.addInstruction("ST " + tempName);
                operands.push(tempName);
            }
            catch (const runtime_error& e) {
                throw runtime_error("ошибка обработки оператора '" + string(1, c) + "': " + e.what());
            }
        }
    }

    if (operands.size() != 1) {
        throw runtime_error("ошибка вычисления: в стеке осталось " + to_string(operands.size()) + " элементов");
    }
}

void PostfixConverter::printInstructions() const {
    instructions.printAll();
}
