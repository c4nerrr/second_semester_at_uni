#include <iostream>
#include <algorithm>
#include <cmath>
#include <conio.h>
using namespace std;


struct FacultyRe {
    string name;
    int year;
    int debts;
};

template<typename hihi>
//----------------------------------------------------------------------------------------------
class Node { //окремі елементи цього списку (окремі ноди)
    public:
    hihi data;
    Node *next, *prev;
    Node(hihi data) { //клас Ноди що описує один елемент двузв'язного списку
        this->data = data;
        this->next = nullptr;
        this->prev = nullptr;
    };

};
//-------------------------------------------------------------------------------------------
template<typename hihi>
class LinkedList {

    public:
    Node<hihi> *head, *tail;
    int Size;

    LinkedList();
    ~LinkedList();


    //прописуємо методи що відповідають за операції з цим двузв'язним списком
    void push_front(hihi data);
    void push_back(hihi data);

    void pop_front();
    void pop_back();

    int getSize() {
        return Size;
    }

    Node<hihi> *getAt (int index);

    void insert(int index, hihi data); //вставка мєжду елементами

    void erase(int index); //удаляєм конкретний елемент


};
//------------------------------------------------------------------------------------------

template<typename hihi>
LinkedList<hihi>::LinkedList() { //конструктор лінкід ліст
    head = nullptr;
    tail = nullptr;
    Size = 0;
}

template<typename hihi>
LinkedList<hihi>::~LinkedList() { //діструктор лол
    while (head != nullptr) {
        pop_front();
    }
}


//========================================================================

template<typename hihi>
void LinkedList<hihi>::push_front(hihi data) { //впіхнуть елемент з самого початку
    Node<hihi> *ptr = new Node<hihi>(data); //создаєм новій обєкт
    ptr->next=head; //якщо хед указує на існуючий об'єкт то і некст буде вказувати на існуючий
    if (head != nullptr) {
        head->prev = ptr;
    }
    if (tail == nullptr) {//означає шо ми додаємо САМИЙ ПЕРШИЙ обьєкт
        tail = ptr;
        head = ptr;
    }
    Size++;
}

template<typename hihi>
void LinkedList<hihi>::push_back(hihi data) { //впіхнуть елемент з самого кінця
    Node<hihi>* ptr = new Node<hihi>(data);
    ptr->prev = tail;
    if (tail != nullptr) {
        tail->next = ptr;
    }
    if (head == nullptr) {
        head = ptr;
        tail = ptr;
    }
    Size++;
}

template<typename hihi>
void LinkedList<hihi>::pop_front() { //удаляє з самого початку
    if (head == nullptr) {
        return;
    }

    Node<hihi> *ptr = head->next;
    if (ptr != nullptr) {
        ptr->prev = nullptr;
    }
    else {
        tail = nullptr;
    }
    delete head;
    head = ptr;
    Size--;
}


template<typename hihi>
void LinkedList<hihi>::pop_back() {
    if (tail == nullptr) { //об'єктів нема
        return;
    }
    Node<hihi> *ptr = tail->prev;
    if (ptr != nullptr) {
        ptr->next = nullptr;
    }
    else {
        head = nullptr;
    }
    delete tail;
    tail = ptr;
    Size--;

}

template<typename hihi>
Node<hihi>* LinkedList<hihi>::getAt(int index) {
    Node<hihi> *ptr = head;
    int n = 0;

    while (n != index && ptr != nullptr) {
            ptr = ptr->next;
            n++;
    }
    return ptr;
}

template<typename hihi>
void LinkedList<hihi>::insert(int index, hihi data) {
    Node<hihi> *right = getAt(index);
    if (right == nullptr) {
        push_back(data);
        return;
    }
    Node<hihi> *left = right->prev;
    if (left == nullptr) {
        push_front(data);
        return;
    }
    Node<hihi> *ptr = new Node<hihi>(data);
    ptr->prev = left;
    ptr->next = right;
    left->next = ptr;
    right->prev = ptr;
    Size++;
}

template<typename hihi>
void LinkedList<hihi>::erase(int index) {
    Node<hihi> *ptr = getAt(index);
    if (ptr == nullptr) {
        return;
    }
    if (ptr->prev == nullptr) { //означає, що ми хочемо видалити перший елмент
       pop_front();
        return;
    }
    if (ptr->next == nullptr) { //останній елемент видаляємо
        pop_back();
        return;
    }

    Node<hihi> *left = ptr->prev; //ссилка на об'єкт зліва
    Node<hihi> *right = ptr->next;
    left->next = right;
    right->prev = left;

    delete ptr; //видалили промєжуточний елемент
}


//-------------------------------------------------------------------------------------
int main() {
    //string fac[] = {"Грифіндор", "Слизерін", "Рейвенклов", "Гафелпаф"};

    LinkedList<FacultyRe> list;
    char coi = '67';
    do {
        cout << "Вітаю. Програма реалізує методи двозв'язного списку." << endl;
        cout << "--MENU--" << endl;
        cout << "1. Створення порожнього списку." << endl;
        cout << "2. Додати елемент в кінець списку." << endl;
        cout << "3. Видалити елемент з кінця списку" << endl;
        cout << "4. Перегляд списку" << endl;
        cout << "5. Очистити весь список" << endl;
        cout << "0. Вийти" << endl;

        cin >> coi;
        cout << "Автоматично додано елемент 67" << endl;
        switch (coi) {
            case '1':

                break;

                case '2':

                break;
                case '3':

                break;
                case '4':

                break;
                case '5':

                break;
            default:
                cout << "Шо ти вводиш, урод? Хапні гавна." << endl;
                exit(1);
                break;

        }


    }while(coi != '0');
    return 0;
}