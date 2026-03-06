//
// Created by c4ner on 3/6/2026.
//

#include "ACD_LABB_5.h"
#include <iostream>
#include <limits>
using namespace std;

//----------------------------------------
template<typename lol>
class Stack {
    public:
    Stack();
    ~Stack();

    void push(lol data);
    lol top(); //значення елементу не видаляючи його
    void pop(); //видалення
    bool empty()const; //перевірка пустий лі стек
    int getSize()const;
    void clear();
    void print();

    //13 варіант завдання функція:
    void TwoChar();

private:
    class Node {
        public:
        Node *pNext;
        lol data;
        Node(lol data = lol(), Node *pNext = nullptr) {
            this->data = data;
            this->pNext = pNext;
        }
    };
    int Size = 0;
    Node *head;
};

//-----------------------------------------
template<typename lol>
Stack<lol>::Stack() {
    Size = 0;
    head = nullptr;

}

template<typename lol>
Stack<lol>::~Stack() {
    clear();
}


template<typename lol>
void Stack<lol>::push(lol data) {
    head =  new Node(data, head);
    Size++;
}

template<typename lol>
lol Stack<lol>::top() {
    if (head == nullptr) {
        cout << "Стек пустий. " << endl;
        return lol();
    }
    cout <<"---------------------------------" << endl;
    cout <<"Значення останнього елемента: "<< head->data << endl;
    cout <<"---------------------------------" << endl;
    return head->data;
}


template<typename lol>
void Stack<lol>::pop() {
    if (head == nullptr) {
        return;
    }
    Node *current = head;
    head = head->pNext;
    delete current;
    Size--;
}

template<typename lol>
bool Stack<lol>::empty() const {
    if (head == nullptr) {
        cout << "Стек пустий" << endl;
        return true;
    }
    cout << "Стек не пустий. " << endl;
    return false;
}

template<typename lol>
int Stack<lol>::getSize() const {
    return Size;
}

template<typename lol>
void Stack<lol>::clear() {
    while (Size) {
        pop();
    }
}

template<typename lol>
void Stack<lol>::print() {
    Node *current = head;
    cout <<"-----------------------------------" << endl;
    cout <<"Усі елементи стеку:" <<endl;
    while (current != nullptr) {
        cout << current->data << endl;
        current = current->pNext;
    }
    cout <<"-----------------------------------" << endl;
}

template<typename lol>
void Stack<lol>::TwoChar() {
    Node *current = head;
    cout <<"-----------------------------------" << endl;
    cout << "Елементи в стеку, що мають лише 2 символа:" << endl;
    while (current != nullptr) {
        if ((current->data).length() == 2) {
            cout << current->data << endl;
            current = current->pNext;
        }
        else {
            current = current->pNext;
        }
    }
    cout <<"---------------------------------" << endl;
}


int main () {
    Stack<string> stack;
    char choi = '1';
    do {
        cout << "--MENU--" << endl;
        cout << "1. Додати елемент в стек" << endl;
        cout << "2. Видалення елементу зі стеку" << endl;
        cout << "3. Перевірити чи порожній стек чи ні" << endl;
        cout << "4. Переглянути вершину стеку" << endl;
        cout << "5. Переглянути усі елементи стеку" << endl;
        cout << "6. Очистити весь стек" << endl;
        cout <<"---------------------------------" << endl;
        cout << "7. Вивести елементи стеку, що мають тільки 2 символа" << endl;
        cout << "0. Вийти" << endl;
        cin >> choi;

        switch (choi) {
            case '1': {
                string data;
                cout << "Введіть рядок стеку який хочете додати: " << endl;
                cin >> data;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                stack.push(data);
                cout << "Успішно додано! " << endl;
            }
                break;
                case '2':
                stack.pop();
                cout<<"Останній елемент успішно видалено!" << endl;
                break;
                case '3':
                stack.empty();
                break;
                case '4':
                stack.top();
                break;
                case '5':
                stack.print();
                break;
                case '6':
                stack.clear();
                cout << "Стек успішно очищено!" << endl;
                break;
                case '7':
                stack.TwoChar();
                break;
                case '0':
                break;

                default:
                cout << "Ти блять заїбав хуйню вводити серйозно "<< endl;
                exit(-1);
                break;

        }
    }while (choi != '0');
return 0;
}
