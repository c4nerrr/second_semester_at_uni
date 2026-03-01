#include <iostream>
#include <algorithm>
#include <windows.h>
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

    void spisok();
    void kosips();

    void pop_front();
    void pop_back();

    void clear();

    int getSize() {
        return Size;
    }

    Node<hihi> *getAt (int index);

    void insert(int index, hihi data); //вставка мєжду елементами

    void erase(int index); //удаляєм конкретний елемент

    void findMinMaxDebts();


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
   clear();
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
    head = ptr;
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
    tail = ptr;
    Size++;
}

template<typename hihi>
void LinkedList<hihi>::spisok() {
    Node<hihi> *current = head;
    int i = 0;
    while (current != nullptr) {
        cout << i+1  << "-й елемент " << endl;
        cout << "-------------------------------" << endl;
        cout << "Факультет: ";
        cout << current->data.name << " " << endl;
        cout << "Рік: ";
        cout << current->data.year << " " << endl;
        cout << "Заборгованості: ";
        cout << current->data.debts << " " << endl;
        cout << "-------------------------------" << endl;

        i++;
        current = current->next;
    }
}


template<typename hihi>
void LinkedList<hihi>::kosips() {
    Node<hihi> *current = tail;
    int i = 0;
    while (current != nullptr) {
        cout << i+1  << "-й елемент " << endl;
        cout << "-------------------------------" << endl;
        cout << "Заборгованості: ";
        cout << current -> data.debts << " " << endl;
        cout << "Рік: ";
        cout << current->data.year << " " << endl;
        cout << "Факультет: ";
        cout << current->data.name << " " << endl;
        cout << "-------------------------------" << endl;
        i++;
        current = current->prev;
    }
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
void LinkedList<hihi>::clear() {
    while (Size) {
        pop_front();
    }
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

template<typename hihi>
void LinkedList<hihi>::findMinMaxDebts() {
    if (head == nullptr) {
        return;
    }
    Node<hihi> *current = head;
    int MAXIM = current->data.debts;
    int MINITA = current->data.debts;

    string LYCHI_FAC = current->data.name;
    string HYDSHI_FAC = current->data.name;

    while (current != nullptr) {
        if (current->data.debts > MAXIM) {
            MAXIM = current->data.debts;
            HYDSHI_FAC = current->data.name;
        }
        if (current->data.debts < MINITA) {
            MINITA = current->data.debts;
            LYCHI_FAC = current->data.name;
        }
        current = current->next;
    }
    cout << "Факультет з найбільшою кількістю боргів: " << HYDSHI_FAC << endl;
    cout << "Кількість боргів: " << MAXIM << endl;
    cout << "-----------------------" << endl;
    cout << "Найтоповіший факультет з найменшою кількістю боргів: " << LYCHI_FAC << endl;
    cout << "Кількість боргів: " << MINITA << endl;
    cout << "-----------------------" << endl;
}


//-------------------------------------------------------------------------------------
int main() {
    //string fac[] = {"Грифіндор", "Слизерін", "Рейвенклов", "Гафелпаф"};
    FacultyRe pynktiki;
    LinkedList<FacultyRe> list;
    char coi = '6';
    cout << endl << endl;
    cout << "Вітаю. Програма реалізує методи двозв'язного списку." << endl;
    cout << endl;
    do {
        cout << "--MENU--" << endl;
        cout << "1. Додати елемент в кінець списку." << endl;
        cout << "2. Видалити елемент з кінця списку" << endl;
        cout << "3. Перегляд списку" << endl;
        cout << "4. Очистити весь список" << endl;
        cout << "5. Визначити факультет з мінімальною та максимальною заборгованістю" << endl;
        cout << "0. Вийти" << endl;

        cin >> coi;
        switch (coi) {
            //---------------------------------------------------
            case '1':{
                cout << "Введіть назву факультету:" << endl;
                cin >> pynktiki.name;
                cout << "Введіть рік: " << endl;
                cin >> pynktiki.year;
                cout << "Введіть кількість заборгованностей: " << endl;
                cin >> pynktiki.debts;
                list.push_back(pynktiki);
                cout <<"Ваші важливі дані успішно додано."<<endl;
                }
                break;
            //---------------------------------------------------
                case '2': {
                    list.pop_back();
                    cout << "Останній елемент було успішно видалено!" << endl;
                }

                break;

            //--------------------------------------------------
                case '3':
                if (list.getSize() == 0) {
                    cout << "У вас порожній список!";
                    cout << endl;
                    continue;
                }
                cout << "Список у прямому порядку:" << endl;
                list.spisok();
                cout << "Список у звоторньому напрямку:" << endl;
                list.kosips();
                break;

            //----------------------------------------------
                case '4':
                if (list.getSize() == 0) {
                    cout << "У вас порожній список!" << endl;
                    cout << endl;
                    continue;
                }
                list.clear();
                cout << "Список успішно очищено!" << endl;
                break;
            //----------------------------------------------
            case '5':
                list.findMinMaxDebts();
                break;

            //---------------------------------------------
                case '0':
                break;
            //--------------------------------------------

            default:
                cout << "Шо ти вводиш, урод? Хапні гавна." << endl;
                int i = 0;
                short ii = 0;
                while (i != 3) {
                    Sleep(200);
                    cout << "installing Wacatac......" << endl;
                    cout << "installing WannaCry...." << endl;
                    Sleep(50);
                    cout << "installing Beast...." << endl;

                    i++;
                }
                Sleep(500);
                while (ii != 500) {
                    Sleep(20);
                    cout << "delete system.32...." << endl;
                    ii++;
                }
                exit(1);
                break;
        }
    }while(coi != '0');
    return 0;
}