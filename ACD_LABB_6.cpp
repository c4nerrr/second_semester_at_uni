
#include <iostream>
#include <string>
#include <limits>
#include <utility>
using namespace std;

struct blinGG{
    double cena{};
    string name;
};

template <typename blin>
class LList {
    public:
    LList();
    ~LList();

    void enqueue(const blin& data);
    void dequeue();

    void proverka();
    void prosmotr_first_elementa();

    void print();
    void clear();

    void calcPensCost();


    private:
    class Node {
        public:
        Node* pNext;
        blin data;

        explicit Node(blin data = blin(), Node* pNext = nullptr) {
            this->data = std::move(data);
            this->pNext = pNext;

        };
    };
    int Size = 0;
    Node* head;
};

template<typename blin>
LList<blin>::LList() {
    Size = 0;
    head = nullptr;

}

template<typename blin>
LList<blin>::~LList() {
    clear();
}

template<typename blin>
void LList<blin>::enqueue(const blin& data) {
    if (head == nullptr) {
        head = new Node(data);
    }
    else {
        Node* current = this->head;
        while (current->pNext != nullptr) {
            current = current->pNext;
        }
        current->pNext = new Node(data);
    }
    Size++;
}

template<typename blin>
void LList<blin>::dequeue() {
    if (head == nullptr) {
        proverka();
        return;
    }
    const Node* temp = head;
    head = head->pNext;
    delete temp;
    Size--;
}

template<typename blin>
void LList<blin>::proverka() {
    if (head == nullptr) {
        cout << "     ------------------" << endl;
        cout << "Черга пуста" << endl;
        cout << "     ------------------" << endl;
    }
    else {
        cout << "     ------------------" << endl;
        cout << "Черга не пуста, кількість елементів: " << Size << endl;
        cout << "     ------------------" << endl;
    }
}

template<typename blin>
void LList<blin>::prosmotr_first_elementa() {
    if (head == nullptr) {
        proverka();
    }
    else {
        cout << "     ------------------" << endl;
        cout << "Перший елемент черги: " << endl;
           cout << "Назва: " <<  head->data.name << endl;
           cout << "Ціна: " <<  head->data.cena << endl;
        cout << "     ------------------" << endl;
    }
}

template<typename blin>
void LList<blin>::print() {
    if (head == nullptr) {
        proverka();
    }
    else {
        Node* current = head;
        cout << "     ------------------" << endl;
        while (current != nullptr) {
            cout << "Назва: " << current->data.name << endl;
            cout << "Ціна: " <<  current->data.cena << endl;
            current = current->pNext;
        }
        cout << "     ------------------" << endl;
    }

}

template<typename blin>
void LList<blin>::clear() {
    while (Size) {
        dequeue();
    }
}

template<typename blin>
void LList<blin>::calcPensCost() {
    if (head == nullptr) {
        proverka();
    }
    else {
        double syma = 0;
        Node* current = head;
        while (current != nullptr) {
            if (current->data.name == "Ручка кулькова") {
                syma += current->data.cena;
                current = current->pNext;
            }
            else {
                current = current->pNext;
            }
        }
        cout << "     ------------------" << endl;
        cout << "Загальна сума товарів 'Ручка кулькова' " << syma << endl;
        cout << "     ------------------" << endl;
    }
}


int main () {
    cout << "Програма створена для реалзіації алгоритму Черги." << endl;
    char ch = '8';
    LList<blinGG> listochek;
    blinGG em_stryctyra_tipo;

    do {
        cout << "     ------------------" << endl;
        cout << "         ---MENU---" << endl;
        cout << "     ------------------" << endl;
        cout << "| 1. Помістити елемент в чергу.      |" << endl;
        cout << "| 2. Вилучити елемент з черги.       |" << endl;
        cout << "| 3. Перевірити чи порожня черга.    |" << endl;
        cout << "| 4. Переглянути перший елемент.     |" << endl;
        cout << "| 5. Переглянути усі елементи черги. |" << endl;
        cout << "| 6. Очистити всі елементи черги.    |" << endl;
        cout << "     ------------------" << endl;;
        cout << " 0. Вихід.    " << endl;
        cout << " 7. Дод.функція: порахувати суму товарів з назвою 'Ручка кулькова'. " << endl;

        cin >> ch;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        switch (ch) {
            case '1':
                cout << "     ------------------" << endl;;
                cout << "Введіть назву елементу яку хочете додати: ";
                getline(cin, em_stryctyra_tipo.name);
                cout << "Введіть ціну вашого елементу: ";
                cin >> em_stryctyra_tipo.cena;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "     ------------------" << endl;;
                listochek.enqueue(em_stryctyra_tipo);
                break;

                case '2':
                listochek.dequeue();
                cout << "     ------------------" << endl;
                cout << "Перший елемент успішно вилучено! " << endl;
                cout << "     ------------------" << endl;
                break;
                case '3':
                listochek.proverka();
                break;

                case '4':
                listochek.prosmotr_first_elementa();
                break;
                case '5':
                listochek.print();

                case '6':
                listochek.clear();
                cout << "     ------------------" << endl;
                cout << "Вся черга була успішно очищена!" << endl;
                cout << "     ------------------" << endl;
                break;

                case '7':
                listochek.calcPensCost();
                break;


                case '0': //NOLINT
                break;

                default:
                cerr << " Segmentation fault." << endl;
                exit(-1);
        }
    }while (ch != '0');
    cout << "fhgefb" << endl;
return 0;
}
